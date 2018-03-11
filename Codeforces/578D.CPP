#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<algorithm>
int n, m, tmp = 0;
long long ans = 0;
inline char next(){
    register char ch = getchar();
    while(!isalpha(ch))ch = getchar();
    return ch;
}
int main(){
    scanf("%d%d", &n, &m);
    ans = 1LL * n * (m - 1);
    register char ch = getchar(), prr = -1, pr = next();
    for(int i = 2;i <= n;i++){
        ch = next();
        if(ch == prr)tmp++; else tmp = 0;
        if(ch != pr)ans += 1LL * n * (m - 1) - tmp - 1;
        prr = pr; pr = ch;
    }
    printf("%lld\n", ans);
    return 0;
}