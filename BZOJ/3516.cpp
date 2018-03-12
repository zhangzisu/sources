#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cassert>
#define MOD 1000000007LL
#define MAXN 500010
long long n, m;
long long fpow(long long x, long long p){
    long long ret = 1;
    while(p){
        if(p & 1)(ret *= x) %= MOD;
        (x *= x) %= MOD;
        p >>= 1;
    }
    return ret;
}
long long frc[MAXN], inv[MAXN], f[MAXN];
inline long long C(long long n, long long m){return frc[n] * inv[m] % MOD * inv[n - m] % MOD;}

int main(){
    scanf("%lld%lld", &n, &m);
    if(m == 1)return printf("%lld", (n + 1) * n / 2 % MOD), 0;
    frc[0] = 1;
    for(int i = 1;i < MAXN;i++)frc[i] = frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fpow(frc[MAXN - 1], MOD - 2);
    for(int i = MAXN - 1;i;i--)inv[i - 1] = inv[i] * i % MOD;

    long long ini = fpow(m - 1, MOD - 2);
    f[0] = ((fpow(m, n + 1) - 1) * ini - 1) % MOD;
    if(f[0] < 0)f[0] += MOD;
    for(int i = 1;i <= m;i++){
        long long tmp = 0;
        for(int j = 0;j < i;j++){
            int k = ((i ^ j) & 1) ? -1 : 1;
            (tmp += C(i, j) * k * f[j] % MOD) %= MOD;
        }
        f[i] = (tmp + fpow(n, i) * fpow(m, n + 1) % MOD) % MOD;
        (f[i] *= ini) %= MOD;
        if(f[i] < 0)f[i] += MOD;
    }

    printf("%lld", f[m]);
    return 0;
}