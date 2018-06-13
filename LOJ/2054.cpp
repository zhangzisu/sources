#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010

int n, q, v[MAXN];
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int deep[MAXN], size[MAXN], fa[MAXN], top[MAXN], dfn[MAXN], pos[MAXN], dfsclk;
void dfs0(int x) {
    size[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x]) continue;
        fa[to[i]] = x;
        deep[to[i]] = deep[x] + 1;
        dfs0(to[i]);
        size[x] += size[to[i]];
    }
}
void dfs1(int x) {
    pos[dfn[x] = ++dfsclk] = x;
    if (!top[x]) top[x] = x;
    int max = 0;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && size[to[i]] > size[max]) max = to[i];
    if (max) top[max] = top[x], dfs1(max);
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && to[i] != max) dfs1(to[i]);
}
int sum[MAXN << 2];
void set(int n, int l, int r, int p) {
    if (l == r) return sum[n] = 1, void();
    int mid = (l + r) >> 1;
    if (p <= mid)
        set(n << 1, l, mid, p);
    else
        set(n << 1 | 1, mid + 1, r, p);
    sum[n] = sum[n << 1] + sum[n << 1 | 1];
}
int querySum(int n, int l, int r, int L, int R) {
    if (l == L && r == R) return sum[n];
    int mid = (l + r) >> 1;
    if (R <= mid) return querySum(n << 1, l, mid, L, R);
    if (L > mid) return querySum(n << 1 | 1, mid + 1, r, L, R);
    return querySum(n << 1, l, mid, L, mid) + querySum(n << 1 | 1, mid + 1, r, mid + 1, R);
}
int queryPos(int n, int l, int r, int L, int R) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (R <= mid) return queryPos(n << 1, l, mid, L, R);
    if (L > mid) return queryPos(n << 1 | 1, mid + 1, r, L, R);
    if (querySum(n << 1 | 1, mid + 1, r, mid + 1, R))
        return queryPos(n << 1 | 1, mid + 1, r, mid + 1, R);
    return queryPos(n << 1, l, mid, L, mid);
}
char buf[5];
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        $(u, v);
    }
    dfs0(1);
    dfs1(1);
    set(1, 1, n, 1);
    while (q--) {
        int x;
        scanf("%s%d", buf + 1, &x);
        if (buf[1] == 'C') {
            set(1, 1, n, dfn[x]);
        } else {
            while (x) {
                int sum = querySum(1, 1, n, dfn[top[x]], dfn[x]);
                if (sum) {
                    x = pos[queryPos(1, 1, n, dfn[top[x]], dfn[x])];
                    break;
                }
                x = fa[top[x]];
            }
            printf("%d\n", x);
        }
    }
    return 0;
}