#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 65536
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2;
int _0;
inline char gc() {
    if (_3 == _1 + BUF) _0 = fread(_1, 1, BUF, stdin), _3 = _1;
    return _3 == _1 + _0 ? 0 : *_3++;
}
inline void pc(char c) {
    if (_4 == _2 + BUF) fwrite(_2, 1, BUF, stdout), _4 = _2;
    *_4++ = c;
}
inline void rt() {
    fwrite(_2, 1, _4 - _2, stdout);
    exit(0);
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch) && (ch ^ 45)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
inline void pi(int x) {
    static int _5[32];
    if (!x) return pc('0');
    if (x < 0) pc(45), x = -x;
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
    while (_6) pc(_5[_6--] ^ 48);
}
#define MAXN 200
int n, m, k, q, a[MAXN][MAXN], v[MAXN * MAXN];
namespace FUCK1 {
int b[MAXN * MAXN], c[MAXN * MAXN], d[MAXN * MAXN];
void main() {
    for (int x0, x1, y0, y1, ans, max; q; q--) {
        x0 = $() - 1, y0 = $() - 1, x1 = $() - 1, y1 = $() - 1;
        ans = max = 0;
        for (int i = x0; i <= x1; i++) {
            for (int j = y0; j <= y1; j++) {
                if (!c[a[i][j]]) d[max++] = a[i][j], c[a[i][j]] = 1;
                b[a[i][j]]++;
            }
        }
        for (int i = 0; i < max; i++) ans += b[d[i]] * b[d[i]];
        for (int i = x0; i <= x1; i++) {
            for (int j = y0; j <= y1; j++) {
                c[a[i][j]] = 0;
                b[a[i][j]]--;
            }
        }
        pi(ans), pc(10);
    }
}
}  // namespace FUCK1
namespace FUCK2 {
int sum[200][200][200];
inline int get(int t, int x, int y) { return (x < 0 || y < 0) ? 0 : sum[t][x][y]; }
void main() {
    for (int t = 0; t < k; t++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                sum[t][i][j] = get(t, i, j - 1) + get(t, i - 1, j) - get(t, i - 1, j - 1) + (a[i][j] == t);
            }
        }
    }
    for (int x0, x1, y0, y1, ans; q; q--) {
        x0 = $() - 1, y0 = $() - 1, x1 = $() - 1, y1 = $() - 1;
        ans = 0;
        for (int t = 0; t < k; t++) {
            int c = get(t, x1, y1) - get(t, x0 - 1, y1) - get(t, x1, y0 - 1) + get(t, x0 - 1, y0 - 1);
            ans += c * c;
        }
        pi(ans), pc(10);
    }
}
}  // namespace FUCK2
int main() {
    freopen("vegetable.in", "r", stdin);
    freopen("vegetable.out", "w", stdout);
    n = $(), m = $(), q = $();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            v[k++] = a[i][j] = $();
        }
    }
    std::sort(v, v + k);
    k = std::unique(v, v + k) - v;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = std::lower_bound(v, v + k, a[i][j]) - v;
        }
    }
    k <= 200 ? FUCK2::main() : FUCK1::main();
    rt();
}