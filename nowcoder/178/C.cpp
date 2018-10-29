#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int top[MAXN], fa[MAXN], deep[MAXN], size[MAXN], dfn[MAXN], pos[MAXN], dfsclk = 0;
void pre(int x) {
	size[x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x]) continue;
		fa[to[i]] = x;
		deep[to[i]] = deep[x] + 1;
		pre(to[i]);
		size[x] += size[to[i]];
	}
}
void split(int x) {
	if (!top[x]) top[x] = x;
	pos[dfn[x] = ++dfsclk] = x;
	int max = 0;
	for (int i = head[x]; ~i; i = next[i])
		if (to[i] != fa[x] && size[to[i]] > size[max]) max = to[i];
	if (max) top[max] = top[x], split(max);
	for (int i = head[x]; ~i; i = next[i])
		if (to[i] != fa[x] && to[i] != max) split(to[i]);
}
struct data {
	int c[3];
	inline data(int c0 = 0, int c1 = 0, int c2 = 0) {
		c[0] = c0, c[1] = c1, c[2] = c2;
	}
} vd[MAXN << 2], td[MAXN << 2];
struct info {
	int spec0, spec1, primary, secondary;
	inline info(int s0 = 0, int s1 = 0, int p = 0, int se = 0) : spec0(s0), spec1(s1), primary(p), secondary(se) {}
} vi[MAXN << 2], ti[MAXN << 2];
bool gd[MAXN << 2], gi[MAXN << 2];
inline int pushDown(int n, int l, int r) {
	int mid = (l + r) >> 1;
	if (gd[n]) {
		td[n << 1] = td[n];
		gd[n << 1] = gd[n];
		for (int i = 0; i < 3; i++) {
			vd[n << 1].c[i] = (mid - l + 1) * td[n].c[i];
		}
		td[n << 1 | 1] = td[n];
		gd[n << 1 | 1] = gd[n];
		for (int i = 0; i < 3; i++) {
			vd[n << 1 | 1].c[i] = (r - mid) * td[n].c[i];
		}
		gd[n] = 0;
	}
	if (gi[n]) {
		vi[n << 1] = ti[n << 1] = ti[n];
		vi[n << 1 | 1] = ti[n << 1 | 1] = ti[n];
		gi[n] = 0;
	}
	return mid;
}
inline data combine(data a, data b) {
	data c;
	for (int i = 0; i < 3; i++) c.c[i] = a.c[i] + b.c[i];
	return c;
}
inline void build(int n, int l, int r) {
	if (l == r) {
		vd[n] = data(1, 0, 0);
		return;
	}
	int mid = (l + r) >> 1;
	build(n << 1, l, mid);
	build(n << 1 | 1, mid + 1, r);
	vd[n] = combine(vd[n << 1], vd[n << 1 | 1]);
}
inline data query(int n, int l, int r, int L, int R) {
	if (L > R) return data(0, 0, 0);
	if (l == L && r == R) return vd[n];
	int mid = pushDown(n, l, r);
	if (R <= mid) return query(n << 1, l, mid, L, R);
	if (L > mid) return query(n << 1|1, mid + 1, r, L, R);
	return combine(query(n << 1, l, mid, L, mid), query(n << 1 | 1, mid + 1, r, mid + 1, R));
}
inline info get(int n, int l, int r, int p) {
	if (l == r) return vi[n];
	int mid = pushDown(n, l, r);
	return p <= mid ? get(n << 1, l, mid, p) : get(n << 1 | 1, mid + 1, r, p);
}
inline void cdata(int n, int l, int r, int L, int R, data d) {
	if (L > R) return;
	if (l == L && r == R) {
		for (int i = 0; i < 3; i++) {
			vd[n].c[i] = (r - l + 1) * d.c[i];
		}
		td[n] = d;
		gd[n] = 1;
		return;
	}
	int mid = pushDown(n, l, r);
	if (R <= mid)
		cdata(n << 1, l, mid, L, R, d);
	else if (L > mid)
		cdata(n << 1 | 1, mid + 1, r, L, R, d);
	else
		cdata(n << 1, l, mid, L, mid, d), cdata(n << 1 | 1, mid + 1, r, mid + 1, R, d);
	vd[n] = combine(vd[n << 1], vd[n << 1 | 1]);
}
inline void cinfo(int n, int l, int r, int L, int R, info i) {
	if (L > R) return;
	if (l == L && r == R) {
		vi[n] = ti[n] = i, gi[n] = 1;
		return;
	}
	int mid = pushDown(n, l, r);
	if (R <= mid) return cinfo(n << 1, l, mid, L, R, i);
	if (L > mid) return cinfo(n << 1 | 1, mid + 1, r, L, R, i);
	cinfo(n << 1, l, mid, L, mid, i);
	cinfo(n << 1 | 1, mid + 1, r, mid + 1, R, i);
}
inline int lca(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) std::swap(u, v);
		u = fa[top[u]];
	}
	return deep[u] < deep[v] ? u : v;
}
int n, m;
inline void query() {
	int u, v, l, col, ans = 0;
	scanf("%d%d%d", &u, &v, &col);
	l = lca(u, v);
	while (top[u] != top[l]) {
		auto res = query(1, 1, n, dfn[top[u]] + 1, dfn[u]);
		ans += res.c[col];
		auto info = get(1, 1, n, dfn[fa[top[u]]]);
		if (info.spec0 == top[u] || info.spec1 == top[u]) {
			ans += info.secondary == col;
		} else {
			ans += info.primary == col;
		}
		u = fa[top[u]];
	}
	while (top[v] != top[l]) {
		auto res = query(1, 1, n, dfn[top[v]] + 1, dfn[v]);
		ans += res.c[col];
		auto info = get(1, 1, n, dfn[fa[top[v]]]);
		if (info.spec0 == top[v] || info.spec1 == top[v]) {
			ans += info.secondary == col;
		} else {
			ans += info.primary == col;
		}
		v = fa[top[v]];
	}
	ans += query(1, 1, n, dfn[l] + 1, dfn[u]).c[col];
	ans += query(1, 1, n, dfn[l] + 1, dfn[v]).c[col];
	printf("%d\n", ans);
}
inline void gao(int u, int v, int c1, int c2) {
	cdata(1, 1, n, dfn[v] + 1, dfn[u], data(c1 == 0, c1 == 1, c1 == 2));
	// printf("CDATA %d - %d: %d %d %d\n", dfn[v] + 1, dfn[u], c1 == 0, c1 == 1, c1 == 2);
	cdata(1, 1, n, dfn[v], dfn[v], data(c2 == 0, c2 == 1, c2 == 2));
	// printf("CDATA %d - %d: %d %d %d\n", dfn[v], dfn[v], c2 == 0, c2 == 1, c2 == 2);
	cinfo(1, 1, n, dfn[v], dfn[u], info(0, 0, c2, 0));
	if (top[pos[dfn[u] + 1]] == top[u]) {
		cdata(1, 1, n, dfn[u] + 1, dfn[u] + 1, data(c2 == 0, c2 == 1, c2 == 2));
		// printf("CDATA %d - %d: %d %d %d\n", dfn[u] + 1, dfn[u] + 1, c2 == 0, c2 == 1, c2 == 2);
	}
}
inline void modify() {
	int u, v, l, col1, col2;
	scanf("%d%d%d%d", &u, &v, &col1, &col2);
	l = lca(u, v);
	int lastu = 0;
	while (top[u] != top[l]) {
		gao(u, top[u], col1, col2);
		cinfo(1, 1, n, dfn[u], dfn[u], info(lastu, 0, col2, col1));
		lastu = top[u];
		u = fa[top[u]];
	}
	int lastv = 0;
	while (top[v] != top[l]) {
		gao(v, top[v], col1, col2);
		cinfo(1, 1, n, dfn[v], dfn[v], info(lastv, 0, col2, col1));
		lastv = top[v];
		v = fa[top[v]];
	}
	gao(deep[u] < deep[v] ? v : u, l, col1, col2);
	if (u == v) {
		cinfo(1, 1, n, dfn[u], dfn[u], info(lastu, lastv, col2, col1));
	} else {
		cinfo(1, 1, n, dfn[u], dfn[u], info(lastu, 0, col2, col1));
		cinfo(1, 1, n, dfn[v], dfn[v], info(lastv, 0, col2, col1));
	}
}
inline void fuck() {
	int rt, x, col;
	scanf("%d%d%d", &rt, &x, &col);
	data d;
	d.c[col] = 1;
	info i;
	i.primary = col;
	if (rt == x) {
		cdata(1, 1, n, 1, n, d);
		cinfo(1, 1, n, 1, n, i);
	} else {
		int l = lca(rt, x);
		if (l == x) {
			int pre = rt;
			while (top[rt] != top[x]) pre = top[rt], rt = fa[top[rt]];
			pre = (rt == x) ? pre : pos[dfn[x] + 1];
			auto origin = get(1, 1, n, dfn[x]);
			int oc = (origin.spec0 == pre || origin.spec1 == pre) ? origin.secondary : origin.primary;
			int L = dfn[pre], R = dfn[pre] + size[pre] - 1;
			cdata(1, 1, n, 1, L - 1, d);
			cinfo(1, 1, n, 1, L - 1, i);
			cdata(1, 1, n, R + 1, n, d);
			cinfo(1, 1, n, R + 1, n, i);
			if (top[pre] == pre) {
				cinfo(1, 1, n, dfn[x], dfn[x], info(pre, 0, col, oc));
			}
		} else {
			cdata(1, 1, n, dfn[x] + 1, dfn[x] + size[x] - 1, d);
			cinfo(1, 1, n, dfn[x], dfn[x] + size[x] - 1, i);
		}
	}
}
int main() {
	memset(head, -1, sizeof(head));
	for (int i = scanf("%d", &n), u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
	pre(1), split(1);
	build(1, 1, n);
	for (int op = scanf("%d", &m); m; m--) {
		scanf("%d", &op);
		if (op == 1) {
			query();
		} else if (op == 2) {
			modify();
		} else {
			fuck();
		}
	}
	return 0;
}