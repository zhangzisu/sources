#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
int n, d[300010], ct[300010], tc[300010], ans = 300010;
char buf[300010];
int main(){
    scanf("%d%s", &n, buf + 1);
    for(int i = 1;i <= n;i++){
        d[i] = buf[i] == 'W';
    }
    for(int i = 1;i <= n;i++)ct[i] = ct[i - 1] + d[i];
    for(int i = n;i >= 1;i--)tc[i] = tc[i + 1] + !d[i];
    for(int i = 1;i <= n;i++){
        ans = std::min(ans, ct[i - 1] + tc[i + 1]);
    }
    printf("%d\n", ans);
    return 0;
}