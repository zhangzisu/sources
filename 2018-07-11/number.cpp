#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>
typedef long long lnt;
typedef unsigned long long ulnt;

int prime[1000010], vis[1000010], pnt = 0;
inline void shai() {
    for (int i = 2; i < 1000010; i++) {
        if (!vis[i]) {
            prime[++pnt] = i;
        }
        for (int j = 1; j <= pnt; j++) {
            if (i * prime[j] <= 1000010) continue;
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

#define MAXN 310
int n;
lnt a;
lnt gcd(lnt a, lnt b) { return b ? gcd(b, a % b) : a; }

const int test_case = 10;
inline lnt pow(lnt n, lnt m, lnt p) {
    lnt res = 1;
    for (; m; m >>= 1) {
        if (m & 1) res = res * n % p;
        n = n * n % p;
    }
    return res;
}
inline unsigned rand_uint() {
    return (unsigned(rand()) << 16) | rand();
}
inline int rand_int() {
    return rand_uint() >> 1;
}
inline ulnt rand_ulnt() {
    return (ulnt(rand_uint()) << 32) | rand_uint();
}
inline lnt rand_lnt() {
    return rand_ulnt() >> 1;
}
inline bool mr(lnt n) {
    if (n < 2) return false;
    if (n == 2) return true;
    for (int i = 0; i < test_case; i++) {
        lnt test_num = rand_lnt() % (n - 2) + 2;
        if (pow(test_num, n, n) != test_num) return false;
    }
    return true;
}

inline lnt rho(lnt n, lnt c) {
    lnt i = 1, k = 2, x = rand_lnt() % (n - 1) + 1, y = x;
    while (1) {
        i++;
        x = (x * x % n + c) % n;
        lnt p = gcd((y - x + n) % n, n);
        if (p != 1 && p != n) return p;
        if (y == x) return n;
        if (i == k) {
            y = x;
            k <<= 1;
        }
    }
}
std::map<lnt, lnt> M;
lnt dat[100010];
int count = 0;
void split(lnt n, lnt c) {
    if (n == 1) return;
    if (mr(n)) {
        dat[++count] = n;
        return;
    }
    lnt p = n, k = c;
    while (p >= n) p = rho(p, c--);
    split(p, k);
    split(n / p, k);
}

lnt max = 0, cnt = 0;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin >> n;
    int start = clock();
    for (int i = 1; i <= n; i++) {
        std::cin >> a;
        for (int i = 1; i <= pnt; i++) {
            while (a % prime[i] == 0) a /= prime[i], dat[++count] = prime[i];
        }
        split(a, rand_lnt() % n);
    }
    printf("%f\n", 1. * (clock() - start) / CLOCKS_PER_SEC);
    for (int i = 1; i <= count; i++) M[dat[i]]++;
    for (std::map<lnt, lnt>::iterator x = M.begin(); x != M.end(); x++) {
        if (x->second > max) {
            max = x->second;
            cnt = 1;
        } else if (x->second == max) {
            cnt++;
        }
    }
    std::cout << max << std::endl;
    BigInteger bint(1);
    for (int i = 1; i <= cnt; i++) bint *= 2;
    bint -= 1;
    std::cout << bint << std::endl;
}