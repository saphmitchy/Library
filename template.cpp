#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <bitset>
#include <climits>
#include <string>
#include <cmath>
#include <bitset>
#include <complex>
#include <functional>
#include <ctime>
#include <cassert>
#include <fstream>
#include <stack>
#include <random>

typedef long long ll;
typedef std::pair<int, int> Pii;
typedef std::pair<long long, long long> Pll;
typedef std::pair<double, double> Pdd;

#define rip(i, n, ss) for (int i = (ss);i < (int)( n ); i++)
#define all(a) a.begin(), a.end()
#define MM << " " <<

template<typename T>
using MaxHeap = std::priority_queue<T>;
template<typename T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template<typename T>
inline bool chmax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
template<typename T>
inline bool chmin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

# ifndef ONLINE_JUDGE
template<typename T>
void vdeb(std::vector<T> &bb) {
    for (int i = 0;i < bb.size();i++) {
        if (i == bb.size() - 1) std::cout << bb[i];
        else std::cout << bb[i] << ' ';
    }
    std::cout << '\n';
}
template<typename T>
void vdeb(std::vector<std::vector<T>> &bb) {
    for (int i = 0;i < bb.size();i++) {
        std::cout << i << ' ';
        vdeb(bb[i]);
    }
    std::cout << '\n';
}
# endif

using namespace std;

int main() {
    
}