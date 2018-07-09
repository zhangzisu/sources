#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 5000010
#define MOD 998244353
#define G 3

inline int fuck(int x, int p){
    register int ret = 1;
    while(p){
        if(p & 1)ret = 1LL * x * ret % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return ret;
}
inline void NTT(int *a, int n, int e){
    for(int i = 1, j = 0;i < n - 1;i++){
        for(int t = n;~j & t;j ^= t)t >>= 1;
        if(i < j)std::swap(a[i], a[j]);
    }
    for(int k = 1;k < n;k <<= 1){
        int t = k << 1, fucker = fuck(G, (MOD - 1) / t);
        for(int i = 0;i < n;i += t){
            for(int j = 0, fucked = 1;j < k;j++, fucked = 1LL * fucked * fucker % MOD){
                int x = a[i + j], y = 1LL * fucked * a[i + j + k] % MOD;
                a[i + j] = (x + y) % MOD;
                a[i + j + k] = (x - y + MOD) % MOD;
            }
        }
    }
    if(e){
        std::reverse(a + 1, a + n);
        for(int i = 0, fucker = fuck(n, MOD - 2);i < n;i++)
            a[i] = 1LL * a[i] * fucker % MOD;
    }
}
int base[MAXN], copy[MAXN], val[MAXN];
int n;
int main(){
    for(int i = 0;i < 100000;i++)base[i] = val[i] = copy[i] = fuck(100000, MOD - 2);
    scanf("%d", &n);
    if(n == 1){
        double x; scanf("%lf", &x);
        int d = (int)(x * 100000);
        return printf("%lld\n", 1LL * d * fuck(100000, MOD - 2) % MOD), 0;
    }
    if(n == 2){
        double x; scanf("%lf", &x);
        int d0 = (int)(x * 100000);
        int ans = 1LL * d0 * fuck(100000, MOD - 2) % MOD;
        scanf("%lf" ,&x);
        int d1 = (int)(x * 100000);
        ans = 1LL * ans * (d0 + 100000) % MOD * fuck(2, MOD - 2) % MOD * fuck(d1, MOD - 2) % MOD;
        return printf("%d\n", ans);
    }
    for(int i = 1, m;i <= n;i++){
        double x; scanf("%lf", &x);
        m = std::min(int(x * 100000), i * 100000);
        if(i == n){
            int ans = 0;
            for(int i = 0;i < m;i++)ans = (0LL + ans + val[i]) % MOD;
            return printf("%d\n", ans), 0;
        }
        //std::fill(val + m, val + MAXN, 0);
        memcpy(base, copy, sizeof(copy));
        int t = 1;
        while(t <= m * 2)t <<= 1;
        printf("DDD !!! %d\n", t);
        NTT(base, t, 0); NTT(val, t, 0);
        for(int i = 0;i < t;i++)val[i] = 1LL * val[i] * base[i] % MOD;
        NTT(val, t, 1);
    }
    return 0;
}