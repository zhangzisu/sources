#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<complex>
#define MAXN 1000010
#define MOD 998244353
#define G 3
inline int fuck(int x, int p){
    register int ret = 1;
    while(p){
        if(p & 1)ret = 1LL * ret * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return ret;
}
inline void FNT(int *a, int N, int e){
    for(int i = 1, j = 0;i < N - 1;i++){
        for(int t = N;~j & t;j ^= t)t >>= 1;
        if(i < j)std::swap(a[i], a[j]);
    }
    for(int i = 1;i < N;i <<= 1){
        int t = i << 1, wn = fuck(G, (MOD - 1) / t);
        for(int j = 0;j < N;j += t){
            for(int k = 0, w = 1;k < i;k++, w = 1LL * w * wn % MOD){
                int x = a[j + k], y = 1LL * w * a[j + k + i] % MOD;
                a[j + k] = (x + y) % MOD;
                a[j + k + i] = (x - y + MOD) % MOD;
            }
        }
    }
    if(e){
        std::reverse(a + 1, a + N);
        for(int i = 0, j = fuck(N, MOD - 2);i < N;i++)a[i] = 1LL * a[i] * j % MOD;
    }
}
int a[MAXN], b[MAXN], tmp[MAXN];
inline void poinv(int *a, int *b, int N){
    if(N == 1)return void(b[0] = fuck(a[0], MOD - 2));
    poinv(a, b, (N >> 1) + (N & 1));
    int n = 1; memcpy(tmp, a, sizeof(int) * N);
    while(n < (N << 1))n <<= 1;
    FNT(tmp, n, 0); FNT(b, n, 0);
    for(int i = 0;i < n;i++)b[i] = (2 - 1LL * tmp[i] * b[i] % MOD + MOD) % MOD * b[i] % MOD;
    FNT(b, n, 1); memset(b + N, 0, sizeof(int) * (MAXN - N));
    // puts("DDD");
    // for(int i = 0;i < N;i++)printf("%d ", a[i]);
    // puts("DDD");
}
int n, frc[MAXN], inv[MAXN], ans;
int main(){
    scanf("%d", &n), n++; frc[0] = a[0] = 1;
    for(int i = 1;i <= n;i++)frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[n] = fuck(frc[n], MOD - 2);
    for(int i = n;i >= 1;i--)inv[i - 1] = 1LL * inv[i] * i % MOD;
    for(int i = 1;i < n;i++)/*printf("DDD %d\n", */a[i] = ((MOD - inv[i]) << 1) % MOD/*)*/;
    poinv(a, b, n);
    /*printf("DDDD %d\n", */ans = b[n - 1]/*)*/;
    for(int i = n - 1;i;i--)ans = (1LL * ans * i % MOD + b[i - 1]) % MOD;
    printf("%d\n", ans);
    return 0;
}