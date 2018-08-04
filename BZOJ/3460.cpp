#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, m, b, q, key, t[MAXN], block[MAXN];
int head[MAXN], to[MAXN], next[MAXN], tot = 0;
inline void $(int u, int v) { next[tot] = head[u], to[tot] = v, head[u] = tot++; }
int in[MAXN], out[MAXN], pos[MAXN], size[MAXN], deep[MAXN], fa[MAXN][20], root, dfsclk = 0;
void dfs(int x) {
	pos[in[x] = ++dfsclk] = x;
	size[x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		fa[to[i]][0] = x;
		deep[to[i]] = deep[x] + 1;
		dfs(to[i]);
		size[x] += size[to[i]];
	}
	pos[out[x] = ++dfsclk] = x;
}
inline int LCA(int x, int y) {
	if (deep[x] < deep[y]) std::swap(x, y);
	int delta = deep[x] - deep[y];
	for (int i = 19; ~i; i--)
		if ((delta >> i) & 1) x = fa[x][i];
	for (int i = 19; ~i; i--)
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return x == y ? x : fa[x][0];
}
struct query_t {
	int x, y, id;
	long long ans;
	inline query_t(int x = 0, int y = 0, int id = 0) {
		if (in[x] > in[y]) std::swap(x, y);
		int l = LCA(x, y);
		this->x = l == x ? in[x] : out[x];
		this->y = in[y];
		this->id = id;
	}
} query[MAXN];
char buf[MAXN];
inline int mpc(int a, int b) { return t[a] < t[b]; }
inline int cmp(const query_t& a, const query_t& b) { return block[a.x] == block[b.x] ? block[a.y] < block[b.y] : block[a.x] < block[b.x]; }
inline int rvt(const query_t& a, const query_t& b) { return a.id < b.id; }
int vis[MAXN], id[MAXN], rk[MAXN], bit0[MAXN];
long long ans, bit1[MAXN];
inline int lowbit(int x) { return x & -x; }
template <class T>
inline void add(T* BIT, int x, int y) {
	for (; x <= n; x += lowbit(x)) BIT[x] += y;
}
template <class T>
inline T qry(T* BIT, int x) {
	register T y = 0;
	for (; x; x -= lowbit(x)) y += BIT[x];
	return y;
}
inline void modify(int x) {
	int X = rk[x];
	if (vis[x]) {
		int count = qry(bit0, n) - qry(bit0, X) + 1;
		long long pre = qry(bit1, X);
		add(bit0, X, -1);
		add(bit1, X, -t[x]);
		ans -= 1LL * count * t[x];
		ans -= pre;
		vis[x] = 0;
	} else {
		add(bit0, X, 1);
		add(bit1, X, t[x]);
		int count = qry(bit0, n) - qry(bit0, X) + 1;
		long long pre = qry(bit1, X);
		ans += 1LL * count * t[x];
		ans += pre;
		vis[x] = 1;
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &key);
	for (int i = 1; i <= n; i++) scanf("%d", &t[i]), id[i] = i;
	std::sort(id + 1, id + n + 1, mpc);
	for (int i = 1; i <= n; i++) rk[id[i]] = i;
	memset(head, -1, sizeof(head));
	for (int i = 1, x; i <= n; i++) scanf("%d", &x), x ? $(x, i) : void(root = i);

	dfs(root);
	b = ceil(sqrt(dfsclk));
	for (int i = 1; i <= n; i++) block[i] = (i + b - 1) / b;
	for (int d = 1; d < 20; d++)
		for (int i = 1; i <= n; i++)
			fa[i][d] = fa[fa[i][d - 1]][d - 1];

	for (int i = 1, t = 1, g = 0, p; i <= m; i++) {
		scanf("%s%d", buf + 1, &p);
		if (buf[1] == 'C') {
			t = p;
		} else {
			query[++q] = query_t((p) % n + 1, t, ++g);
			query[++q] = query_t((p + key) % n + 1, t, ++g);
		}
	}

	std::sort(query + 1, query + q + 1, cmp);
	int l = 1, r = 0;
	for (int i = 1; i <= q; i++) {
		while (l > query[i].x) modify(pos[--l]);
		while (r < query[i].y) modify(pos[++r]);
		while (l < query[i].x) modify(pos[l++]);
		while (r > query[i].y) modify(pos[r--]);
		int lca = LCA(pos[query[i].x], pos[query[i].y]);
		if (lca != query[i].x) modify(lca);
		query[i].ans = ans;
		if (lca != query[i].x) modify(lca);
	}

	std::sort(query + 1, query + q + 1, rvt);
	for (int i = 1, lans = 0; i <= q; i += 2) {
		printf("%lld\n", query[i + lans].ans);
		lans = query[i + lans].ans & 1;
	}
	return 0;
}