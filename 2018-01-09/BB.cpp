#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 105
int _, n, m, K, sb[MAXN][MAXN], x[MAXN], y[MAXN];
int zx[MAXN][MAXN], tim;
struct node {
    int s, x, y;
    node(int s = 0, int x = 0, int y = 0) : s(s), x(x), y(y) {}
    inline friend bool operator < (const node &a, const node &b){return a.s > b.s;}
} Q[MAXN * MAXN];
int calc(int a, int b) {
    int tmp = Q[a].s, X = Q[a].x, Y = Q[a].y;
    tim++;
    for (int i = 1; i <= K; i++)
        if (X + x[i] <= 0 || X + x[i] > n || Y + y[i] <= 0 || Y + y[i] > m)continue;
        else zx[X + x[i]][Y + y[i]] = tim;
    X = Q[b].x, Y = Q[b].y;
    for (int i = 1; i <= K; i++)
        if (X + x[i] <= 0 || X + x[i] > n || Y + y[i] <= 0 || Y + y[i] > m || zx[X + x[i]][Y + y[i]] == tim)continue;
        else tmp += sb[X + x[i]][Y + y[i]];
    return tmp;
}
int main() {
    scanf("%d", &_);
    while(_--) {
        scanf("%d%d%d", &n, &m, &K);
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)scanf("%1d", &sb[i][j]);
        for (int i = 1; i <= K; i++) scanf("%d%d", &x[i], &y[i]);
        int ans = 0, tot = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                int tmp = 0;
                for (int k = 1; k <= K; k++)
                    if (i + x[k] <= 0 || i + x[k] > n || j + y[k] <= 0 || j + y[k] > m)
                        continue;
                    else
                        tmp += sb[i + x[k]][j + y[k]];
                Q[++tot] = node(tmp, i, j);
            }
        std::sort(Q + 1, Q + tot + 1);
        for (int i = 1; i <= tot && i <= 4000; i++) {
            if (ans >= Q[i].s * 2) break;
            for (int j = i + 1; j <= tot && j <= 4000; j++) {
                if (ans >= Q[i].s + Q[j].s) break;
                ans = std::max(calc(i, j), ans);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
