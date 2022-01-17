#include <iostream>
#include <vector>

struct modint {
    long long num;
    const static long long p = 998244353;
    constexpr static long long pow(long long n, long long k) {//n^k(mod p)
        long long ret = 1;
        while(k) {
            if(k&1) ret = ret * n % p;
            n = n * n % p;
            k >>= 1;
        }
        return ret;
    }
    // a*A + b*B = 1
    constexpr static void euclid(long long &a, long long &b) { // a>=b A*b+B*(a-a/b*b)=1
        if (a == 1) {
            a = 1;
        }
        else {
            long long A = b, B = a % b;
            euclid(A, B);
            b = (A - (p + a / b) % p * B % p + p) % p;
            a = B;
        }
    }
    constexpr static long long rev(const long long n) {// n*x-p*y=1
        //long long q = p;
        //euclid(p, n, p);
        //return n % q;
        return pow(n,p-2);
    }
    constexpr modint() : num(0) {}
    constexpr modint(long long x) : num(x%p < 0 ? x%p+p : x%p) {}
    constexpr modint inv() const {return rev(num);}
    modint operator-() const {return modint(p-num);}
    modint& operator+=(const modint &other){
        num = (num + other.num) % p;
        return *this;
    }
    modint& operator-=(const modint &other){
        num = (num - other.num + p) % p;
        return *this;
    }
    modint& operator*=(const modint &other){
        num = (num * other.num) % p;
		if(num < 0) num += p;
        return *this;
    }
    modint& operator/=(const modint &other){
        (*this) *= other.inv();
        return *this;
    }
    modint& operator+=(const long long &other){
        num = (num + other) % p;
        return *this;
    }
    modint& operator-=(const long long &other){
        num = (num - other + p) % p;
        return *this;
    }
    modint& operator*=(const long long &other){
        num = (num * other) % p;
        return *this;
    }
    modint& operator/=(const long long &other){
        (*this) *= rev(other);
        return *this;
    }
    modint& operator++(){return *this += 1;}
    modint& operator--(){return *this -= 1;}
    modint& operator=(const long long &other){return (*this) = modint(other);}
    modint operator+(const modint &other) const{return modint(*this) += other;}
    modint operator-(const modint &other) const{return modint(*this) -= other;}
    modint operator*(const modint &other) const{return modint(*this) *= other;}
    modint operator/(const modint &other) const{return modint(*this) /= other;}
    modint operator+(const long long &other) const{return modint(*this) += other;}
    modint operator-(const long long &other) const{return modint(*this) -= other;}
    modint operator*(const long long &other) const{return modint(*this) *= other;}
    modint operator/(const long long &other) const{return modint(*this) /= other;}
    bool operator==(const modint &other) const{return num == other.num;}
};
std::istream& operator>>(std::istream &is, modint x) {
    is >> x.num;
    return is;
}
std::ostream& operator<<(std::ostream &os, const modint &x){
    os << x.num;
    return os;
}
 
struct combination{
    std::vector<modint> li;
    std::vector<modint> rev;
    combination(int size = 202000){
        li = std::vector<modint>(size);
        rev = std::vector<modint>(size);
        li[0] = 1;
        for(int i= 1; i< size;i++) li[i] = li[i-1]*i;
        rev.back() = modint(1)/li.back();
        for(int i = size-1; i > 0; i--) rev[i-1] = rev[i]*i;
    }
    modint nCk(int n, int k){
        if(k < 0 || n < k) return 0;
        return li[n]*rev[k]*rev[n-k];
    }
} comb(202000);