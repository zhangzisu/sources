#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MOD 20101009
#define MAXN 10000010
int vis[MAXN], mu[MAXN], pfx[MAXN], pr[1500000], cnt = 0;
inline void shai(int n){
    mu[1] = 1;
    for(register int i = 2;i <= n;i++){
        if(!vis[i]){mu[i] = -1; pr[++cnt] = i;}
        for(register int j = 1;j <= cnt;j++){
            if(i * pr[j] > n)break;
            vis[i * pr[j]] = 1;
            if(i % pr[j]){mu[i * pr[j]] = -mu[i];}
            else {mu[i * pr[j]] = 0; break;}
        }
    }
    for(register int i = 1;i <= n;i++)pfx[i] = (1LL * i * i % MOD * mu[i] % MOD + pfx[i - 1]) % MOD;
}
inline int sum(int n, int m){
    return (1LL * n * (n + 1) / 2 % MOD) * (1LL * m * (m + 1) / 2 % MOD) % MOD;
}
inline int F(int n, int m){
    register int ans = 0;
    for(register int i = 1, j;i <= n && i <= m;i = j + 1){
        j = std::min(n / (n / i), m / (m / i));
        (ans += 1LL * sum(n / i, m / i) * (pfx[j] - pfx[i - 1]) % MOD) %= MOD;
    }
    return ans;
}
int main(){
    register int n, m, ans = 0;
    scanf("%d%d", &n, &m); shai(std::min(n, m));
    for(register int i = 1, j;i <= n && i <= m;i = j + 1){
        j = std::min(n / (n / i), m / (m / i));
        (ans += 1LL * (j - i + 1) * (i + j) / 2 % MOD * F(n / i, m / i) % MOD) %= MOD;
    }
    printf("%d\n", (ans + MOD) % MOD);
    return 0;
}