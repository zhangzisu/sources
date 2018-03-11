#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 1000010
#define MOD 1000000007
inline long long fuck(long long x, long long p){
    long long ret = 1;
    while(p){
        if(p & 1)ret = ret * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return ret;
}
long long fb[MAXN], sb[MAXN], mu[MAXN], fi[MAXN], si[MAXN], vi[MAXN], pr[MAXN], cnt = 0;
inline void cao(){
    fb[0] = sb[0] = 0; fb[1] = sb[1] = 1; mu[1] = 1;
    for(long long i = 2;i < MAXN;i++){
        fb[i] = (fb[i - 1] + fb[i - 2]) % MOD; sb[i] = fuck(fb[i], MOD - 2);
        if(!vi[i]){ pr[++cnt] = i; mu[i] = -1; }
        for(long long j = 1;j <= cnt;j++){
            if(i * pr[j] >= MAXN)break;
            vi[i * pr[j]] = 1;
            if(!(i % pr[j]))break;
            mu[i * pr[j]] = -mu[i];
        }
    }
}
inline void kao(){
    std::fill(fi, fi + MAXN, 1);
    for(long long i = 1;i < MAXN;i++){
        for(long long j = 1;i * j < MAXN;j++){
            if(mu[j])fi[i * j] = fi[i * j] * (mu[j] == 1 ? fb[i] : sb[i]) % MOD;
        }
    }
    for(long long i = 1;i < MAXN;i++)fi[i] = fi[i] * fi[i - 1] % MOD;
    for(long long i = 0;i < MAXN;i++)si[i] = fuck(fi[i], MOD - 2);
}
int main(){
    cao(); kao();
    // for(long long i = 1;i <= 10;i++)printf("DDD %d %d\n", fi[i], si[i]);
    long long t, n, m; scanf("%lld", &t);
    while(t--){
        scanf("%lld%lld", &n, &m);
        long long ans = 1;
        for(long long i = 1, j;i <= n && i <= m;i = j + 1){
            j = std::min(n / (n / i), m / (m / i));
            ans = ans * fuck(fi[j] * si[i - 1] % MOD, (n / i) * (m / i)) % MOD;
        }
        printf("%lld\n", (ans + MOD) % MOD);
    }
    return 0;
}