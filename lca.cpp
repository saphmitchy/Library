/*
verlified by
AIZU ONLINE JUDGE GRL_5_C https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_C
submission: https://onlinejudge.u-aizu.ac.jp/status/users/sapphire15/submissions/1/GRL_5_C/judge/5047494/C++17
*/

#include <vector>
#include <cassert>

class LCA{
    int n;
    std::vector<std::vector<int>> dist;
    std::vector<std::vector<int>> ed;
    std::vector<int> depth;
    int ed_cnt;

    bool dfs(const int child, const int root, const int parent = -1) {
        if((parent != -1 && child == root) || dist[child].size() > 0) return false;
        if(parent >= 0) {
            dist[child].push_back(parent);
            depth[child] = depth[parent] + 1;
            unsigned int id = 0;
            while(1) {
                auto &now = dist[dist[child][id]];
                if(now.size() <= id) break;
                else {
                    dist[child].push_back(now[id]);
                    id++;
                }
            }
        }
        else {
            depth[child] = 0;
        }
        for(int i = 0; i < ed[child].size(); i++) {
            if(ed[child][i] == parent) continue;
            if(!dfs(ed[child][i], root, child)) return false;
        }
        return true;
    }

    int common_ancestor(const int &u, const int &v, int upper = -2) const {
        assert(depth[u] == depth[v]);
        if(u == v) return u;
        if(upper == -2) upper = dist[u].size()-1;
        if(upper == -1) return dist[u][0];
        else if (upper == 0) return dist[u][0];
        while((int)dist[u].size() <= upper || dist[u][upper] == dist[v][upper]) {
            upper--;
            if(upper == -1) return dist[u][0];
        }
        return common_ancestor(dist[u][upper], dist[v][upper], upper);
    }

    public:
    LCA(const int &_n) : n(_n) {
        ed = std::vector<std::vector<int>>(n, std::vector<int>(0));
        ed_cnt = 0;
    }
    int add_edge(const int &u, const int &v) {
        ed[u].push_back(v);
        ed[v].push_back(u);
        return ed_cnt++;
    }
    bool construct(const int &root=0) {
        assert(root < n);
        assert(ed_cnt == n-1);
        depth = std::vector<int>(n);
        dist = std::vector<std::vector<int>>(n, std::vector<int>(0));
        return dfs(root, root);
    }
    int lca(const int &u, const int &v) const {
        int a, b;
        if(depth[u] > depth[v]) {
            a = v;
            b = ancestor(u, depth[u]-depth[v]);
        }
        else {
            a = u;
            b = ancestor(v, depth[v]-depth[u]);
        }
        return common_ancestor(a, b);
    }
    int ancestor(const int &u, const int &k) const {
        assert(depth[u] >= k);
        int ret = u, up = 0;
        while(k >> up) {
            if((k >> up)&1) {
                ret = dist[ret][up];
            }
            up++;
        }
        return ret;
    }
};