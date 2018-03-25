#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 50010
int vis[MAXN], pr[MAXN], mu[MAXN], pnt = 0;
inline void shai(){
    mu[1]=1;
    for(int i=2;i<MAXN;i++){
        if(!vis[i])pr[++pnt]=i,mu[i]=-1;
        for(int j=1;j<=pnt;j++){
            if(i*pr[j]>=MAXN)break;
            vis[i*pr[j]]=1;
            if(i%pr[j]){
                mu[i*pr[j]]=-mu[i];
            }else{
                mu[i*pr[j]]=0;
                break;
            }
        }
    }
    for(int i = 2;i<MAXN;i++)mu[i] += mu[i-1];
}
int n, a, b, d, ans;
int main(){
    shai();
    scanf("%d", &n);
    while(n--){
        scanf("%d%d%d", &a, &b, &d);
        ans = 0;
        a /= d;
        b /= d;
        for(int i = 1, j;i <= a && i <= b;i = j + 1){
            j = std::min(a / (a / i), b / (b / i));
            ans += (a / i) * (b / i) * (mu[j] - mu[i - 1]);
        }
        printf("%d\n", ans);
    }
    return 0;
}