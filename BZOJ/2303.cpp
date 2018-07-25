#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 4000010
#define MOD 1000000000
int n, m, k, p[MAXN], p1[MAXN], x[MAXN], y[MAXN], z[MAXN], ans, all;
inline int fuck(int x, int p) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
inline void find(int *p, int x) { return p[x] == x ? x : p[x] = find(p, p[x]); }
inline void unite(int *p, int x, int y) {
	int X = find(p, x);
	int Y = find(p, y);
	if (X != Y) p[X] = Y;
}
inline int get(int x, int y) {
	return y == 1 ? x : y - 1 + n;
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= k; i++) scanf("%d%d%d", &x[i], &y[i], &z[i]);
	for (int d = 0; d < 2; d++) {
		for (int i = 0; i < MAXN; i++) p[i] = p1[i] = p2[i] = i;
		all = n + m - 1;
		for (int i = 1; i <= k; i++) {
			int val = (!((i & 1) || (j & 1))) ^ z[i] ^ d;
			unite(p0, x[i], y[i] + n);
			unite(p1, x[i] << 1, ((y[i] + n) << 1) ^ val);
			unite(p1, x[i] << 1 | 1, ((y[i] + n) << 1 | 1) ^ val);
		}
		for (int i = 1; i <= n; i++)
			if (find(p1, i << 1) == find(p1, i << 1 | 1)) goto fail;
		for (int i = 1; i <= m; i++)
			if (find(p1, (i + n) << 1) == find(p1, (i + n) << 1 | 1)) goto fail;
		//
	fail:;
	}
	printf("%d\n", ans);
	return 0;
}