#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 100010
#define EPS 1e-8
int n;
double w[MAXN], pfx[MAXN], ans[MAXN], t;
int main(){
    scanf("%d%lf", &n, &t);
    for(int i = 1;i <= n;i++)scanf("%lf", &w[i]);
    int now = 0; ans[1] = 0;
    int lim = std::min(2000, n);
    for(int i = 1;i <= lim;i++){
        while(1. + now <= t * i + EPS)now++;
        for(int j = 1;j <= now;j++)ans[i] += w[j] * w[i] / (i - j);
    }
    for(int i = 1;i <= n;i++)pfx[i] = pfx[i - 1] + w[i];
    for(int i = lim + 1;i <= n;i++){
        while(1. + now <= t * i + EPS)now++;
        ans[i] = pfx[now] * w[i] / (i - now / 2);
    }
    for(int i = 1;i <= n;i++)printf("%.10f\n", ans[i]);
    return 0;
}