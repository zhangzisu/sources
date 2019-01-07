#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MAXM 100010
int t, n, m;
int head[MAXN], to[MAXN << 1], val[MAXN << 1], next[MAXN << 1], tot;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int fa[MAXN][18], deep[MAXN];
long long dis[MAXN];
void dfs(int x) {
	for (int i = 1; i < 18; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x][0]) continue;
		fa[to[i]][0] = x;
		deep[to[i]] = deep[x] + 1;
		dis[to[i]] = dis[x] + val[i];
		dfs(to[i]);
	}
}
inline int lca(int u, int v) {
	if (deep[u] < deep[v]) std::swap(u, v);
	int delta = deep[u] - deep[v];
	for (int i = 17; ~i; i--)
		if ((delta >> i) & 1) u = fa[u][i];
	for (int i = 17; ~i; i--)
		if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return u == v ? u : fa[u][0];
}
struct path {
	int u, v, l;
	long long w;
} p[MAXM];
int main() {
	for (scanf("%d", &t); t; t--) {
		memset(head, -1, sizeof(head));
		tot = 0;
		scanf("%d", &n);
		for (int i = 1, u, v, w; i < n; i++) {
			scanf("%d%d%d", &u, &v, &w);
			$(u, v, w);
		}
		dfs(1);
		scanf("%d", &m);
		for (int i = 1; i <= m; i++) {
			scanf("%d%d%lld", &p[i].u, &p[i].v, &p[i].w);
			p[i].l = lca(p[i].u, p[i].v);
			p[i].w = dis[p[i].u] + dis[p[i].v] - 2 * dis[p[i].l] - p[i].w;
		}
		//
	}
	return 0;
}