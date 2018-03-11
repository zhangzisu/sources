#include<cstdio>
#define MAXN 1000010
#define MOD 998244353
int n, q, m, a[MAXN], l, r;
long long ans;
int main(){
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1;i <= n;i++)scanf("%d", &a[i]);
    while(q--){
        scanf("%d%d", &l, &r);
        ans = 1LL * (r - l + 1) * (m - 1) % MOD;
        int llll = 0, Il = -1, ll = a[l];
        for(int I = l + 1;I <= r;I++){
            if(Il == a[I])llll++; else llll = 0;
            if(ll != a[I])(ans += 1LL * (r - l + 1) * (m - 1) % MOD - llll - 1) %= MOD;
            Il = ll; ll = a[I];
        }
        printf("%lld\n", ans);
    }
    return 0;
}