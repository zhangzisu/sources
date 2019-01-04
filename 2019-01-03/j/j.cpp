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

