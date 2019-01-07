#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
const int INF = (~0U) >> 1;
int n, m, a[MAXN], head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int size[MAXN], esm[MAXN], vis[MAXN], fa[MAXN][20], dis[MAXN][20], deep[MAXN], all, root;
void gr(int x, int p) {
	size[x] = 1;
	esm[x] = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == p || vis[to[i]]) continue;
		gr(to[i], x);
		size[x] += size[to[i]];
		esm[x] = std::max(esm[x], size[to[i]]);
	}
	esm[x] = std::max(esm[x], all - size[x]);
	if (esm[x] < esm[root]) root = x;
}
void dfs(int x, int p, int org, int d) {
	deep[x]++;
	fa[x][deep[x]] = org;
	dis[x][deep[x]] = d;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == p || vis[to[i]]) continue;
		dfs(to[i], x, org, d + 1);
	}
}
int *bit[MAXN], *fbit[MAXN];
void solve(int x) {
	gr(x, 0);
	vis[x] = 1;
	fa[x][++deep[x]] = x;
	for (int i = head[x]; ~i; i = next[i]) {
		if (!vis[to[i]]) {
			dfs(to[i], x, x, 1);
		}
	}
	for (int i = head[x]; ~i; i = next[i]) {
		if (!vis[to[i]]) {
			all = size[to[i]];
			root = 0;
			gr(to[i], x);
			solve(root);
		}
	}
	bit[x] = (int *)calloc(size[x] + 1, sizeof(int));
	fbit[x] = (int *)calloc(size[x] + 1, sizeof(int));
}
inline int lowbit(int x) { return x & -x; }
inline void add(int *BIT, int x, int n, int v) {
	for (; x && x <= n; x += lowbit(x)) BIT[x] += v;
}
inline int qry(int *BIT, int x) {
	register int y = 0;
	for (; x; x -= lowbit(x)) y += BIT[x];
	return y;
}
inline void ADD(int x, int v) {
	for (int i = deep[x]; i; i--) {
		add(bit[fa[x][i]], dis[x][i], size[fa[x][i]], v);
		add(fbit[fa[x][i]], dis[x][i - 1], size[fa[x][i]], v);
	}
}
inline int QRY(int x, int k) {
	int ans = 0;
	for (int i = deep[x]; i; i--) {
		if (k - dis[x][i] >= 0) {
			ans += a[fa[x][i]];
			ans += qry(bit[fa[x][i]], std::min(size[fa[x][i]], k - dis[x][i]));
			ans -= qry(fbit[fa[x][i + 1]], std::min(size[fa[x][i + 1]], k - dis[x][i]));
		}
	}
	return ans;
}
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		$(u, v);
	}
	esm[all = n, root = 0] = INF;
	gr(1, 0);
	solve(root);
	for (int i = 1; i <= n; i++) ADD(i, a[i]);
	for (int lans = 0, op, x, y; m; m--) {
		scanf("%d%d%d", &op, &x, &y);
		x ^= lans;
		y ^= lans;
		if (op) {
			ADD(x, -a[x]);
			ADD(x, y);
			a[x] = y;
		} else {
			printf("%d\n", lans = QRY(x, y));
		}
	}
	return 0;
}