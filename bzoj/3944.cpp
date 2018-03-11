#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#define MAXN 2000000
std::map<unsigned, long long> M0, M1;
int vi[MAXN], pr[MAXN], cnt = 0;
long long ph[MAXN], mu[MAXN];
inline void shai(){
    ph[1] = 1; mu[1] = 1;
    for(int i = 2;i < MAXN;i++){
        if(!vi[i])pr[++cnt] = i, ph[i] = i - 1, mu[i] = -1;
        for(int j = 1;j <= cnt;j++){
            if(i * pr[j] >= MAXN)break;
            vi[i * pr[j]] = 1;
            if(i % pr[j]){
                mu[i * pr[j]] = -mu[i];
                ph[i * pr[j]] = ph[i] * (pr[j] - 1);
            }else{
                mu[i * pr[j]] = 0;
                ph[i * pr[j]] = ph[i] * pr[j];
                break;
            }
        }
    }
    for(int i = 1;i < MAXN;i++){
        ph[i] += ph[i - 1];
        mu[i] += mu[i - 1];
    }
}
long long D0(unsigned x){
    if(x < MAXN)return ph[x];
    if(M0.count(x))return M0[x];
    long long ret = 1LL * x * (x + 1) >> 1;
    for(unsigned i = 2, j;i <= x;i = j + 1){
        j = x / (x / i);
        ret -= 1LL * (j - i + 1) * D0(x / i);
    }
    return M0[x] = ret;
}
long long D1(unsigned x){
    if(x < MAXN)return mu[x];
    if(M1.count(x))return M1[x];
    long long ret = 1LL;
    for(unsigned i = 2, j;i <= x;i = j + 1){
        j = x / (x / i);
        ret -= 1LL * (j - i + 1) * D1(x / i);
    }
    return M1[x] = ret;
}
unsigned n, m;
int main(){
    shai();//scanf("%u", &n);
    printf("%lld\n", D0(100000000));
    return 0;
}