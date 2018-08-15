#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
int n, m, f[1 << 15], g[15][1 << 15], h[15][1 << 15], bin[150];
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline int lowbit(int x) { return x & -x; }
int main() {
	scanf("%d%d", &n, &m);
	bin[0] = 1;
	for (int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v);
		u--, v--;
		g[u][1 << v] = 1;
		bin[i] = (bin[i - 1] << 1) % MOD;
	}
	for (int i = 0; i < n; i++) {
		for (int d = 1; d < (1 << n); d++) {
			g[i][d] = g[i][d - lowbit(d)] + g[i][lowbit(d)];
		}
	}
	f[0] = 1;
	for (int d = 1; d < (1 << n); d++) {
		for (int x = d; x; x = (x - 1) & d) {
			if ((x & 1) == ((x >> 1) & 1)) {
				int tmp = 1;
				for (int i = 0; i < n; i++) {
					if ((d >> i) & 1) {
						if ((x >> i) & 1) {
							tmp = 1LL * tmp * bin[g[i][d - x]] % MOD;
						} else {
							tmp = 1LL * tmp * (bin[g[i][x]] - 1) % MOD;
						}
					}
				}
				up(f[d], 1LL * tmp * f[d - x] % MOD);
			}
		}
	}
	printf("%d\n", (bin[m] - f[(1 << n) - 1] + MOD) % MOD);
	return 0;
}