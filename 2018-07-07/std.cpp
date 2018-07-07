#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 10010
const int INF = (~0U) >> 2;

int n, a[MAXN], b[MAXN], c[MAXN], d[MAXN];
int f[51][51][51][51];

inline void up(int &x, int y) { x = std::max(x, y); }

inline void baoli() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                for (int l = 1; l <= n; l++) {
                    up(f[i][j][k][l], f[i - 1][j][k][l]);
                    up(f[i][j][k][l], f[i - 1][j - 1][k][l]);
                    up(f[i][j][k][l], f[i - 1][j - 1][k - 1][l]);

                    up(f[i][j][k][l], f[i][j - 1][k][l]);
                    up(f[i][j][k][l], f[i][j - 1][k - 1][l]);
                    up(f[i][j][k][l], f[i][j - 1][k - 1][l - 1]);

                    up(f[i][j][k][l], f[i][j][k - 1][l]);
                    up(f[i][j][k][l], f[i][j][k - 1][l - 1]);
                    up(f[i][j][k][l], f[i - 1][j][k - 1][l - 1]);

                    up(f[i][j][k][l], f[i][j][k][l - 1]);
                    up(f[i][j][k][l], f[i - 1][j][k][l - 1]);
                    up(f[i][j][k][l], f[i - 1][j - 1][k][l - 1]);

                    if (a[i] == b[j] && a[i] == c[k] && a[i] == d[l])
                        up(f[i][j][k][l], f[i - 1][j - 1][k - 1][l - 1] + 1);
                }
            }
        }
    }
    printf("%d\n", f[n][n][n][n]);
}

std::pair<int, int> dat[3][MAXN];
struct data {
    int val[3][2], f[8], fmax;
    inline void debug() {
        printf("\t > [%d, %d], [%d, %d], [%d, %d]", val[0][0], val[0][1], val[1][0], val[1][1], val[2][0], val[2][1]);
    }
} t[MAXN], tmp[MAXN];

// inline void muni() {
//     for (int i = 1; i <= n; i++) {
//         for (int j = 0; j < 3; j++) {
//             int pos = (*std::lower_bound(dat[j] + 1, dat[j] + n + 1, std::make_pair(d[i], 0))).second;
//             t[i].val[j][0] = pos;
//         }
//     }
//     int ans = 0;
//     for (int i = 1; i <= n; i++) {
//         t[i].f[0] = 1;
//         for (int j = 1; j <= i; j++) {
//             if (t[i].val[0][0] > t[j].val[0][0] && t[i].val[1][0] > t[j].val[1][0] && t[i].val[2][0] > t[j].val[2][0]) {
//                 up(t[i].f[0], t[j].f[0] + 1);
//             }
//         }
//         up(ans, t[i].f[0]);
//     }
//     printf("%d\n", ans);
// }

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), dat[0][i] = std::make_pair(a[i], i);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]), dat[1][i] = std::make_pair(b[i], i);
    for (int i = 1; i <= n; i++) scanf("%d", &c[i]), dat[2][i] = std::make_pair(c[i], i);
    for (int i = 1; i <= n; i++) scanf("%d", &d[i]);
    // if (n <= 50) return baoli(), 0;
    for (int i = 0; i < 3; i++) std::sort(dat[i] + 1, dat[i] + n + 1);
    // muni();
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            auto a = std::lower_bound(dat[j] + 1, dat[j] + n + 1, std::make_pair(d[i], 0));
            auto b = a + 1;
            t[i].val[j][0] = a->first == d[i] ? a->second : INF;
            t[i].val[j][1] = b->first == d[i] ? b->second : INF;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int d = 0; d < 8; d++) {
            if (t[i].val[0][d & 1] == INF || t[i].val[1][(d >> 1) & 1] == INF || t[i].val[2][(d >> 2) & 1] == INF) continue;
            int &now = t[i].f[d];
            now = 1;
            for (int j = 1; j <= i; j++) {
                if (t[j].fmax < t[i].f[d]) continue;
                for (int p = 0; p < 8; p++) {
                    if (t[j].val[0][p & 1] == INF || t[j].val[1][(p >> 1) & 1] == INF || t[j].val[2][(p >> 2) & 1] == INF) continue;
                    if (t[i].val[0][d & 1] > t[j].val[0][p & 1] &&
                        t[i].val[1][(d >> 1) & 1] > t[j].val[1][(p >> 1) & 1] &&
                        t[i].val[2][(d >> 2) & 1] > t[j].val[2][(p >> 2) & 1])
                        up(now, t[j].f[p] + 1);
                }
            }
            up(t[i].fmax, now);
        }
        up(ans, t[i].fmax);
    }
    printf("%d\n", ans);
    return 0;
}