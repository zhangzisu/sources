#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 1300010
#define MOD 1004535809
inline long long fpow(long long n, long long p){
    long long ret = 1;
    while(p){
        if(p & 1)(ret *= n) %= MOD;
        (n *= n) %= MOD;
        p >>= 1;
    }
    return ret;
}
long long frc[MAXN], inv[MAXN];
long long A[MAXN], B[MAXN], C[MAXN];
inline void NTT(long long *a, int n, int e){
    for(int i = 1, j = 0;i < n - 1;i++){
        for(int t = n;~j & t;j ^= t)t >>= 1;
        if(i < j)std::swap(a[i], a[j]);
    }
    for(int k = 1;k < n;k <<= 1){
        int t = k << 1;
        long long wn = fpow(3, (MOD - 1) / t);
        for(int i = 0;i < n;i += t){
            long long w = 1;
            for(int j = 0;j < k;j++, w = w * wn % MOD){
                long long x = a[i + j], y = w * a[i + j + k] % MOD;
                a[i + j] = (x + y) % MOD;
                a[i + j + k] = (x - y) % MOD;
                if(a[i + j + k] < 0)a[i + j + k] += MOD;
            }
        }
    }
    if(e){
        std::reverse(a + 1, a + n);
        for(int i = 0, j = fpow(n, MOD - 2);i < n;i++)(a[i] *= j) %= MOD;
    }
}
inline void poinv(long long *a, long long *b, int N){
    if(N == 1)return void(b[0] = fpow(a[0], MOD - 2));
    poinv(a, b, (N >> 1) + (N & 1));
    static long long tmp[MAXN];
    int n = 1; memcpy(tmp, a, sizeof(long long) * N);
    while(n < (N << 1))n <<= 1;
    NTT(tmp, n, 0); NTT(b, n, 0);
    for(int i = 0;i < n;i++)b[i] = (2 - 1LL * tmp[i] * b[i] % MOD + MOD) % MOD * b[i] % MOD;
    NTT(b, n, 1); memset(b + N, 0, sizeof(long long) * (MAXN - N));
}
int n;
int main(){
    frc[0] = 1; scanf("%d", &n);
    for(int i = 1;i < MAXN;i++)frc[i] = frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fpow(frc[MAXN - 1], MOD - 2);
    for(int i = MAXN - 1;i;i--)inv[i - 1] = inv[i] * i % MOD;
    //
    for(int i = 0;i <= n;i++)A[i] = fpow(2, 1LL * i * (i - 1) / 2 % (MOD - 1)) * inv[i] % MOD;
    for(int i = 1;i <= n;i++)B[i] = fpow(2, 1LL * i * (i - 1) / 2 % (MOD - 1)) * inv[i - 1] % MOD;
    // for(int i = 0;i <= n;i++)printf("%d ", A[i]); puts("");
    // for(int i = 0;i <= n;i++)printf("%d ", B[i]); puts("");
    poinv(A, C, n + 1);
    int N = 1;
    while(N <= n + 1)N <<= 1;
    NTT(C, N, 0); NTT(B, N, 0);
    for(int i = 0;i < N;i++)(C[i] *= B[i]) %= MOD;
    NTT(C, N, 1);
    long long ans = C[n];
    (ans *= frc[n - 1]) %= MOD;
    printf("%lld\n", ans);
    return 0;
}