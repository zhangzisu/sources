#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXM 1010
int sum[MAXM][MAXM], n, m, k, e, d;
int head[MAXM], to[MAXM << 4], next[MAXM << 4], val[MAXM << 4], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int dis[MAXM], inq[MAXM], g[MAXM][MAXM], f[MAXM];
std::queue<int> Q;
inline bool o(int x, int l, int r) { return sum[x][r] == sum[x][l - 1]; }
inline int di(int l, int r) {
    memset(dis, 0x3F, sizeof(int) * m + 8);
    if (!o(1, l, r)) return 0x3F3F3F3F;
    dis[1] = 0;
    inq[1] = 1;
    Q.push(1);
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        inq[x] = 0;
        for (int i = head[x]; ~i; i = next[i]) {
            if (o(to[i], l, r) && dis[to[i]] > dis[x] + val[i]) {
                dis[to[i]] = dis[x] + val[i];
                if (!inq[to[i]]) Q.push(to[i]), inq[to[i]] = 1;
            }
        }
    }
    return dis[m];
}
int main() {
    scanf("%d%d%d%d", &n, &m, &k, &e);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= e; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        $(u, v, w);
    }
    scanf("%d", &d);
    for (int i = 1; i <= d; i++) {
        int x, l, r;
        scanf("%d%d%d", &x, &l, &r);
        sum[x][l]++;
        sum[x][r + 1]--;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) sum[i][j] += sum[i][j - 1];
        for (int j = 1; j <= n; j++) sum[i][j] += sum[i][j - 1];
    }
    for (int l = 1; l <= n; l++)
        for (int r = l; r <= n; r++) g[l][r] = di(l, r);
    memset(f, 0x3F, sizeof(f));
    f[0] = -k;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (g[j + 1][i] != 0x3F3F3F3F)
                f[i] = std::min(f[i], f[j] + g[j + 1][i] * (i - j) + k);
        }
    }
    printf("%d\n", f[n]);
    return 0;
}