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
#define MOD 998244353
#define MAXN 500010
int n, m, head[MAXN], to[MAXN << 1], next[MAXN << 1], val[MAXN << 1], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int p[MAXN], f[MAXN], g[MAXN], d[MAXN], ans;
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
void dp(int x, int fa) {
	g[x] = d[x] & 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		dp(to[i], x);
		up(f[x], f[to[i]]);
		if (g[to[i]]) {
			up(f[x], val[i]);
			g[x] ^= 1;
		}
	}
}
int main() {
	n = $(), m = $();
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= n; i++) p[i] = i;
	for (int i = 1, u, v, w = 2; i <= m; i++) {
		u = $(), v = $();
		d[u]++, d[v]++;
		if (find(u) != find(v)) {
			p[find(u)] = find(v);
			$(u, v, w);
		}
		up(ans, w);
		w = (w << 1) % MOD;
	}
	dp(1, 0);
	up(ans, f[1]);
	printf("%d\n", ans);
	return 0;
}