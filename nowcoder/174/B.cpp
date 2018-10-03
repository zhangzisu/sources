#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#define MAXN 10010
#define MAXM 1000010
const int INF = 0x3F3F3F3F;
int head[MAXN], to[MAXM << 1], next[MAXM << 1], tot, ans, ansu, ansv;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int fa[MAXN][18], deep[MAXN], vis[MAXN], n, m;
std::queue<int> Q;
inline void init() {
	memset(head, -1, sizeof(head));
	memset(vis, 0, sizeof(vis));
	tot = 0;
	ans = INF;
	memset(fa, 0, sizeof(fa));
	memset(deep, 0, sizeof(deep));
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
inline void BFS(int x) {
	Q.push(x);
	vis[x] = 1;
	while (Q.size()) {
		int x = Q.front();
		Q.pop();
		for (int i = 1; i < 18; i++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
		for (int i = head[x]; ~i; i = next[i]) {
			if (to[i] == fa[x][0]) continue;
			if (!vis[to[i]]) {
				vis[to[i]] = 1;
				fa[to[i]][0] = x;
				deep[to[i]] = deep[x] + 1;
				Q.push(to[i]);
			} else {
				int l = lca(x, to[i]);
				int size = deep[x] - deep[l] + deep[to[i]] - deep[l] + 1;
				if (size < ans) {
					ans = size;
					ansu = x;
					ansv = to[i];
				}
			}
		}
	}
}

inline void solve() {
	if (scanf("%d%d", &n, &m) != 2) exit(0);
	n <<= 1;
	for (int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v);
		u = u * 2 - 1;
		v = v * 2;
		$(u, v);
	}
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			BFS(i);
		}
	}
	if (ans == INF) return puts("-1"), void();
	printf("%d\n", ans);
	int l = lca(ansu, ansv);
	std::vector<int> uu, vv;
	for (; ansu != l; ansu = fa[ansu][0]) uu.push_back(ansu);
	for (; ansv != l; ansv = fa[ansv][0]) vv.push_back(ansv);
	std::reverse(vv.begin(), vv.end());
	for (auto u : uu) printf("%d ", (u + 1) / 2);
	printf("%d ", (l + 1) / 2);
	for (auto v : vv) printf("%d ", (v + 1) / 2);
	puts("");
}
int main() {
	scanf("%*d");
	while (1) init(), solve();
	return 0;
}