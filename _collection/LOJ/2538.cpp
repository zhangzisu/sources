#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>

#define MAXN 3010
#define MOD 998244353
int t, n, m, k, a[MAXN], b[MAXN];
int f[MAXN][MAXN], g[MAXN][MAXN], s[MAXN][MAXN];
inline int fpow(int x, int p) {
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
int frc[MAXN], inv[MAXN];
inline int C(int n, int m) {
	if (n < 0 || m < 0 || n < m) return 0;
	return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD;
}
inline int F(int x, int y) {
	int ret = 0;
	for (int i = 0; i <= n; i++) up(ret, 1LL * f[y][i] * C(n - i, x - y) % MOD);
	return ret;
}
inline int G(int x, int y) {
	int ret = 0;
	for (int i = 0; i <= n; i++) up(ret, 1LL * g[y][i] * C(n - i, x - y) % MOD);
	return ret;
}
int main() {
	frc[0] = 1;
	for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
	inv[MAXN - 1] = fpow(frc[MAXN - 1], MOD - 2);
	for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;

	for (scanf("%d", &t); t; t--) {
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		std::sort(a + 1, a + n + 1, std::greater<int>());
		std::sort(b + 1, b + n + 1, std::greater<int>());
		memset(s, 0, sizeof(s));
		for (int i = 1; i <= n; i++) {
			for (int j = i; j <= n; j++) {
				f[i][j] = (1LL * a[j] * C(j - 1, i - 1) % MOD + s[i - 1][j - 1]) % MOD;
			}
			for (int j = 1; j <= n; j++) {
				s[i][j] = f[i][j];
				up(s[i][j], s[i][j - 1]);
			}
		}
		memset(s, 0, sizeof(s));
		g[0][0] = s[0][0] = 1;
		for (int i = 1; i <= n; i++) s[0][i] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = i; j <= n; j++) {
				g[i][j] = 1LL * b[j] * s[i - 1][j - 1] % MOD;
			}
			for (int j = 1; j <= n; j++) {
				s[i][j] = g[i][j];
				up(s[i][j], s[i][j - 1]);
			}
		}
		int ans = 0;
		for (int i = 1; i <= m; i++) {
			int atk = i;
			int upg = m - i;
			if (upg >= k) {
				up(ans, 1LL * F(atk, 1) * G(upg, k - 1) % MOD);
			} else {
				up(ans, 1LL * F(atk, k - upg) * G(upg, upg) % MOD);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}