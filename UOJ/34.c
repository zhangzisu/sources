#include<cstdio>
#include<cctype>
#define MAXN 1000100
#define MOD 998244353
#define G 3

const int __ = 1 << 16;
char _1[__], _2[__], *_3 = _1 + __, *_4 = _2;
inline char gc() { if (_3 == _1 + __)fread(_1, 1, __, stdin), _3 = _1; return *_3++; }
inline int _() {
    register int x = 0; register char ch = gc();
    while(!isdigit(ch))ch = gc();
    for(;isdigit(ch);ch = gc())x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
inline void _(char c) { if (_4 == _2 + __)fwrite(_2, 1, __, stdout), _4 = _2; *_4++ = c; }
int _5[13];
inline void _(int x) {
    if (x == 0) { _('0'); return; }
    register int _6;
    for (_6 = 0; x; x /= 10)_5[++_6] = x % 10;
    while (_6)_(char(_5[_6--] ^ 48));
}
inline void $() { fwrite(_2, 1, _4 - _2, stdout); }

inline void swap(int *a, int *b){
    (*a) ^= (*b);
    (*b) ^= (*a);
    (*a) ^= (*b);
}
inline void reverse(int *a, int *b){
    while(a != b)swap(a++, --b);
}

int a[MAXN], b[MAXN];
inline int fuck(int x, int p){
    register int ret = 1;
    while(p){
        if(p & 1)ret = 1LL * ret * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return ret;
}
inline void NTT(int *a, int N, int e){
    register int i, j, t, k, w, wn, x, y;
    for(i = 1, j = 0;i < N - 1;i++){
        for(int t = N;~j & t;j ^= t)t >>= 1;
        if(i < j)swap(a + i, a + j);
    }
    for(i = 1;i < N;i <<= 1){
        t = i << 1, wn = fuck(G, (MOD - 1) / t);
        for(j = 0;j < N;j += t){
            for(k = 0, w = 1;k < i;k++, w = 1LL * w * wn % MOD){
                x = a[j + k], y = 1LL * w * a[j + k + i] % MOD;
                a[j + k] = (x + y) % MOD;
                a[j + k + i] = (x - y + MOD) % MOD;
            }
        }
    }
    if(e){
        reverse(a + 1, a + N);
        for(i = 0, j = fuck(N, MOD - 2);i < N;i++)a[i] = 1LL * a[i] * j % MOD;
    }
}

int main(){
    register int n, m, N = 1, i;
    n = _(); m = _();
    for(i = 0;i <= n;i++)a[i] = _();
    for(i = 0;i <= m;i++)b[i] = _();
    while(N <= n + m)N <<= 1;
    NTT(a, N, 0); NTT(b, N, 0);
    for(i = 0;i < N;i++)a[i] = 1LL * a[i] * b[i] % MOD;
    NTT(a, N, 1);
    for(i = 0;i < n + m;i++)_(a[i]), _(' ');
    _(a[n + m]); _('\n'); $();
}