#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<bitset>
#define MAXN 10000010
int is[MAXN], u[MAXN], g[MAXN];
int prime[5000010], cnt = 0;
long long pfx[MAXN];
inline void shai(int n){
    u[1] = 1;
    for(int i = 2;i <= n;i++){
        if(!is[i]){prime[++cnt] = i; u[i] = -1; g[i] = 1;}
        for(int j = 1;j <= cnt;j++){
            if(prime[j] * i > n)break;
            is[prime[j] * i] = 1;
            if(i % prime[j]){
                u[i * prime[j]] = -u[i];
                g[i * prime[j]] = u[i] - g[i];
            }else{
                u[i * prime[j]] = 0;
                g[i * prime[j]] = u[i];
                break;
            }
        }
    }
    for(int i = 1;i <= n;i++)pfx[i] = pfx[i - 1] + g[i];
}
int n;
long long ans = 0;
int main(){
    scanf("%d", &n); shai(n);
    for(int i = 1, j;i <= n;i = j + 1){
        j = n / (n / i);
        ans += (long long)(n / i) * (n / i) * (pfx[j] - pfx[i - 1]);
        // printf("%lld\n", ans);
    }
    printf("%lld\n", ans);
    return 0;
}