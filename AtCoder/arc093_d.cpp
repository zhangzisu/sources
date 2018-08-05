#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define popcount(x) __builtin_popcount(x)
#define MOD 1000000007
#define MAXN 100010
inline int fuck(int x, int p) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
int n, m, k, a[20], f[20][MAXN], frc[MAXN], inv[MAXN], ans;
inline int P(int n, int m) {
	if (m > n) return 0;
	return 1LL * frc[n] * inv[n - m] % MOD;
}
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int main() {
	scanf("%d%d", &n, &m);
	k = 1 << n;
	for (int i = 1; i <= m; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + m + 1, [](int a, int b) { return a > b; });

	frc[0] = 1;
	for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
	inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
	for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;

	f[0][0] = 1;
	for (int i = 0; i < m; i++) {
		for (int d = 0; d < k; d++) {
			if (!f[i][d]) continue;
			up(f[i + 1][d], f[i][d]);
			int can = k - d - a[i + 1];
			for (int j = 0; j < n; j++) {
				if ((d >> j) & 1) continue;
				up(f[i + 1][d | (1 << j)], 1LL * f[i][d] * P(can, (1 << j) - 1) % MOD * (1 << j) % MOD);
			}
		}
	}
	ans = frc[k - 1];
	for (int d = 1; d < k; d++) f[m][d] = 1LL * f[m][d] * frc[k - d - 1] % MOD, up(ans, (popcount(d) & 1) ? MOD - f[m][d] : f[m][d]);
	printf("%lld\n", 1LL * ans * (1 << n) % MOD);
	return 0;
}