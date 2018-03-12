#include<cstdio>
#include<algorithm>
#include<map>
#define MAXN 1000010
#define MOD 1000000007
int ph[MAXN], vi[MAXN], pr[MAXN], fr[MAXN], cnt = 0;
int pfx[MAXN];
inline void shai(){
    ph[1] = fr[1] = pfx[1] = 1;
    for(int i = 2;i < MAXN;i++){
        if(!vi[i])pr[++cnt] = i, ph[i] = i - 1, fr[i] = 1;
        (pfx[i] += pfx[i - 1] + ph[i]) %= MOD;
        for(int j = 1;j <= cnt;j++){
            if(i * pr[j] >= MAXN)break;
            vi[i * pr[j]] = 1;
            if(i % pr[j]){
                ph[i * pr[j]] = ph[i] * ph[pr[j]];
                fr[i * pr[j]] = fr[i];
            }else{
                ph[i * pr[j]] = ph[i] * pr[j];
                fr[i * pr[j]] = fr[i] * pr[j];
                break;
            }
        }
    }
}

std::map<int, int> M0;
int f(int n){
    if(n < MAXN)return pfx[n];
    if(M0.count(n))return M0[n];
    int ret = (1LL * n * (n + 1) >> 1) % MOD;
    for(int i = 2, j;i <= n;i = j + 1){
        j = n / (n / i);
        ((ret -= 1LL * f(n / i) * (j - i + 1) % MOD) += MOD) %= MOD;
    }
    return M0[n] = ret;
}
inline unsigned long long hash(int n, int m){
    return (unsigned long long)n * MOD + m;
}
std::map<unsigned long long, int> M1;
int d(int n, int m){
    if(!n || !m)return 0;
    if(n == 1)return f(m);
    unsigned long long key = hash(n, m);
    if(M1.count(key))return M1[key];
    int ret = 0;
    for(int i = 1;i * i <= n;i++){
        if(n % i)continue;
        (ret += 1LL * ph[n / i] * d(i, m / i) % MOD) %= MOD;
        if(i * i == n)continue;
        (ret += 1LL * ph[i] * d(n / i, m / (n / i)) % MOD) %= MOD;
    }
    return M1[key] = ret;
}
int n, m, ans;
int main(){
    scanf("%d%d", &n, &m);shai();
    for(int i = 1;i <= n;i++){
        (ans += 1LL * fr[i] * d(i / fr[i], m) % MOD) %= MOD;
        //printf("FINISHED %3d. S_M0 = %5lu. S_M1 = %5lu.\n", i, M0.size(), M1.size());
    }
    printf("%d\n", ans);
    return 0;
}