#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
typedef unsigned long long ulnt;
const ulnt ALL = ~0ULL;
int n, m, k;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int fa[MAXN], deep[MAXN], size[MAXN], dfn[MAXN], top[MAXN], dfsclk = 0;
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
	dfn[x] = ++dfsclk;
	if (!top[x]) top[x] = x;
	int max = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x] || size[to[i]] <= size[max]) continue;
		max = to[i];
	}
	if (max) top[max] = top[x], split(max);
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x] || to[i] == max) continue;
		split(to[i]);
	}
}
struct data_t {
	ulnt l0, l1, r0, r1;
	inline data_t(ulnt l0 = 0, ulnt l1 = ALL, ulnt r0 = 0, ulnt r1 = ALL) : l0(l0), l1(l1), r0(r0), r1(r1) {}
	inline data_t friend operator+(const data_t &a, const data_t &b) {
		return data_t((a.l0 & b.l1) | (~a.l0 & b.l0), (a.l1 & b.l1) | (~a.l1 & b.l0), (b.r0 & a.r1) | (~b.r0 & a.r0), (b.r1 & a.r1) | (~b.r1 & a.r0));
	}
} val[MAXN << 2];
void modify(int n, int l, int r, int p, data_t v) {
	if (l == r) return val[n] = v, void();
	int mid = (l + r) >> 1;
	p <= mid ? modify(n << 1, l, mid, p, v) : modify(n << 1 | 1, mid + 1, r, p, v);
	val[n] = val[n << 1] + val[n << 1 | 1];
}
data_t query(int n, int l, int r, int L, int R) {
	if (l == L && r == R) return val[n];
	int mid = (l + r) >> 1;
	if (R <= mid) return query(n << 1, l, mid, L, R);
	if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R);
	return query(n << 1, l, mid, L, mid) + query(n << 1 | 1, mid + 1, r, mid + 1, R);
}
inline void gao(int x, int y, ulnt val) {
	if (y == 1) {
		modify(1, 1, n, dfn[x], data_t(0 & val, ALL & val, 0 & val, ALL & val));
	} else if (y == 2) {
		modify(1, 1, n, dfn[x], data_t(0 | val, ALL | val, 0 | val, ALL | val));
	} else if (y == 3) {
		modify(1, 1, n, dfn[x], data_t(0 ^ val, ALL ^ val, 0 ^ val, ALL ^ val));
	}
}
int kind[MAXN];
ulnt init[MAXN];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= n; i++) scanf("%d%llu", kind + i, init + i);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		$(u, v);
	}
	pre(1);
	split(1);
	for (int i = 1; i <= n; i++) gao(i, kind[i], init[i]);
	for (int opt, x, y; m; m--) {
		ulnt val;
		scanf("%d%d%d%llu", &opt, &x, &y, &val);
		if (opt == 1) {
			data_t up, down;
			while (top[x] != top[y]) {
				if (deep[top[x]] < deep[top[y]]) {
					down = query(1, 1, n, dfn[top[y]], dfn[y]) + down;
					y = fa[top[y]];
				} else {
					up = query(1, 1, n, dfn[top[x]], dfn[x]) + up;
					x = fa[top[x]];
				}
			}
			if (deep[x] < deep[y]) {
				down = query(1, 1, n, dfn[x], dfn[y]) + down;
			} else {
				up = query(1, 1, n, dfn[y], dfn[x]) + up;
			}
			ulnt v0 = (up.r0 & down.l1) | (~up.r0 & down.l0), v1 = (up.r1 & down.l1) | (~up.r1 & down.l0), now = 0, ans = 0;
			for (int i = k - 1; ~i; i--) {
				if (((v0 >> i) & 1) || !((v1 >> i) & 1) || (now + (1LL << i) > val)) {
					ans += v0 & (1LL << i);
				} else {
					ans += v1 & (1LL << i);
					now += 1LL << i;
				}
			}
			printf("%llu\n", ans);
		} else {
			gao(x, y, val);
		}
	}
	return 0;
}