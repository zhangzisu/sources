#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
typedef long long lnt;
const lnt MOD = 1000000000000000000;
inline lnt add(lnt x, lnt y) {
    return (x += y) >= MOD ? x - MOD : x;
}
inline lnt mul(lnt x, lnt p) {
    lnt y = 0;
    for (; p; p >>= 1) {
        if (p & 1) y = add(x, y);
        x = add(x, x);
    }
    return y;
}
struct matrix {
    lnt f[4][4];
    inline matrix() {
        memset(f, 0, sizeof(f));
    }
    inline matrix friend operator*(matrix a, matrix b) {
        matrix c;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    c.f[i][j] = add(c.f[i][j], mul(a.f[i][k], b.f[k][j]));
                }
            }
        }
        return c;
    }
};
lnt a0, a1, a2, b, c, d, e, n;
int main() {
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);

    scanf("%lld%lld%lld%lld%lld%lld%lld%lld", &a0, &a1, &a2, &b, &c, &d, &e, &n);
    if (n == 0) return printf("%018lld\n", a0), 0;
    if (n == 1) return printf("%018lld\n", a1), 0;
    if (n == 2) return printf("%018lld\n", a2), 0;
    n -= 2;
    matrix base;
    base.f[0][0] = a2;
    base.f[0][1] = a1;
    base.f[0][2] = a0;
    base.f[0][3] = 1;
    matrix tf;
    tf.f[0][0] = b, tf.f[0][1] = 1;
    tf.f[1][0] = c, tf.f[1][2] = 1;
    tf.f[2][0] = d;
    tf.f[3][0] = e, tf.f[3][3] = 1;
    matrix rs;
    rs.f[0][0] = rs.f[1][1] = rs.f[2][2] = rs.f[3][3] = 1;
    for (; n; n >>= 1) {
        if (n & 1) rs = rs * tf;
        tf = tf * tf;
    }
    base = base * rs;
    printf("%018lld\n", base.f[0][0]);
    return 0;
}