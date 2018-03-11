#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#define MOD 998244353
#define MAXK 100010
int n, k;
int f[3][MAXK], frac[MAXK];
int main(){
    scanf("%d%d", &n, &k);
    frac[0] = 1;
    for(int i = 1;i <= k;i++)frac[i] = 1LL * frac[i - 1] * i % MOD;
    f[0][0] = 1;
    for(int i = 1;i <= n;i++){
        f[i % 3][0] = 1;
        for(int j = 1;j <= n && j <= k;j++){
            f[i % 3][j] = (0LL + f[(i + 2) % 3][j] + f[(i + 2) % 3][j - 1] + (i > 1 ? f[(i + 1) % 3][j - 1] : 0)) % MOD;
        }
    }
    for(int i = 1;i <= k;i++)printf("%lld ", 1LL * f[n % 3][i] * frac[i] % MOD);
    return puts(""), 0;
}