/*
verlified by
AIZU ONLINE JUDGE DSL-2-G https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_G
submission: https://onlinejudge.u-aizu.ac.jp/status/users/sapphire15/submissions/1/DSL_2_G/judge/4956456/C++17
*/

#include <iostream>
#include<algorithm>
#include <vector>
#include <functional>
#include <cassert>

/*nod: 値 monoid: モノイドの値 flag: モノイドが非伝播か t0: nodの単位元 so: モノイドの単位元 operation: nodのmerge merge: monoidのmerge calc: モノイドの作用*/
template<typename T, typename S>
struct LazySegTree{
    int size;
    std::vector<T> nod;
    std::vector<S> monoid;
    std::vector<bool> flag;
    T t0;
    S s0;
    std::function<T(T,T)> operation;
    std::function<S(S,S)> merge;
    std::function<T(T,S,int)> calc;
    LazySegTree(int n, T _t0, S _s0, std::function<T(T,T)> _operation, std::function<S(S,S)> _merge, std::function<T(T,S,int)> _calc){
        t0 = _t0;
        s0 = _s0;
        operation = _operation;
        merge = _merge;
        calc = _calc;
        size = 1;
        while(n > size) size *= 2;
        nod = std::vector<T> (size*2-1, t0);
        monoid = std::vector<S> (size*2-1, s0);
        flag = std::vector<bool> (size*2-1);
    }
    void update(int a, int b, S x){ // operation(da[a, b), x)
        assert(0 <= a && a < size);
        assert(0 <= b && b <= size);
        assert(a <= b);
        update_query(a,b,0,0,size,x);
    }
    T sum(int a, int b){ // merge[a, b)
        assert(0 <= a && a < size);
        assert(0 <= b && b <= size);
        assert(a <= b);
        return sum_query(a,b,0,0,size);
    }
   void deb(){
        for(int i=0;i<size*2-1;i++){
            if(i==size*2-2) std::cout << nod[i] <<std:: endl;
            else std::cout << nod[i] << ' ';
        }
        for(int i=0;i<size*2-1;i++){
            if(i==size*2-2) std::cout << monoid[i] <<std:: endl;
            else std::cout << monoid[i] << ' ';
        }
        return;
    }
    private:
    void disassembly(int k, int l, int r){
        if(r-l>1){
            monoid[k*2+1] = merge(monoid[k*2+1], monoid[k]);
            monoid[k*2+2] = merge(monoid[k*2+2], monoid[k]);
            flag[k*2+1] = true;
            flag[k*2+2] = true;
        }
        nod[k] = calc(nod[k],monoid[k],r-l);
        monoid[k] = s0;
        flag[k] = false;
    }
    T update_query(int a,int b,int k,int l,int r,S x){
        if(r<=a||b<=l){
            if(flag[k]) return calc(nod[k], monoid[k], r-l);
            return nod[k];
        }
        if(a<=l && r<=b){
            monoid[k] = merge(monoid[k], x);
            flag[k] = true;
            return calc(nod[k], monoid[k],r-l);
        }
        else{
            if(flag[k]) disassembly(k,l,r);
            nod[k] = operation(update_query(a,b,k*2+1,l,(l+r)/2,x), update_query(a,b,k*2+2,(l+r)/2,r,x));
            return nod[k];
        }
    }
    T sum_query(int a,int b,int k,int l,int r){
        if(r<=a||b<=l){
            return t0;
        }
        if(a<=l && r<=b){
            if(flag[k]) return calc(nod[k],monoid[k],r-l);
            else return nod[k];
        }
        if(flag[k]) disassembly(k, l, r);
        return operation(sum_query(a,b,k*2+1,l,(l+r)/2),sum_query(a,b,k*2+2,(l+r)/2,r));
    }
};

int main(){
    int n,q; std::cin >> n >> q;
    std::vector<long long> ans(0);
    LazySegTree<long long, long long> lst(n,0,0,[](long long a, long long b){return a+b;}, [](long long a, long long b){return a+b;},[](long long a, long long b, long long c){return (long long)a+b*c;});
    for(int i= 0;i<q;i++){
        int w; std::cin >> w;
        if(w == 0){
            int s,t,x; std::cin >> s >> t >> x;
            lst.update(s-1, t, x);
        }
        else{
            int s,t; std::cin >> s >> t;
            std::cout << lst.sum(s-1, t) << '\n';
        }
    }
}