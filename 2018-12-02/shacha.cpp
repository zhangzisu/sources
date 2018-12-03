#include <cstdio>
#include <cstring>
#include <queue>
#define MAXN 2010
#define MOD 1000000007
int n, k, d[MAXN], head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
    d[u]++, d[v]++;
}
int rbq[MAXN][MAXN], fa[MAXN];
void pre(int x) {
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x]) continue;
        fa[to[i]] = x;
        pre(to[i]);
    }
}
int dis[MAXN][MAXN];
void dfs(int x, int fa, int *dis) {
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        dis[to[i]] = dis[x] + 1;
        dfs(to[i], x, dis);
    }
}
int mid, res, ret;
inline bool Chen(int x) {
    std::queue<int> Q;
    Q.push(x);
    while (Q.size()) {
        x = Q.front();
        Q.pop();
        int ci = 0, tmp = 0;
        for (int i = 1; i <= k; i++)
            if (!rbq[x][i]) {
                ci = i;
                tmp++;
            }
        if (!ci) return false;
        res = 1LL * res * tmp % MOD;
        for (int i = 1; i <= n; i++)
            if (dis[x][i] < mid) rbq[i][ci] = 1;
        for (int i = head[x]; ~i; i = next[i]) {
            if (to[i] == fa[x]) continue;
            Q.push(to[i]);
        }
    }
    return true;
}
int main() {
    scanf("%d%d", &n, &k);
    if (k == 1) return puts("1 1"), 0;
    if (k == 2) return puts("2 2"), 0;
    memset(head, -1, sizeof(head));
    for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
    bool chen = true;
    for (int i = 1; i <= n; i++) chen &= d[i] <= 2;
    if (chen) {
        int ans = 1;
        for (int i = 2; i <= k; i++) ans = 1LL * ans * i % MOD;
        return printf("%d %d\n", k, ans), 0;
    }
    for (int i = 1; i <= n; i++) dfs(i, 0, dis[i]);
    pre(1);
    int l = 0, r = n, ans = 0;
    while (l <= r) {
        mid = (l + r) >> 1;
        res = 1;
        memset(rbq, 0, sizeof(rbq));
        if (Chen(1)) {
            ans = mid;
            ret = res;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%d %d\n", ans, ret);
    return 0;
}