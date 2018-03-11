#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 2000050
long long n, sn, f[MAXN][2], mn[MAXN], ct[2];
int vi[MAXN], pr[MAXN], pos[2][MAXN], cnt = 0, pnt = 0;
inline int& p(long long x){ return x <= sn ? pos[0][x] : pos[1][n / x]; }
inline void shai(){
    for(int i = 2;i <= sn;i++){
        if(!vi[i]){pr[++cnt] = i;}
        for(int j = 1;j <= cnt;j++){
            if(i * pr[j] > sn)break;
            vi[i * pr[j]] = 1;
            if(!(i % pr[j]))break;
        }
    }
    for(long long i = 1, j;i <= n;i = j + 1){
        j = n / (n / i);
        mn[p(n / i) = ++pnt] = n / i;
        f[pnt][0] = (n / i + 1) / 4;
        f[pnt][1] = (n / i + 3) / 4 - 1;
        //printf("[%d - %d]\n", i, j);
    }
}

int main(){
    scanf("%lld", &n); sn = sqrt(n); shai();
    for(int i = 2;i <= cnt;i++){
        long long p2 = (long long)pr[i] * pr[i];
        int d = (pr[i] & 3) == 1;
        for(int j = 1;j <= pnt && mn[j] >= p2;j++){
            int pre = p(mn[j] / pr[i]);
            //printf("PAG!!! %lld %lld, %lld %lld, %lld\n", f[j][0], f[j][1], mn[j], pr[i], pre);
            //printf("FSB!!! %lld %lld\n", f[pre][d ^ 1], f[pre][d]);
            /*printf("DDD!!! %lld\n", */f[j][0] -= f[pre][d ^ 1] - ct[d ^ 1]/*)*/;
            /*printf("DDD!!! %lld\n", */f[j][1] -= f[pre][d] - ct[d]/*)*/;
        }
        ct[d]++;
    }
    //printf("D : %lld %lld\n", ct[0], ct[1]);
    printf("%lld\n", f[1][1]);
    return 0;
}