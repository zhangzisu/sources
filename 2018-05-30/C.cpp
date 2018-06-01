#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
typedef long long lnt;
int t, n, m;
struct man {
    int d, v, w;
    inline friend bool operator<(const man &a, const man &b) {
        return a.w < b.w;
    }
} sb[MAXN];
inline lnt gcd(lnt a, lnt b) {
    return b ? gcd(b, a % b) : a;
}
struct frac {
    lnt a, b;
    inline frac(lnt x, lnt y) {
        lnt g = gcd(x, y);
        a = x / g;
        b = y / g;
    }
    inline friend frac operator+(const frac a, const frac b) {
        lnt g = gcd(a.b, b.b);
        lnt nb = a.b / g * b.b;
        lnt na = b.b / g * a.a + a.b / g * b.a;
        return frac(na, nb);
    }
    inline friend bool operator<(const frac a, const frac b) {
        lnt g = gcd(a.b, b.b);
        return b.b / g * a.a < a.b / g * b.a;
    }
    inline friend bool operator==(const frac a, const frac b) {
        return a.a == b.a && a.b == b.b;
    }
};
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", &sb[i].d);
        for (int i = 1; i <= n; i++) scanf("%d", &sb[i].v);
        for (int i = 1; i <= n; i++) scanf("%d", &sb[i].w);
        std::sort(sb + 1, sb + n + 1);
        int cgc = 1;
        for (int i = 2; i <= n; i++)
            if (sb[i].d != sb[i - 1].d) {
                cgc = 0;
                break;
            }
        if (cgc) {
            puts("0");
            continue;
        }
        frac ans(0, 1);
        for (int i = 1; i < n; i++) {
            frac tmp(1, 0);
            for (int j = i + 1; j <= n; j++) {
                if (sb[j].w <= sb[i].w) continue;
                if(a.v==b.v)continue;
                man a = sb[i];
                man b = sb[j];
                if (a.d < b.d) std::swap(a, b);
                int d, v;
                if ((a.v > 0) ^ (b.v > 0)) {
                    if (a.v < 0) {
                        d = a.d - b.d;
                        v = b.v - a.v;
                    } else {
                        d = m - (a.d - b.d);
                        v = a.v - b.v;
                    }
                } else {
                    int dr = (std::abs(a.v)<std::abs(b.v))^(a.v<0);
                    if(){
                        if(a.v<0){
                            //
                        }else{
                            //
                        }
                    }else{
                        if(a.v<0){
                            //
                        }else{
                            //
                        }
                    }
                }
                int v = sb[j].v - sb[i].v;
                int d = sb[j].d - sb[i].d;
                if (d < 0) d += m;
                if (v < 0) v = -v, d = m - d;
                tmp = std::min(tmp, frac(d, v));
            }
            printf("The answer of pos %d is %lld/%lld\n", i, tmp.a, tmp.b);
            if (tmp == frac(1, 0)) continue;
            ans = std::max(ans, tmp);
        }
        printf("%lld/%lld\n", ans.a, ans.b);
    }
    return 0;
}