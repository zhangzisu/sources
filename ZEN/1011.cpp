#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 210
#define MAXM 20010
#define MAXS 20000010
#define PRIC 2000010
int pr[PRIC], pfx[MAXS], vi[MAXS], pnt;
inline void shai() {
    pfx[1] = 0;
    for (register int i = 2; i < MAXS; i++) {
        pfx[i] = pfx[i - 1];
        if (!vi[i]) pr[++pnt] = i, pfx[i]++;
        for (register int j = 1; j <= pnt; j++) {
            if (i * pr[j] >= MAXS) break;
            vi[i * pr[j]] = 1;
            if (i % pr[j] == 0) break;
        }
    }
    pr[0] = 1;
}
long long rp[MAXM][MAXN];
inline void renping() {
    for (int m = 0; m < MAXM; m++) {
        rp[m][0] = m;
        for (int n = 1; n < MAXN; n++) {
            rp[m][n] = rp[m][n - 1] - rp[m / pr[n]][n - 1];
        }
    }
}
inline long long phi(long long m, long long n) {
    if (!n) return m;
    if (pr[n] >= m) return 1;
    if (n < MAXN && m < MAXM) return rp[m][n];
    return phi(m, n - 1) - phi(m / pr[n], n - 1);
}
inline long long pi(long long m) {
    if (m < MAXS) return pfx[m];
    int s = sqrt(m + 0.9), y = cbrt(m + 0.9);
	long long ret = phi(m, pfx[y]) + pfx[y] - 1;
	//printf("DDD | %10lld %10lld\n", ret, m);
    for (int i = pfx[y] + 1; pr[i] <= s; i++) {
        /*printf("DDD | %lld\n", */ret -= pi(m / pr[i]) - pi(pr[i]) + 1/*)*/;
    }
    return ret;
}
long long n;
int main() {
    shai(); renping();
    scanf("%lld", &n);
    printf("%lld\n", pi(n));
    return 0;
}