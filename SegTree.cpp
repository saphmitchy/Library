/*
verlified by
AIZU ONLINE JUDGE DSL-2-A https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A
submission: https://onlinejudge.u-aizu.ac.jp/status/users/sapphire15/submissions/1/DSL_2_A/judge/4956449/C++17
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

template<typename T>
struct SegTree{
    std::vector<T> nod;
    T t0;
    std::function<T(T,T)> operation;
    std::function<T(T,T)> merge;
    int size;
    SegTree(int _size, T _t0, std::function<T(T,T)> _operation, std::function<T(T,T)> _merge):t0(_t0), operation(_operation), merge(_merge){
        size=1;
        while(_size>size){
            size*=2;
        }
        nod=std::vector<T>(size*2-1, t0);
    }
    void update(int k, T a){ // operation(da[k], a)
        assert(0<= k && k < size);
        k+=size-1;
        nod[k] = operation(nod[k], a);
        while(k>0){
            k=(k-1)/2;
            nod[k] = merge(nod[k*2+1], nod[k*2+2]); 
        }
    }
    void range_update(int a, int b, T x) {
        assert(0 <= a && a < size);
        assert(0 <= b && b <= size);
        assert(a <= b);
        range_update_query(a, b, 0, 0, size, x);
    }
    T sum(int a, int b) { // merge[a, b)
        assert(0 <= a && a < size);
        assert(0 <= b && b <= size);
        assert(a <= b);
        return sum_query(a, b, 0, 0, size);
    }
    void deb(){
        for(int i=0;i<size*2-1;i++){
            if(i==size*2-2) std::cout << nod[i] <<std:: endl;
            else std::cout << nod[i] << ' ';
        }
        return;
    }
    private:
    void range_update_query(int a,int b,int k,int l,int r,T x){
        if(r<=a||b<=l){
            return;
        }
        if(a<=l && r<=b){
            nod[k] = operation(nod[k], x);
            return;
        }
        else{
            range_update_query(a,b,k*2+1,l,(l+r)/2,x);
            range_update_query(a,b,k*2+2,(l+r)/2,r,x);
            return;
        }
    }
    T sum_query(int a,int b,int k,int l,int r){
        if(r<=a||b<=l){
            return t0;
        }
        if(a<=l && r<=b){
            return nod[k];
        }
        else{
            return merge(sum_query(a,b,k*2+1,l,(l+r)/2),sum_query(a,b,k*2+2,(l+r)/2,r));
        }
    }
};

const int INT_M = ~(1<<31);

int main() {
    int n, q; std::cin >> n >> q;
    SegTree<int> st(n, INT_M,
                    [](int x, int y) {return y;},
                    [](int x, int y) {return std::min(x, y);});
    for(int i = 0; i < q; i++) {
        int com, x, y; std::cin >> com >> x >> y;
        if(com == 0) {
            st.update(x, y);
        }
        else {
            std::cout << st.sum(x, y+1) << '\n';
        }
    }
}