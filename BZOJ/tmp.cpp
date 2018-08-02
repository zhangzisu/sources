#include <stdio.h>

typedef long long LL;
const int N=150005;

int prime[N/10],map[N+5],cnt;
bool not_prime[N];
int n,x,i,j;
LL ans=0;

__attribute__((optimize("O2")))
int main(void) {
    scanf("%d",&n);
    for (i=2;i<=n;i++) {
        if (!not_prime[i]) prime[++cnt]=i;
        for (j=1;j<=cnt&&i*prime[j]<=n;j++) {
            not_prime[i*prime[j]]=1;
            if (i%prime[j]==0) break;
        }
    }
    for (i=1;i<=cnt&&(prime[i]<<1)<=n;i++) {
        for (j=i+1;j<=cnt&&prime[i]+prime[j]<=n;j++) {
            map[prime[i]+prime[j]]+=2;
        }
        map[prime[i]<<1]++;
    }
    for (i=(n>>1);i;i--) ans+=map[i]*map[n-i]*2;
    if (!(n&1)) ans-=map[n>>1]*map[n>>1];
    printf("%lld", ans);
    return 0;
}