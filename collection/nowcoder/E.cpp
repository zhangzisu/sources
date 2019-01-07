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
	register int x = 0, f = 0;
	register char ch = gc();
	while (!isdigit(ch) && (ch ^ 45)) ch = gc();
	if (!(ch ^ 45)) f = 1, ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return f ? -x : x;
}
#define MAXN 100010
#define LOGN 16
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int u[MAXN], v[MAXN], w[MAXN];
int n, m, vis[MAXN], fa[MAXN][16], cnt[MAXN], a[MAXN];
int size[MAXN], nice[MAXN], in[MAXN][16], out[MAXN][16], all, root, dfsclk;
typedef long long lnt;
// f: Subtree rooted as i, which ans is f[i]
// g: Subtree rooted as i, which make g[i] to its father
inline int lowbit(int x) { return x & -x; }
struct BIT {
	lnt *BIT;
	int n;
	inline BIT() {}
	inline BIT(int n) {
		this->n = n;
		BIT = (int *)calloc(n + 1, sizeof(lnt));
		memset(BIT, 0, sizeof(lnt) * (n + 1));
	}
	inline void add(int x, lnt v) {
		for (; x; x += lowbit(x)) BIT[x] += v;
	}
	inline lnt query(int x) {
		lnt v = 0;
		for (; x; x -= lowbit(x)) v += BIT[x];
		return v;
	}
} bita[MAXN], bitb[MAXN];
lnt f[MAXN], g[MAXN], ss[MAXN][16];
void getSize(int x, int fa) {
	size[x] = 1;
	nice[x] = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa || vis[to[i]]) continue;
		getSize(to[i], x);
		size[x] += size[to[i]];
		nice[x] = std::max(nice[x], size[to[i]]);
	}
	nice[x] = std::max(nice[x], all - size[x]);
	if (nice[x] < nice[root]) root = x;
}
void fill(int x, int fa, int v, lnt d) {
	fa[x][++cnt[x]] = v;
	bita[v].add(in[x][cnt[x]] = ++dfsclk, a[x]);
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa || vis[to[i]]) continue;
		fill(to[i], x, v, d + val[i]);
		ss[x][cnt[x]] += ss[to[i]][cnt[x]];
	}
	out[x][cnt[x]] = dfsclk;
}
void solve(int x) {
	vis[x] = 1;
	getSize(x);
	bita[x] = BIT(all = size[x]);
	dfsclk = 0;
	fa[x][++cnt[x]] = x;
	bita[x].add(in[x][cnt[x]] = ++dfsclk, a[x]);
	for (int i = head[x]; ~i; i = next[i]) {
		if (vis[to[i]]) continue;
		fill(to[i], x, x);
	}
	for (int i = head[x]; ~i; i = next[i]) {
		all = size[to[i]];
		root = 0;
		getSize(to[i]);
		solve(to[i]);
	}
}
inline void query(int x) {
	lnt last = 0;
	lnt ans = 0;
	for (int i = cnt[x]; i; i--) {
		lnt tmp = f[fa[x][i]];
		ans += tmp - last;
		last = g[fa[x][i]];
	}
	printf("%lld\n", ans);
}
inline void modify(int x, int v) {
	int delta = v - a[i];
	for (int i = cnt[x]; i; i--) {
		f[fa[x][i]] += delta * bitb[fa[x][i]].query(in[x][i]);
		g[fa[x][i]] += delta * bitb[fa[x][i - 1]].query(in[x][i - 1]);
		bita[fa[x][i]].add(in[x][i], delta);
	}
	a[i] = v;
}
inline void change(int x, int v) {
	int u = u[x];
	int v = v[x];
	int delta = w[x];
	if (fa[u][cnt[u]] == fa[v][cnt[v]]) {
		for (int i = cnt[u]; i; i--) {
			int p = fa[::u[x]][i], y = fa[::u[x]][i-1];
			if(in[u][i] > in[v][i])std::swap(u, v);
			bitb[p].add(in[v][i], delta);
			f[p] += delta * (bita[p].query(in[v]) - bita[p].query(out[v] - 1));
			g[fa[u][i-1]] += delta * (bita[fa[u][i-1]].query(in[v]) - bita[fa[u][i - 1]].query(out[v] - 1));
		}
	} else if (fa[u][cnt[u]] == v) {
		//
		for (int i = cnt[v]; i; i--) {
			if(in[u][i] > in[v][i])std::swap(u, v);
			bitb[fa[u][i]].add(in[v][i], delta);
			f[fa[u][i]] += delta * (bita[fa[u][i]].query(in[v]) - bita[fa[u][i]].query(out[v] - 1));
			g[fa[u][i-1]] += delta * (bita[fa[u][i-1]].query(in[v]) - bita[fa[u][i - 1]].query(out[v] - 1));
		}
	} else {
		for (int i = cnt[u]; i; i--) {
			if(in[u][i] > in[v][i])std::swap(u, v);
			bitb[fa[u][i]].add(in[v][i], delta);
			f[fa[u][i]] += delta * (bita[fa[u][i]].query(in[v]) - bita[fa[u][i]].query(out[v] - 1));
			g[fa[u][i-1]] += delta * (bita[fa[u][i-1]].query(in[v]) - bita[fa[u][i - 1]].query(out[v] - 1));
		}
	}
	w[x] = v;
}
int main() {
	n = $(), m = $();
	memset(head, -1, sizeof(head));
	for (int i = 1; i < n; i++) {
		u[i] = $(), v[i] = $(), w[i] = $();
		$(u[i], v[i]);
	}
	nice[0] = 0x3F3F3F3F;
	getSize(1, 0);
	solve(root);
	for (int i = 1; i <= n; i++) modify(i, $());
	for (int i = 1; i < m; i++) {
		change(i, w[i]);
	}
	for (int op, x, y; m; m--) {
		op = $();
		if (op == 1) {
			x = $(), y = $();
			modify(x, y);
		} else if (op == 2) {
			x = $(), y = $();
			change(x, y);
		} else if (op == 3) {
			query($());
		}
	}
	return 0;
}