#include <iostream>
#include <vector>

long long pow(long long n, long long p, long long k) {//n^k(mod p)
    if (!k) return 1;
    long long a = pow(n,p, k>>1);
    a = a * a%p;
    if (k & 1) a = a * n%p;
    return a;
}
void euclid(long long &a, long long &b, long long p) { // a>=b A*b+B*(a-a/b*b)=1
    if (a == 1) {
        a = 1;
    }
    else {
        long long A = b, B = a % b;
        euclid(A, B, p);
        b = (A - (p + a / b) % p * B % p + p) % p;
        a = B;
    }
}
long long rev(long long n, long long p) {// n*x-p*y=1
    //long long q = p;
    //euclid(p, n, p);
    //return n % q;
    return pow(n,p,p-2);
}
long long bino(long long n, long long m, long long p) {//nCm(mod p)
    long long ans = 1, div = 1;
    for(int i = 0;i < m; i++){
        ans = (n - i) * ans % p;
        div = div * (i +1) % p;
    }
    return ans * rev(div, p) % p;
}
struct modint {
    long long num;
    long long p;
    modint() {
        num = 0;
        p = 998244353;
    }
    modint(long long x) {
        p = 998244353;
        num = x % p;
    }
	modint inv()const{return rev(num, p);}
	modint operator-() const{return modint(p-num);}
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
		(*this) *= rev(other, p);
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
std::istream& operator>>(std::istream &is, const modint x) {
	std::cin >> x.num;
	return is;
}
std::ostream& operator<<(std::ostream &os, const modint &x){
    std::cout << x.num;
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
        if(k <= 0 || n <= k) return 1;
        return li[n]*rev[k]*rev[n-k];
    }
} comb(202000);
