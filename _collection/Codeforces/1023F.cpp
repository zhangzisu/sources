#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 1000010
typedef long long lnt;
int n, m;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], val[MAXN << 1], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int top[MAXN], dfn[MAXN], fa[MAXN], deep[MAXN], size[MAXN], dfsclk;
void dfs(int x) {
	size[x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x]) continue;
		fa[to[i]] = x;
		deep[to[i]] = deep[x] + 1;
		spc[to[i]] = val[i];
		dfs(to[i]);
		size[x] += size[to[i]];
	}
}
void split(int x) {
	dfn[x] = ++dfsclk;
	if (!top[x]) top[x] = x;
	int max = 0;
	for (int i = head[x]; ~i; i = next[i])
		if (to[i] != fa[x] && size[to[i]] > size[max]) max = to[i];
	if (max) top[max] = top[x], split(max);
	for (int i = head[x]; ~i; i = next[i])
		if (to[i] != fa[x] && to[i] != max) split(to[i]);
}
lnt min[MAXN << 2];
inline void up(lnt& x, lnt y) {
	if (y < x) x = y;
}
inline void pushDown(int n) {
	up(min[n << 1], min[n]);
	up(min[n << 1 | 1], min[n]);
}
void setMin(int n, int l, int r, int L, int R, lnt v) {
	if (L > R) return;
	if (l == L && r == R) return up(min[n], v);
	int mid = (l + r) >> 1;
	pushDown(n);
	if (R <= mid) return setMin(n << 1, l, mid, L, R, v);
	if (L > mid) return setMin(n << 1 | 1, mid + 1, r, L, R, v);
	setMin(n << 1, l, mid, L, mid, v);
	setMin(n << 1 | 1, mid + 1, r, mid + 1, R, v);
}
lnt getMin(int n, int l, int r, int p) {
	if (l == r) return min[n];
	int mid = (l + r) >> 1;
	pushDown(n);
	return p <= mid ? getMin(n << 1, l, mid, p) : getMin(n << 1 | 1, mid + 1, r, p);
}
inline int lca(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) std::swap(u, v);
		u = fa[top[u]];
	}
	return deep[u] < deep[v] ? u : v;
}
inline void gao(int u, int v, int w) {
	int x = lca(u, v);
	while (top[u] != top[x]) {
		setMin(1, 1, n, dfn[top[u]], dfn[u], w);
		u = fa[top[u]];
	}
	setMin(1, 1, n, dfn[x] + 1, dfn[u], w);
	while (top[v] != top[x]) {
		setMin(1, 1, n, dfn[top[v]], dfn[v], w);
		v = fa[top[v]];
	}
	setMin(1, 1, n, dfn[x] + 1, dfn[v], w);
}
lnt ans = 0;
std::vector<std::pair<std::pair<int, int>, int>> gg;
int main() {
	scanf("%d%d%d", &n, &k, &m);
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= n; i++) p[i] = i;
	for (int i = 1, u, v; i <= k; i++) {
		scanf("%d%d", &u, &v);
		$(u, v, 1);
		p[find(u)] = find(v);
	}
	for (int i = 1, u, v, w; i <= m; i++) {
		scanf("%d%d%d", &u, &v, &w);
		if (find(u) != find(v)) {
			$(u, v, 0);
			p[find(u)] = find(v);
		} else {
			gg.emplace_back(std::make_pair(u, v), w);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (!dfn[i]) {
			dfs(i);
			split(i);
		}
	}
	memset(min, 0x3F, sizeof(min));
	lnt inf = min[0];
	for (auto x : gg) gao(x.first.first, x.first.second, x.second);
	// fprintf(stderr, "PASS %d\n", __LINE__);
	for (int i = 1; i <= n; i++) {
		if (spc[i]) {
			lnt x = getMin(1, 1, n, dfn[i]);
			if (x == inf) return puts("-1"), 0;
			ans += x;
		}
	}
	printf("%lld\n", ans);
	return 0;
}