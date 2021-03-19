/*
verlified by
AIZU ONLINE JUDGE DSL-2-G https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_C
submission: https://onlinejudge.u-aizu.ac.jp/status/users/sapphire15/submissions/1/GRL_3_C/judge/5301789/C++17
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <stack>

class UnionFind {
    int _n;
    int _size;
    std::vector<int> par_size;

    public:
    UnionFind() :_n(0), _size(0){}
    UnionFind(int n) : _n(n), _size(n), par_size(n, -1) {}

    int unite(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        a = root(a), b = root(b);
        if(a == b) return a;
        _size--;
        if(-par_size[a] < -par_size[b]) {
            par_size[b] += par_size[a];
            return par_size[a] = b;
        }
        else {
            par_size[a] += par_size[b];
            return par_size[b] = a;
        }
    }

    int root(int a) {
        assert(0 <= a && a < _n);
        if(par_size[a] < 0) return a;
        return par_size[a] = root(par_size[a]); 
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return root(a) == root(b);
    }

    int size(int a) {
        assert(0 <= a && a< _n);
        return -par_size[root(a)];
    }

    int size() {return _size;}

    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = root(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                        [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }
};

class SCC {
    typedef std::vector<std::vector<int>> Vec2;
    size_t node_num;
    Vec2 _to;
    Vec2 _ot;
    void dfs1(std::vector<bool> &achieved, 
              std::stack<size_t> &_st, 
              const size_t _now) const {
        achieved[_now] = true;
        for(size_t i = 0; i < _to[_now].size(); i++) {
            const size_t _nxt = _to[_now][i];
            if(!achieved[_nxt]) {
                dfs1(achieved, _st, _nxt);
            }
        }
        _st.push(_now);
    }

    void dfs2(std::vector<bool> &achieved,
              const size_t _now) {
        achieved[_now] = false;
        for(size_t i = 0; i < _ot[_now].size(); i++) {
            const size_t _nxt = _ot[_now][i];
            if(achieved[_nxt]) {
                group.unite(_now, _nxt);
                dfs2(achieved, _nxt);
            }
        }
    }

    public:
    UnionFind group;

    SCC(const size_t num_of_node) : node_num(num_of_node),
                                    _to(num_of_node), 
                                    _ot(num_of_node),
                                    group(num_of_node) {}

    SCC(const Vec2 &_ed) : node_num(_ed.size()),
                           _to(_ed), group(_ed.size()) {
        for(size_t i = 0; i < _to.size(); i++) {
            for(size_t j = 0; j < _to[j].size(); j++) {
                _ot[_to[i][j]].push_back(i);
            }
        }
    }

    void add_edge(const size_t &a, const size_t &b) { // a to b
        assert(a < node_num);
        assert(b < node_num);
        _to[a].push_back(b);
        _ot[b].push_back(a);
    }

    void construct() {
        std::vector<bool> achieved(node_num);
        std::stack<size_t> _st;
        for(size_t i = 0; i < node_num; i++) {
            if(!achieved[i]) dfs1(achieved, _st, i);
        }
        while(!_st.empty()) {
            size_t _now = _st.top();
            _st.pop();
            if(achieved[_now]) dfs2(achieved, _now);
        }
    }
};

int main() {
    int v, e; std::cin >> v >> e;
    SCC scc(v);
    for(int i = 0; i < e; i++) {
        int a, b; std::cin >> a >> b;
        scc.add_edge(a, b);
    }
    scc.construct();

    int q; std::cin >> q;
    for(int i = 0; i < q; i++) {
        int a, b; std::cin >> a >> b;
        std::cout << scc.group.same(a,b) << std::endl;
    }
}