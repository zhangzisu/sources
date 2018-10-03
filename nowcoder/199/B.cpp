#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MOD 1000000007
int n, l, r, ans;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int size[MAXN], fa[MAXN], f[MAXN], g[MAXN];
int _s[MAXN << 1], *s = _s + MAXN, _c[MAXN << 1], *c = _c + MAXN;
void dp(int x) {
	size[x] = 1;
	f[x] = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x]) continue;
		fa[to[i]] = x;
		dp(to[i]);
		up(f[x], 1LL * size[x] * size[to[i]] % MOD);
		size[x] += size[to[i]];
	}
}
void dfs(int x, int deep) {
	s[deep] = s[deep - 1];
	up(s[deep], g[x]);
	c[deep] = c[deep - 1];
	up(c[deep], 1);

	int sum = s[deep - l + 1];
	up(sum, MOD - s[deep - r]);
	int cnt = c[deep - l];
	up(cnt, MOD - c[deep - r - 1]);

	up(ans, 1LL * f[x] * sum * 2 % MOD);
	up(ans, sum);
	up(ans, 1LL * f[x] * cnt % MOD);
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x]) continue;
		dfs(to[i], deep + 1);
	}
}
int main() {
	scanf("%d%d%d", &n, &l, &r);
	memset(head, -1, sizeof(head));
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		$(u, v);
	}
	dp(1);
	for (int i = 2; i <= n; i++) {
		g[i] = f[fa[i]];
		up(g[i], MOD - 1LL * (size[fa[i]] - size[i]) * size[i] % MOD);
		up(g[i], 1LL * (n - size[fa[i]]) * (size[fa[i]] - size[i]) % MOD);
	}
	dfs(1, 1);
	printf("%d\n", ans);
	return 0;
}