#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline void pc(char c) {
	if (_4 == _2 + BUF) fwrite(_2, 1, BUF, stdout), _4 = _2;
	*_4++ = c;
}
inline void rt() { fwrite(_2, 1, _4 - _2, stdout), exit(0); }
inline void pi(int x) {
	static int _5[32];
	if (!x) {
		pc('0');
		return;
	}
	if (x < 0) {
		pc(45);
		x = -x;
	}
	register int _6;
	for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
	while (_6) pc(_5[_6--] ^ 48);
}
inline int $() {
	register int x = 0;
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 200010
#define MAXK 51
#define MOD 998244353
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int top[MAXN], dfn[MAXN], fa[MAXN], deep[MAXN], pos[MAXN], size[MAXN], dfsclk;
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
int sum[MAXN << 2][MAXK], val[MAXN];
inline int get(int n, int l, int r, int L, int R, int d) {
	if (l == L && r == R) return sum[n][d];
	int mid = (l + r) >> 1;
	if (R <= mid) return get(n << 1, l, mid, L, R, d);
	if (L > mid) return get(n << 1 | 1, mid + 1, r, L, R, d);
	return get(n << 1, l, mid, L, mid, d) + get(n << 1 | 1, mid + 1, r, mid + 1, R, d);
}
void build(int n, int l, int r, int d) {
	if (l == r) return sum[n][d] = (val[pos[l]] == d), void();
	int mid = (l + r) >> 1;
	build(n << 1, l, mid, d);
	build(n << 1 | 1, mid + 1, r, d);
	sum[n][d] = sum[n << 1][d] + sum[n << 1 | 1][d];
}
int n, k, q, tmp[MAXK];
inline void get(int u, int v) {
	memset(tmp, 0, sizeof(tmp));
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) std::swap(u, v);
		for (int j = 0; j < k; j++) tmp[j] += get(1, 1, n, dfn[top[u]], dfn[u], j);
		u = fa[top[u]];
	}
	if (dfn[u] > dfn[v]) std::swap(u, v);
	for (int j = 0; j < k; j++) tmp[j] += get(1, 1, n, dfn[u], dfn[v], j);
}
int f[MAXK][MAXK], g[MAXK][MAXK], frc[MAXN], inv[MAXN];
inline int fuck(int x, int p) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline int C(int n, int m) {
	return n >= m ? 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD : 0;
}

int main() {
	frc[0] = 1;
	for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
	inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
	for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;

	memset(head, -1, sizeof(head));
	n = $(), k = $();
	for (int i = 1; i < n; i++) $($(), $());
	for (int i = 1; i <= n; i++) val[i] = $() % k;
	dfs(1);
	split(1);
	for (int i = 0; i < k; i++) build(1, 1, n, i);
	q = $();
	for (int u, v; q; q--) {
		u = $(), v = $();
		get(u, v);
		memset(f, 0, sizeof(f));
		for (int i = 0; i < k; i++) {
			for (int j = 0; j <= tmp[i]; j++) {
				up(f[i][(j * i) % k], C(tmp[i], j));
			}
		}
		memset(g, 0, sizeof(g));
		g[0][0] = 1;
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < k; j++) {
				for (int l = 0; l < k; l++) {
					up(g[i + 1][(j + l) % k], 1LL * g[i][j] * f[i][l] % MOD);
				}
			}
		}
		pi(g[k][0]);
		pc(10);
	}
	rt();
	return 0;
}