#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 110
#define MOD 998244353
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int n, m, k, a[MAXN], b[MAXN], f[MAXN * MAXN][MAXN], c[MAXN][MAXN], ans = 0;
int main() {
	scanf("%d", &n);
	c[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		c[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
		}
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		m += a[i];
		b[a[i]]++;
	}
	f[0][0] = 1;
	for (int pfx = 0, i = 0; i < n; pfx += a[++i]) {
		for (int c = pfx; ~c; c--) {
			for (int p = i; ~p; p--) {
				int &v = f[c][p];
				if (!v) continue;
				f[c + a[i + 1]][p + 1] += v;
			}
		}
	}
	for (int i = 1; i <= 100; i++) {
		k += !!b[i];
		for (int j = 1; j <= b[i]; j++) {
			if (f[i * j][j] == c[b[i]][j]) {
				ans = std::max(ans, j);
			}
		}
	}
	if (k <= 2) ans = n;
	printf("%d\n", ans);
	return 0;
}