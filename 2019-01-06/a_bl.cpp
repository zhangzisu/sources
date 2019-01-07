#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
typedef long long lnt;
int main() {
    int t;
    for(scanf("%d", &t);t;t--){
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        lnt ans=0;
        for(int i=1;i<=n;i++){
            lnt r=1,g=1;
            for(int j=1;j<=k;j++){
                (g*=i)%=m;
                (r+=g)%=m;
            }
            (r*=n/i)%=m;
            (ans+=r)%=m;
        }
        printf("%lld\n", ans);
    }
    return 0;
}