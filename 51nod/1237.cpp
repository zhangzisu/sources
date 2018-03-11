#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define MAXN 5000000
#define MOD 1000000007
#define IV2 500000004
int vi[MAXN], pr[MAXN], fi[MAXN], cnt = 0;
long long pi[MAXN], px[MAXN];
inline void shai(){
    pi[1] = px[1] = 1;
    for(int i = 2;i < MAXN;i++){
        if(!vi[i])pr[++cnt] = i, pi[i] = i - 1;
        (px[i] = px[i - 1] + pi[i]) %= MOD;
        for(int j = 1;j <= cnt;j++){
            if(i * pr[j] >= MAXN)break;
            vi[i * pr[j]] = 1;
            if(i % pr[j]){
                pi[i * pr[j]] = pi[i] * (pr[j] - 1);
            }else{
                pi[i * pr[j]] = pi[i] * pr[j]; break;
            }
        }
    }
}
std::map<long long, long long> M;
 inline long long phi(long long x){
     if(x < MAXN)return px[x];
     if(M.count(x))return M[x];
     long long ret = x % MOD * (x % MOD + 1) % MOD * IV2 % MOD;
     for(long long i = 2, j;i <= x;i = j + 1){
         j = x / (x / i);
         ret -= (j - i + 1) * phi(x / i) % MOD;
     }
     ((ret %= MOD) += MOD) %= MOD;
     return M[x] = ret;
}
long long n, ans, pre, now, t0 ,t1;
int main(){
    shai();
    scanf("%lld", &n);
    for(long long i = 1, j;i <= n;i = j + 1){
        j = n / (n / i);
        now = phi(j);
        t0 = (((now - pre) % MOD) + MOD) % MOD;
        t1 = (n / i) % MOD;
        (ans += t0 * t1 % MOD * t1 % MOD) %= MOD;
        pre = now;
    }
    printf("%lld\n", ans);
    return 0;
}