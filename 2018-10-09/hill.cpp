#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 65536
char _1[BUF], *_3 = _1 + BUF;
int _0;
inline char gc() {
    if (_3 == _1 + BUF) _0 = fread(_1, 1, BUF, stdin), _3 = _1;
    return _3 == _1 + _0 ? 0 : *_3++;
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch) && (ch ^ 45)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#include <queue>
#define MAXN 51
#define MAXM 310
int n, m, f[MAXN][21][1010];
int head[MAXN], to[MAXM], next[MAXM], val[MAXM], in[MAXN], out[MAXN], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    in[v]++, out[u]++;
}
std::queue<int> Q;
inline void up(int &x, int y) {
    if (y < x) x = y;
}
int main() {
    memset(head, -1, sizeof(head));
    n = $(), m = $();
    for (int i = 1, u, v, w; i <= m; i++) {
        u = $(), v = $(), w = $();
        $(u, v, w);
    }
    memset(f, 0x3F, sizeof(f));
    f[1][0][0] = 0;
    for (int i = 1; i <= n; i++)
        if (!in[i]) Q.push(i);
    double ans = 1e100;
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        for (int i = head[x]; ~i; i = next[i]) {
            for (int j = 0; j < 20; j++) {
                for (int k = 0; k < 1010; k++) {
                    if (k + val[i] > 1010) break;
                    up(f[to[i]][j + 1][k + val[i]], f[x][j][k] + val[i] * val[i]);
                }
            }
            if (!--in[to[i]]) Q.push(to[i]);
        }
    }
    for (int i = 1; i <= 20; i++) {
        for (int k = 0; k < 1010; k++) {
            ans = std::min(ans, (1. * f[n][i][k] * i - k * k) / i / i);
        }
    }
    printf("%.4f\n", ans);
    return 0;
}