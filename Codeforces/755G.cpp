#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 262145
#define MOD 998244353
#define G 3

inline void _add(int &a, int b){a += b;if(a >= MOD)a -= MOD;}
inline int add(int a, int b){return a + b >= MOD ? a + b - MOD : a + b;}
inline void _del(int &a, int b){a -= b;if(a < 0)a += MOD;}
inline int del(int a, int b){return a - b < 0 ? a - b + MOD : a - b;}
inline void _mul(int &a, int b){a = 1LL * a * b % MOD;}
inline int mul(int a, int b){return 1LL * a * b % MOD;}

#pragma region BASE
inline int pow(int x, int p){
    int r = 1;
    while(p){
        if(p & 1)_mul(r, x);
        _mul(x, x);
        p >>= 1;
    }
    return r;
}
int w[MAXN], inv[MAXN];
inline void PRE(int k){
    int n = k << 1;
    w[n] = 1; w[n + 1] = pow(G, (MOD - 1) / k); inv[1] = 1;
    for(int i = 2;i < n;i++)w[n + i] = mul(w[n + i - 1], w[n + 1]);
    for(int i = n - 1;i > 0;i--)w[i] = w[i << 1];
    for (int i = 2; i <= k; i++)inv[i] = mul(del(MOD, MOD / i), inv[MOD % i]);
}
inline void NTT(int *a, int n){
    for(int i = 1, j = 0;i < n - 1;i++){
        for(int t = n;~j & t;j ^= t)t >>= 1;
        if(i < j)std::swap(a[i], a[j]);
    }
    for(int k = 1;k < n;k <<= 1){
        int t = k << 1;
        for(int i = 0;i < n;i += t){
            for(int j = 0;j < k;j++){
                int x = a[i + j], y = mul(w[j], a[i + j + k]);
                a[i + j] = add(x, y);
                a[i + j + k] = del(x, y);
            }
        }
    }
}
#pragma endregion

#pragma region FUNC
inline void dft(int *a, int n){NTT(a, n);}
inline void idft(int *a, int n){
    NTT(a, n);
    std::reverse(a + 1, a + n);
    for(int i = 0, j = pow(n, MOD - 2);i < n;i++)_mul(a[i], j);
}
inline void drvt(int *a, int *b, int n){
    for(int i = 1;i < n;i++)b[i - 1] = mul(i, a[i]);
    b[n - 1] = 0;
}
inline void itgt(int *a, int *b, int n){
    for(int i = n - 1;i;i--)b[i] = mul(inv[i], a[i - 1]);
    b[0] = 0;
}
int tmp[MAXN];
inline void inverse(int *a, int *b, int n){
    memset(tmp, 0, sizeof(int) * n << 1);
    b[0] = pow(a[0], MOD - 2);
    for(int i = 4, j = 2;j <= n;j = i, i <<= 1){
        memcpy(tmp, a, sizeof(int) * j);
        memset(tmp + j, 0, sizeof(int) * (i - j));
        dft(tmp, i); dft(b, i);
        for(int k = 0;k < i;k++){
            
        }
    }
}
#pragma endregion

int main(){
    //
    return 0;
}