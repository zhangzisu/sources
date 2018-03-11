#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 500010
int n, m, MOD;
inline int pow(int x, int p){
    int ret = 1;
    while(p){
        if(p & 1)ret = 1LL * ret * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return ret;
}
int frc[MAXN], inv[MAXN];
inline int C(int n, int m) { return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD; }

int main(){
    scanf("%d%d%d", &n, &m, &MOD);
    frc[0] = 1;
    for(int i = 1;i <= n;i++)frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[n] = pow(frc[n], MOD - 2);
    for(int i = n;i >= 1;i--)inv[i - 1] = 1LL * inv[i] * i % MOD;

    printf("%lld\n", 1LL * C(n - 1, m - 1) * pow(m, n - m - 1) % MOD * pow(n - m, m - 1) % MOD);

    return 0;
}