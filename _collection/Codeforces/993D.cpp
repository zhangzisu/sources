#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAXN 510
typedef long double ld;
const ld EPS = 1e-6;
const ld INF = 1. / 0.;
int n;
struct data {
    ld a, b, c;
} d[MAXN];
ld f[MAXN][MAXN], sa, sb, tmp[MAXN];
inline bool check(ld mid) {
    for (int i = 1; i <= n; i++) d[i].c = d[i].a - d[i].b * mid;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++) f[i][j] = INF;
    f[0][0] = 0;
    int all = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
        tmp[++all] = d[i].c;
        if (d[i].a != d[i + 1].a) {
            ++cnt;
            std::sort(tmp + 1, tmp + all + 1);
            for (int i = 1; i <= all; i++) tmp[i] += tmp[i - 1];
            for (int j = 0; j <= all; j++) {
                for (int k = all - j; k <= i; k++) {
                    f[cnt][k - (all - j) + j] = std::min(f[cnt][k - (all - j) + j], f[cnt - 1][k] + tmp[j]);
                }
            }
            all = 0;
        }
    }
    ld res = INF;
    for (int i = 0; i <= n; i++) res = std::min(res, f[cnt][i]);
    return res <= EPS;
}
int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> d[i].a;
        sa += d[i].a;
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> d[i].b;
        sb += d[i].b;
    }
    std::sort(d + 1, d + n + 1, [](const data& a, const data& b) { return a.a > b.a; });
    ld l = 0, r = sa / sb;
    while (r - l > EPS) {
        ld mid = (l + r) / 2;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    std::cout << (long long)round(r * 1000) << std::endl;
}