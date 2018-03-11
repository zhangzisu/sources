#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define D(format, args...) fprintf(stderr, format "\n", ##args)
#define MAXN 102400
#define MOD 1000000007
#define INV 500000004
int vi[MAXN], pr[MAXN], cnt = 0;
inline void shai() {
    std::fill(vi, vi + MAXN, 1);
    vi[0] = vi[1] = 0;
    for (int i = 2; i < MAXN; i++) {
        if (vi[i]) pr[++cnt] = i;
        for (int j = 1; j <= cnt; j++) {
            if (i * pr[j] >= MAXN) break;
            vi[i * pr[j]] = 0;
            if (i % pr[j] == 0) break;
        }
    }
}
inline int fuck(int x, int p) {
    register int ret = 1;
    while (p) {
        if (p & 1) ret = 1LL * ret * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return ret;
}
inline void FWT(int *a, int n, int e) {
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += (k << 1)) {
            for (int j = 0; j < k; j++) {
                int x = a[i + j], y = a[i + j + k];
                a[i + j] = (x + y) % MOD;
                a[i + j + k] = (x - y + MOD) % MOD;
                if (e){
                    a[i + j] = 1LL * a[i + j] * INV % MOD;
                    a[i + j + k] = 1LL * a[i + j + k] * INV % MOD;
                }
            }
        }
    }
}
int d[MAXN], n, m, t;
int main() {
    shai();  // printf("%d\n", fuck(2, 10));
    // for(int i = 1;i <= 20;i++)D("%3d %s a prime.", i, vi[i] ? "is" : "isn't");
    while (~scanf("%d%d", &n, &m)) {
        t = 1;
        while (t <= m) t <<= 1;
        //D("DDD");
        for (int i = 0; i < t; i++) d[i] = vi[i] && i <= m;
        FWT(d, t, 0);
        for (int i = 0; i < t; i++) d[i] = fuck(d[i], n);
        FWT(d, t, 1);
        printf("%d\n", d[0]);
    }
    return 0;
}