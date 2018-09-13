#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 21
#define MAXM 10010
#define MOD 998244353
int n, m, p, all, u[MAXM], v[MAXM], w[MAXN], c[MAXN], fa[MAXN];
inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline int fuck(int x, int p) {
	int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
int f[MAXN + 1][1 << MAXN], g[MAXN + 1][1 << MAXN], h[1 << MAXN], s[1 << MAXN], is[1 << MAXN];
inline void FWT(int *a, int n) {
	for (int i = 1; i < n; i <<= 1) {
		int t = i << 1;
		for (int j = 0; j < n; j += t) {
			for (int k = 0; k < i; k++) {
				up(a[j + k + i], a[j + k]);
			}
		}
	}
}
inline void IFWT(int *a, int n) {
	for (int i = 1; i < n; i <<= 1) {
		int t = i << 1;
		for (int j = 0; j < n; j += t) {
			for (int k = 0; k < i; k++) {
				up(a[j + k + i], MOD - a[j + k]);
			}
		}
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &p);
	for (int i = 0; i < m; i++) scanf("%d%d", &u[i], &v[i]), u[i]--, v[i]--;
	for (int i = 0; i < n; i++) scanf("%d", &w[i]);
	all = 1 << n;
	for (int d = 0; d < all; d++) {
		int count = 0;
		for (int i = 0; i < n; i++)
			if ((d >> i) & 1)
				up(s[d], w[i]), c[i] = 0, fa[i] = i, ++count;
		s[d] = fuck(s[d], p);
		is[d] = fuck(s[d], MOD - 2);
		for (int i = 0; i < m; i++) {
			if (((d >> u[i]) & 1) && ((d >> v[i]) & 1)) {
				c[u[i]]++, c[v[i]]++;
				if (find(u[i]) != find(v[i])) {
					count--;
					fa[find(u[i])] = find(v[i]);
				}
			}
		}
		h[d] = count > 1;
		for (int i = 0; i < n; i++)
			if ((d >> i) & 1)
				h[d] |= (c[i] & 1);
	}
	for (int d = 0; d < all; d++) g[__builtin_popcount(d)][d] = h[d] * s[d];
	for (int i = 0; i <= n; i++) FWT(g[i], all);
	f[0][0] = 1;
	FWT(f[0], all);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			for (int k = 0; k < all; k++) {
				up(f[i][k], 1LL * g[j][k] * f[i - j][k] % MOD);
			}
		}
		IFWT(f[i], all);
		for (int j = 0; j < all; j++) f[i][j] = 1LL * f[i][j] * is[j] % MOD;
		FWT(f[i], all);
	}
	IFWT(f[n], all);
	printf("%d\n", f[n][all - 1]);
	return 0;
}
