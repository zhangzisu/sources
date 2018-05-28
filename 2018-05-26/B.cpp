#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 200010
int n, a[MAXN], d[MAXN][20];
long long res = 0;
int main(){
    scanf("%d", &n);
    for(int i = 1;i <= n;i++)scanf("%d", &a[i]);
    for(int i = 1;i <= n;i++){
        for(int j = 0;j < 20;j++){
            d[i][j] = d[i - 1][j] + ((a[i] >> j) & 1);
        }
    }
    for(int i = 1;i <= n;i++){
        int l = i, r = n, ans = i;
        while(l <= r){
            int mid = (l + r) >> 1;
            int ok = true;
            for(int j = 0;j < 20;j++){
                if(d[mid][j] - d[i - 1][j] > 1){
                    ok = false;
                    break;
                }
            }
            if(ok)ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        res += ans - i + 1;
    }
    printf("%lld\n", res);
    return 0;
}