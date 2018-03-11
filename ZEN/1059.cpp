#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
#define MAXN 100000
#define MOD 99991
const double PI = acos(-1);

struct fsb{
    double r, i;
    inline fsb(double r = 0, double i = 0) : r(r), i(i){}
    inline friend fsb operator + (const fsb &a, const fsb &b){
        return fsb(a.r + b.r, a.i + b.i);
    }
    inline friend fsb operator - (const fsb &a, const fsb &b){
        return fsb(a.r - b.r, a.i - b.i);
    }
    inline friend fsb operator * (const fsb &a, const fsb &b){
        return fsb(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
    }
    inline friend fsb operator / (const fsb &a, const double &b){
        return fsb(a.r / b, a.i / b);
    }
}wi[MAXN], iw[MAXN], a[MAXN], b[MAXN];

typedef std::vector<int> poly;

inline void FFT(fsb *a, int n, bool e){
    for(int i = 1, j = 0;i < n - 1;i++){
        for(int t = n;~j & t;j ^= t)t >>= 1;
        if(i < j)std::swap(a[i], a[j]);
    }
    const fsb* d = e ? iw : wi;
    for(int k = 1;k < n;k <<= 1){
        int t = k << 1;
        for(int i = 0;i < n;i += t){
            for(int j = 0;j < k;j++){
                fsb x = a[i + j], y = d[j] * a[i + j + k];
                a[i + j] = x + y;
                a[i + j + k] = x - y;
            }
        }
    }
}

inline poly operator * (const poly &a, const poly &b){
    //
}

inline prepare(int n){
    wi[0] = fsb(1, 0);
    for(int i = 1;i < n;i++){
        wi[i] = fsb(sin(PI / i), cos(PI / i));
    }
    return 0;
}

int n, k, a[MAXN], f0, f1, a0, a1;

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 1;i <= n;i++)scanf("%d", &a[i]);
    scanf("%d%d", &f0, &f1);
    a1 = 1LL * (f0 + f1) * fuck(4, MOD - 2) % MOD;
    a0 = (f0 - a1 + MOD) % MOD;
    return 0;
}