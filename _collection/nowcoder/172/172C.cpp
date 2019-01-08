#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline int $() {
	register int x = 0;
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#include <vector>
#define MAXN 400010
#define MAXM 8000010
int n, m, q, head[MAXN], next[MAXN << 1], to[MAXN << 1], tot = 0;
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
inline int lca(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) std::swap(u, v);
		u = fa[top[u]];
	}
	return deep[u] < deep[v] ? u : v;
}
std::vector<int> val[MAXN];
int root[MAXN], L[MAXM], R[MAXM], count[MAXM], cnt;
int insert(int n, int l, int r, int p) {
	int cur = ++cnt;
	L[cur] = L[n], R[cur] = R[n], count[cur] = count[n] + 1;
	if (l == r) return cur;
	int mid = (l + r) >> 1;
	p <= mid ? L[cur] = insert(L[n], l, mid, p) : R[cur] = insert(R[n], mid + 1, r, p);
	return cur;
}
int get(int n, int m, int l, int r, int k) {
	if (count[n] - count[m] < k) return -1;
	if (l == r) return l;
	int mid = (l + r) >> 1;
	if (count[L[n]] - count[L[m]] >= k) return get(L[n], L[m], l, mid, k);
	return get(R[n], R[m], mid + 1, r, k - (count[L[n]] - count[L[m]]));
}
int main() {
	n = $(), m = $();
	memset(head, -1, sizeof(head));
	for (int i = 1; i < n; i++) $($(), $());
	deep[1] = 1;
	dfs(1);
	split(1);
	for (int i = 1, u, v; i <= m; i++) {
		u = $(), v = $();
		int l = lca(u, v);
		val[u].push_back(deep[l]);
		val[v].push_back(deep[l]);
	}
	for (int i = 1; i <= n; i++) {
		root[i] = root[i - 1];
		for (auto x : val[pos[i]]) {
			root[i] = insert(root[i], 1, n, x);
		}
	}
	q = $();
	for (int u, v; q; q--) {
		u = $(), v = $();
		int result = get(root[dfn[u] + size[u] - 1], root[dfn[u] - 1], 1, n, v);
		printf("%d\n", (~result && result < deep[u]) ? deep[u] - result : 0);
	}
	return 0;
}