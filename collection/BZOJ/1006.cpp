#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 10010
#define MAXM 2000010
int head[MAXN], to[MAXM], next[MAXM], tot = 0, n, m;
inline void addEdge(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int first[MAXN], val[MAXM], go[MAXM], cnt = 0;
inline void addValue(int key, int value) {
    go[cnt] = first[key], val[cnt] = value, first[key] = cnt++;
}
int vis[MAXN], clk[MAXN], pfn[MAXN], pos[MAXN];
inline void GLC() {
    for (int i = 1; i <= n; i++) addValue(0, i);
    int max = 0;
    for (int x = n; x; x--) {
        while (1) {
            int i;
            for (i = first[max]; ~i; i = go[i]) {
                if (!vis[val[i]])
                    break;
                else
                    first[max] = i;
            }
            if (~i) {
                int y = val[i];
                vis[y] = 1;
                pos[pfn[y] = x] = y;
                for (int j = head[y]; ~j; j = next[j]) {
                    int z = to[j];
                    if (vis[z]) continue;
                    addValue(++clk[z], z);
                    max = std::max(max, clk[z]);
                }
                break;
            } else {
                max--;
            }
        }
    }
}
int mark[MAXN], col[MAXN], ans;
int main() {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    memset(first, -1, sizeof(first));

    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
    }

    GLC();

    for (int i = n; i; i--) {
        for (int j = head[pos[i]]; ~j; j = next[j]) mark[col[to[j]]] = i;
        int t = 1;
        while (mark[t] == i) t++;
        ans = std::max(ans, col[pos[i]] = t);
    }
    printf("%d\n", ans);
    return 0;
}