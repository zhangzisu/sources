#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
#define INV 500000004
#define MAXN 200010
int n, m;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int top[MAXN], dfn[MAXN], fa[MAXN], deep[MAXN], size[MAXN], pos[MAXN], dfsclk;
void dfs(int x) {
	size[x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x]) continue;
		fa[to[i]] = x;
		deep[to[i]] = deep[x] + 1;
		dfs(to[i]);
		size[x] += size[to[i]];
	}
}
void split(int x) {
	pos[dfn[x] = ++dfsclk] = x;
	if (!top[x]) top[x] = x;
	int max = 0;
	for (int i = head[x]; ~i; i = next[i])
		if (to[i] != fa[x] && size[to[i]] > size[max]) max = to[i];
	if (max) top[max] = top[x], split(max);
	for (int i = head[x]; ~i; i = next[i])
		if (to[i] != fa[x] && to[i] != max) split(to[i]);
}
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int sum1[MAXN << 2], sum2[MAXN << 2], tag[MAXN << 2], val[MAXN];
void build(int n, int l, int r) {
	if (l == r) {
		sum1[n] = val[pos[l]];
		sum2[n] = 1LL * val[pos[l]] * val[pos[l]] % MOD;
		return;
	}
	int mid = (l + r) >> 1;
	build(n << 1, l, mid);
	build(n << 1 | 1, mid + 1, r);
	sum1[n] = (sum1[n << 1] + sum1[n << 1 | 1]) % MOD;
	sum2[n] = (sum2[n << 1] + sum2[n << 1 | 1]) % MOD;
}
inline void calc(int &s1, int &s2, int len, int v) {
	up(s2, (1LL * len * v % MOD * v % MOD + 2LL * v * s1 % MOD) % MOD);
	up(s1, 1LL * len * v % MOD);
}
inline int pushDown(int n, int l, int r) {
	int mid = (l + r) >> 1;
	if (tag[n]) {
		calc(sum1[n << 1], sum2[n << 1], mid - l + 1, tag[n]);
		calc(sum1[n << 1 | 1], sum2[n << 1 | 1], r - mid, tag[n]);
		up(tag[n << 1], tag[n]);
		up(tag[n << 1 | 1], tag[n]);
		tag[n] = 0;
	}
	return mid;
}
void add(int n, int l, int r, int L, int R, int v) {
	if (l == L && r == R) {
		calc(sum1[n], sum2[n], r - l + 1, v);
		up(tag[n], v);
		return;
	}
	int mid = pushDown(n, l, r);
	if (R <= mid)
		add(n << 1, l, mid, L, R, v);
	else if (L > mid)
		add(n << 1 | 1, mid + 1, r, L, R, v);
	else
		add(n << 1, l, mid, L, mid, v), add(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	sum1[n] = (sum1[n << 1] + sum1[n << 1 | 1]) % MOD;
	sum2[n] = (sum2[n << 1] + sum2[n << 1 | 1]) % MOD;
}
int querySum1(int n, int l, int r, int L, int R) {
	if (l == L && r == R) return sum1[n];
	int mid = pushDown(n, l, r);
	if (R <= mid) return querySum1(n << 1, l, mid, L, R);
	if (L > mid) return querySum1(n << 1 | 1, mid + 1, r, L, R);
	return (querySum1(n << 1, l, mid, L, mid) + querySum1(n << 1 | 1, mid + 1, r, mid + 1, R)) % MOD;
}
int querySum2(int n, int l, int r, int L, int R) {
	if (l == L && r == R) return sum2[n];
	int mid = pushDown(n, l, r);
	if (R <= mid) return querySum2(n << 1, l, mid, L, R);
	if (L > mid) return querySum2(n << 1 | 1, mid + 1, r, L, R);
	return (querySum2(n << 1, l, mid, L, mid) + querySum2(n << 1 | 1, mid + 1, r, mid + 1, R)) % MOD;
}
inline void fuck(int x, int v) {
	add(1, 1, n, dfn[x], dfn[x] + size[x] - 1, v);
}
inline void gao(int x, int y, int v) {
	while (top[x] != top[y]) {
		if (deep[top[x]] < deep[top[y]]) std::swap(x, y);
		add(1, 1, n, dfn[top[x]], dfn[x], v);
		x = fa[top[x]];
	}
	if (deep[x] > deep[y]) std::swap(x, y);
	add(1, 1, n, dfn[x], dfn[y], v);
}
inline void cao(int x, int y) {
	int sum1 = 0, sum2 = 0;
	while (top[x] != top[y]) {
		if (deep[top[x]] < deep[top[y]]) std::swap(x, y);
		up(sum1, querySum1(1, 1, n, dfn[top[x]], dfn[x]));
		up(sum2, querySum2(1, 1, n, dfn[top[x]], dfn[x]));
		x = fa[top[x]];
	}
	if (deep[x] > deep[y]) std::swap(x, y);
	up(sum1, querySum1(1, 1, n, dfn[x], dfn[y]));
	up(sum2, querySum2(1, 1, n, dfn[x], dfn[y]));
	printf("%lld\n", (1LL * sum1 * sum1 % MOD - sum2 + MOD) % MOD * INV % MOD);
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
	memset(head, -1, sizeof(head));
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
	dfs(1);
	split(1);
	build(1, 1, n);
	for (int op, x, y, v; m; m--) {
		scanf("%d", &op);
		switch (op) {
			case 1:
				scanf("%d%d", &x, &v);
				fuck(x, v);
				break;
			case 2:
				scanf("%d%d%d", &x, &y, &v);
				gao(x, y, v);
				break;
			case 3:
				scanf("%d%d", &x, &y);
				cao(x, y);
				break;
		}
	}
	return 0;
}