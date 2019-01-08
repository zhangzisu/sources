#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 10010
#define MAXM 100010
#define INF 0x3F3F3F3F
int n, m, head[MAXN], cur[MAXN], to[MAXM], cap[MAXM], next[MAXM], tot = 0;
inline void $(int u, int v, int c) {
    // printf(" > %d - %d : %d\n", u, v, c);
    next[tot] = head[u], to[tot] = v, cap[tot] = c, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, cap[tot] = 0, head[v] = tot++;
}
int cnt = 0, pos[100][100], s, t, level[MAXN];
char buf[100][100];
std::queue<int> Q;
inline bool bfs() {
    memcpy(cur, head, sizeof(cur));
    memset(level, -1, sizeof(level));
    level[s] = 0;
    Q.push(s);
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        for (int i = head[x]; ~i; i = next[i]) {
            if (cap[i] && !~level[to[i]]) {
                level[to[i]] = level[x] + 1;
                Q.push(to[i]);
            }
        }
    }
    return ~level[t];
}
int dfs(int x, int flow) {
    if (x == t || !flow) return flow;
    int ret = 0, tmp;
    for (int &i = cur[x]; ~i; i = next[i]) {
        if (level[to[i]] == level[x] + 1 && cap[i]) {
            tmp = dfs(to[i], std::min(flow, cap[i]));
            flow -= tmp;
            ret += tmp;
            cap[i] -= tmp;
            cap[i ^ 1] += tmp;
            if (!flow) return ret;
        }
    }
    return ret;
}
inline int Dinic() {
    int ret = 0;
    while (bfs()) ret += dfs(s, INF);
    return ret;
}
int main() {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) {
        scanf("%s", buf[i] + 1);
        for (int j = 1; j <= m; j++) {
            if (buf[i][j] == '*') {
                pos[i][j] = cnt++;
            }
        }
    }
    s = cnt++;
    t = cnt++;
    for (int i = 1; i <= n; i++) {
        int l = 0, r = 0;
        for (int j = 1; j <= m; j++) {
            if (buf[i][j] != '#') {
                if (!l) l = j;
                r = j;
            } else {
                if (l) {
                    int x = cnt++;
                    // printf("LINK %d : %d - %d => %d\n", i, l, r, x);
                    $(s, x, 1);
                    for (int k = l; k <= r; k++) {
                        if (buf[i][k] == '*') $(x, pos[i][k], 1);
                    }
                }
                l = r = 0;
            }
        }
        if (l) {
            int x = cnt++;
            // printf("LINK %d : %d - %d => %d\n", i, l, r, x);
            $(s, x, 1);
            for (int k = l; k <= r; k++) {
                if (buf[i][k] == '*') $(x, pos[i][k], 1);
            }
        }
        l = r = 0;
    }
    for (int i = 1; i <= m; i++) {
        int l = 0, r = 0;
        for (int j = 1; j <= n; j++) {
            if (buf[j][i] != '#') {
                if (!l) l = j;
                r = j;
            } else {
                if (l) {
                    int x = cnt++;
                    // printf("LINK %d - %d : %d => %d\n", l, r, i, x);
                    $(x, t, 1);
                    for (int k = l; k <= r; k++) {
                        if (buf[k][i] == '*') $(pos[k][i], x, 1);
                    }
                }
                l = r = 0;
            }
        }
        if (l) {
            int x = cnt++;
            // printf("LINK %d - %d : %d => %d\n", l, r, i, x);
            $(x, t, 1);
            for (int k = l; k <= r; k++) {
                if (buf[k][i] == '*') $(pos[k][i], x, 1);
            }
        }
        l = r = 0;
    }
    printf("%d\n", Dinic());
    return 0;
}