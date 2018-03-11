#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 1000010
#define $ long
#define _ inline void
$ vis[MAXN], pri[MAXN], fir[MAXN], cnt = 0;
$ $ G0[MAXN], G1[MAXN], F0[MAXN], F1[MAXN], FFF[MAXN];
_ shai(){
    fir[1] = 1; FFF[1] = 1;
    for($ i = 2;i < MAXN;i++){
        if(!vis[i])pri[++cnt] = i, fir[i] = i, FFF[i] = 4;
        for($ j = 1;j <= cnt;j++){
            if(i * pri[j] >= MAXN)break;
            vis[i * pri[j]] = 1;
            if(i % pri[j]){
                FFF[i * pri[j]] = FFF[i] << 2;
                fir[i * pri[j]] = pri[j];
            }else{
                if(i / fir[i] == 1)FFF[i * pri[j]] = FFF[i] + 3;
                else FFF[i * pri[j]] = FFF[i / fir[i]] * FFF[fir[i] * pri[j]];
                fir[i * pri[j]] = fir[i] * pri[j];
                break;
            }
        }
    }
}
$ $ n, L0[MAXN], L1[MAXN], CP[MAXN];
_ G($ $ n, $ sn, $ sp){
    // printf("%ld %ld %lld\n", sn, sp, n);
    for($ i = 1;i < sn;i++)G0[i] = i, G1[i] = n / i;
    for($ i = 1;i < sp;i++){
        for($ j = 1;j < sn && i < L1[j];j++){
            $ $ y = n / j / pri[i];
            G1[j] -= (y < sn ? (G0[y] - std::max(0LL, std::min(($ $)i, CP[y]) - L0[y])) : (G1[n / y] - std::max(0LL, i - L1[n / y])));
        }
        for($ j = sn - 1;j >= 1 && i < L0[j];j--){
            $ $ y = j / pri[i];
            G0[j] -= (G0[y] - std::max(0LL, std::min(($ $)i, CP[y]) - L0[y]));
        }
    }
    for($ i = 1;i < sn;i++){
        // printf("<-%%%%%% %lld %lld\n" ,G0[i], G1[i]);
        (G0[i] -= CP[i] - L0[i] + 1) *= 4;
        (G1[i] -= std::max(0LL, sp - L1[i]) + 1) *= 4;
    }
}
_ F($ $ n, $ sn, $ sp){
    for($ i = 1;i < sn;i++)F0[i] = F1[i] = 1;
    for($ i = sp - 1;i >= 1;i--){
        for($ j = 1;j < sn && i < L1[j];j++){
            $ $ y = n / j / pri[i];
            for($ k = 1;y;k++, y /= pri[i]){
                F1[j] += (3 * k + 1) * (y < sn ? (F0[y] + (std::max(0LL, CP[y] - std::max(i + 1LL, L0[y])) << 2)) : (F1[n / y] + (std::max(0LL, sp - std::max(i + 1LL, L1[n / y])) << 2)));
            }
        }
        for(int j = sn - 1;j >= 1 && i < L0[j];j--){
            $ $ y = j / pri[i];
            for($ k = 1;y;k++, y /= pri[i]){
                F0[j] += (3 * k + 1) * (F0[y] + (std::max(0LL, CP[y] - std::max(i + 1LL, L0[y])) << 2));
            }
        }
    }
    for($ i = 1;i < sn;i++){
        F0[i] += std::max(0LL, CP[i] - L0[i]) << 2;
        F1[i] += (sp - L1[i]) << 2;
    }
}
_ _main(){
    scanf("%lld", &n);
    $ sn = 0, sp = 1;
    while(($ $)sn * sn <= n)sn++;
    while(($ $)pri[sp] * pri[sp] <= n)sp++;
    L0[0] = 0;
    for($ i = 1;i < sn;i++){
        for(L0[i] = L0[i - 1];($ $)pri[L0[i]] * pri[L0[i]] <= i;L0[i]++);
    }
    L1[sn] = 0;
    for($ i = sn - 1;i >= 1;i--){
        $ $ x = n / i;
        for(L1[i] = L1[i + 1];($ $)pri[L1[i]] * pri[L1[i]] <= x;L1[i]++);
    }
    CP[0] = 0;
    for($ i = 1;i < sn;i++){
        for(CP[i] = CP[i - 1];pri[CP[i]] <= i;++CP[i]);
    }
    G(n, sn, sp); F(n, sn, sp);
    $ $ ans = F1[1];
    // printf("DBG %lld\n", ans);
    // for($ i = 1;i < sn;i++)printf("[D]--[D] %lld\n", G1[i]);
    for($ i = 1;i < sn;i++)ans += FFF[i] * G1[i];
    printf("%lld\n", ans);
}
int main(){
    shai(); $ t; scanf("%ld", &t);
    while(t--)_main();
    return 0;
}