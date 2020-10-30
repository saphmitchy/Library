/*
verlified by
AIZU ONLINE JUDGE DSL-2-B https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B
submission: https://onlinejudge.u-aizu.ac.jp/status/users/sapphire15/submissions/1/DSL_2_B/judge/4956426/C++17
*/

#include <iostream>
#include <vector>
#include <cassert>

template<typename T>
struct BIT{
    std::vector<T> li;
    int size;
    BIT (int n){
        li=std::vector<T>(n+1,0);
        size=n;
    }
    T sum (int i){ // sum of [0, n)
        assert(0 <= i && i <= size);
        if(i == 0) return 0;
        int s=0;
        while(i>0){
            s+=li[i];
            i-=i & -i;
        }
        return s;
    }
    T sum(int i, int j) { // sum of [i, j)
        assert(i <= j);
        return sum(j) - sum(i);
    }
    void add(int i,T x){ // li[i] += x
        assert(0 <= i && i < size);
        ++i;
        while(i<=size){
            li[i]+=x;
            i+=i & -i;
        }
    }
};

int main() {
    int n, q; std::cin >> n >> q;
    BIT<long long> bt(n);
    for(int i = 0; i <q; i++) {
        long long com, c, u; std::cin >> com >> c >> u;
        if(com) {
            --c; --u;
            std::cout << bt.sum(c, u+1) << '\n';
        }
        else {
            --c;
            bt.add(c, u);
        }
    }
}