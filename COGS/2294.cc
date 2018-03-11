#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 262200
#define L long

const L L mod[] = {998244353, 1004535809, 469762049};
const L L G = 3;
const L L CCF = 23333333;
inline L L fuck(L L x, L L p, L L MOD){
    L L ret = 1;
    while(p){
        if(p & 1)ret = ret * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return ret;
}
inline void NTT(L L *a, int n, int e, int MOD){
    for(L L i = 0;i < n;i++)a[i] %= MOD;
    for(L L i = 1, j = 0;i < n - 1;i++){
        for(L L t = n;~j & t;j ^= t)t >>= 1;
        if(i < j)std::swap(a[i], a[j]);
    }
    for(L L i = 1;i < n;i <<= 1){
        L L t = i << 1, wn = fuck(G, (MOD - 1) / t, MOD);
        for(L L j = 0;j < n;j += t){
            for(L L k = 0, w = 1;k < i;k++, w = w * wn % MOD){
                L L x = a[j + k], y = w * a[j + k + i] % MOD;
                a[j + k] = (x + y) % MOD;
                a[j + k + i] = (x - y + MOD) % MOD;
            }
        }
    }
    if(e){
        std::reverse(a + 1, a + n);
        for(L L i = 0, j = fuck(n, MOD - 2, MOD);i < n;i++)a[i] = a[i] * j % MOD;
    }
}
inline L L kao(L L a, L L b, L L MOD){
    a %= MOD; b %= MOD;
    return ((a * b - ((L L)((L double)a / MOD * b + 1e-3)) * MOD) % MOD + MOD) % MOD;
}
inline L L cao(L L a0, L L a1, L L a2){
    L L m = mod[0] * mod[1];
    L L t =
    (
        kao(a0 * mod[1] % m, fuck(mod[1] % mod[0], mod[0] - 2, mod[0]), m) +
        kao(a1 * mod[0] % m, fuck(mod[0] % mod[1], mod[1] - 2, mod[1]), m)
    ) % m;
    L L k = ((a2 - t) % mod[2] + mod[2]) % mod[2] * fuck(m % mod[2], mod[2] - 2, mod[2]) % mod[2];
    return (((k % CCF) * (m % CCF) % CCF + t % CCF) % CCF + CCF) % CCF;
}
L L n, m = 1, a[MAXN], b[MAXN], c[MAXN], d[MAXN], e[3][MAXN];
int main(){
    scanf("%lld", &n);
    while(m < (n << 1))m <<= 1;
    for(int i = 0;i < n;i++)scanf("%lld", &a[i]);
    for(int i = 0;i < n;i++)scanf("%lld" ,&b[i]);
    memcpy(c, a, sizeof(c)); memcpy(d, b, sizeof(d));
    NTT(c, m, 0, mod[0]); NTT(d, m, 0, mod[0]);
    for(int i = 0;i < m;i++)/*printf("D0 : %15lld\n", */e[0][i] = c[i] * d[i] % mod[0]/*)*/;
    memcpy(c, a, sizeof(c)); memcpy(d, b, sizeof(d));
    NTT(c, m, 0, mod[1]); NTT(d, m, 0, mod[1]);
    for(int i = 0;i < m;i++)/*printf("D1 : %15lld\n", */e[1][i] = c[i] * d[i] % mod[1]/*)*/;
    memcpy(c, a, sizeof(c)); memcpy(d, b, sizeof(d));
    NTT(c, m, 0, mod[2]); NTT(d, m, 0, mod[2]);
    for(int i = 0;i < m;i++)/*printf("D2 : %15lld\n", */e[2][i] = c[i] * d[i] % mod[2]/*)*/;
    NTT(e[0], m, 1, mod[0]); NTT(e[1], m, 1, mod[1]); NTT(e[2], m, 1, mod[2]);
    for(int i = 0;i < n;i++)printf("%lld\n", cao(e[0][i], e[1][i], e[2][i]));
    return 0;
}