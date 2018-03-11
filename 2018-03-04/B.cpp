#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MOD 998244353
namespace PA{
    const int MAXN = 1010;
    int a[MAXN], n, m;
    inline int main(){
        scanf("%d%d", &n, &m);
        for(int i = 1;i <= n;i++)scanf("%d", &a[i]);
        while(m--){
            int l, r, x; scanf("%d", &x);
            if(x == 1){
                scanf("%d%d%d", &l ,&r, &x);
                for(int i = l;i <= r;i++)a[i] = x;
            }else if(x == 2){
                scanf("%d%d", &l, &r);
                for(int i = l;i <= r;i++)a[i] = -a[i];
            }else if(x == 3){
                scanf("%d%d", &l, &r);
                std::reverse(a + l, a + r + 1);
            }else{
                scanf("%d%d", &l, &r);
                int sum = 0, min = 0x7FFFFFFF, max = 0x80000000, xxx = 1;
                for(int i = l;i <= r;i++){
                    (sum += a[i]) %= MOD;
                    min = std::min(min, a[i]);
                    max = std::max(max, a[i]);
                    xxx = 1LL * xxx * a[i] % MOD;
                }
                ((sum %= MOD) += MOD) %= MOD;
                ((min %= MOD) += MOD) %= MOD;
                ((max %= MOD) += MOD) %= MOD;
                ((xxx %= MOD) += MOD) %= MOD;
                printf("%d %d %d %d\n", sum, max, min, xxx);
                std::sort(a + l, a + r + 1);
            }
        }
        return 0;
    }
}
int main(){
    PA::main();
    return 0;
}