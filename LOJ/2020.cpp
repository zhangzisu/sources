#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 5000010
#define MOD 998244353
#define G 3
int n, m;
int x[MAXN], y[MAXN], a[MAXN], b[MAXN];
inline int fuck(int x, int p){
    int ret = 1;
    while(p){
        if(p & 1)ret = 1LL * ret * x % MOD;
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
        int t = k << 1;
        int fucker = fuck(G, (MOD - 1) / t);
        for(int i = 0;i < n;i += t){
            int fucked = 1;
            for(int j = 0;j < k;j++, fucked = 1LL * fucked * fucker % MOD){
                int x = a[i + j], y = 1LL * fucked * a[i + j + k] % MOD;
                a[i + j] = (x + y) % MOD;
                a[i + j + k] = (x - y + MOD) % MOD;
            }
        }
    }
    if(e){
        std::reverse(a + 1, a + n);
        for(int i = 0, fucked = fuck(n, MOD - 2);i < n;i++)a[i] = 1LL * a[i] * fucked % MOD;
    }
}

long long sx, sy, s2x, s2y, delta, ans = 0x3F3F3F3F3F3F3F3FLL;
int main(){
    scanf("%d%d", &n, &m);
    for(int i = 0;i < n;i++)scanf("%d", &x[i]), sx += x[i], s2x += 1LL * x[i] * x[i];
    for(int i = 0;i < n;i++)scanf("%d", &y[i]), sy += y[i], s2y += 1LL * y[i] * y[i];
    delta = sx - sy;
    memcpy(a, x, sizeof(a)); memcpy(b, y, sizeof(b));
    for(int i = 0;i < n;i++)a[i + n] = a[i];
    std::reverse(b, b + n);
    int t = 1;
    while(t <= (n << 2))t <<= 1;
    NTT(a, t, 0); NTT(b, t, 0);
    for(int i = 0;i < t;i++)a[i] = 1LL * a[i] * b[i] % MOD;
    NTT(a, t, 1);
    //for(int i = 0;i < t;i++)printf("%d ", a[i]);
    //puts("");
    for(int i = 0;i < n;i++){
        int pos = n + i + 1, val = a[pos];
        for(long long gol = -m;gol <= m;gol++){
            long long result = s2x + s2y + gol * gol * n + gol * delta * 2 - 2 * val;
            ans = std::min(ans, result);
        }
    }
    printf("%lld\n", ans);
    return 0;
}