#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
#define MOD 1000000007
inline int fuck(int x, int p) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
int n, m, ans, a[MAXN], b[MAXN], c[MAXN], f[MAXN], C[MAXN];
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int main() {
	for (int i = scanf("%d", &n); i <= n; i++) {
		scanf("%d%d", &a[i], &b[i]);
		c[++m] = a[i];
		c[++m] = ++b[i];
	}
	std::sort(c + 1, c + m + 1);
	m = std::unique(c + 1, c + m + 1) - c - 1;
	for (int i = 1; i <= n; i++) {
		a[i] = std::lower_bound(c + 1, c + m + 1, a[i]) - c;
		b[i] = std::lower_bound(c + 1, c + m + 1, b[i]) - c;
	}
	C[0] = f[0] = 1;
	for (int i = 1; i < m; i++) {
		int delta = c[i + 1] - c[i];
		for (int j = 1; j <= n; j++) C[j] = 1LL * C[j - 1] * (delta - 1 + j) % MOD * fuck(j, MOD - 2) % MOD;
		for (int j = n; j >= 1; j--) {
			if (a[j] > i || b[j] <= i) continue;
			for (int k = j, t = 0; k >= 1; k--) {
				if (a[k] <= i && b[k] > i) t++;
				up(f[j], 1LL * C[t] * f[k - 1] % MOD);
			}
		}
	}
	for (int i = 1; i <= n; i++) up(ans, f[i]);
	printf("%d\n", ans);
	return 0;
}