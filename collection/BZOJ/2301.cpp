#include<cstdio>
#include<algorithm>
#define MAXN 10000010
int vis[MAXN], mu[MAXN], pfx[MAXN], pr[2000000], cnt = 0;
inline void shai(){
    mu[1] = 1;
    for(int i = 2;i < MAXN;i++){
        if(!vis[i]){
            mu[i] = -1; pr[++cnt] = i;
        }
        for(int j = 1;j <= cnt;j++){
            if(i * pr[j] >= MAXN)break;
            vis[i * pr[j]] = 1;
            if(i % pr[j]){
                mu[i * pr[j]] = -mu[i];
            }else{
                mu[i * pr[j]] = 0; break;
            }
        }
    }
    for(int i = 1;i < MAXN;i++)pfx[i] = pfx[i - 1] + mu[i];
}
inline long long calc(int n, int m){
    long long ans = 0;
    for(int i = 1, j;i <= n && i <= m;i = j + 1){
        j = std::min(n / (n / i), m / (m / i));
        ans += (long long)(n / i) * (m / i) * (pfx[j] - pfx[i - 1]);
    }
    // printf("%3d %3d => %lld\n", n, m, ans);
    return ans;
}
int n;
int main(){
    shai();
    scanf("%d", &n);
    while(n--){
        int a, b, c, d, k;
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        printf(
            "%lld\n",
            calc(b / k, d / k) - calc((a - 1) / k, d / k) -
            calc(b / k, (c - 1) / k) + calc((a - 1) / k, (c - 1) / k)
        );
    }
    return 0;
}