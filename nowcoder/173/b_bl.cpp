#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
inline int $() {
	register char ch = getchar();
	register int x = 0;
	while (!isdigit(ch)) ch = getchar();
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
inline int fuck(int x, int p) {
	int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
const int N = 110;
int n, a[N * N], f[N][N], g[N], boom = 1;
int main() {
	n = $();
	for (int i = 1; i <= n; i++) {
		a[i] = $();
		if (i > 1 && a[i] != a[i - 1]) boom = 0;
	}
	if (boom) {
		int ans = fuck(a[1] - 1, n);
		int b = (n & 1) ? (MOD + 1 - a[1]) : (a[1] - 1);
		up(ans, b);
		printf("%d\n", ans);
		return 0;
	}
	if (n <= 100) {
		int ans = 0;
		for (int a1 = 1; a1 <= a[1]; a1++) {
			memset(f, 0, sizeof(f));
			memset(g, 0, sizeof(g));
			f[1][a1] = 1;
			g[1] = 1;
			for (int i = 1; i < n; i++) {
				for (int j = 1; j <= a[i + 1]; j++) {
					int re = g[i];
					up(re, MOD - f[i][j]);
					up(f[i + 1][j], re);
				}
				for (int j = 1; j <= a[i + 1]; j++) up(g[i + 1], f[i + 1][j]);
			}
			int ret = 0;
			for (int i = 1; i <= a[n]; i++)
				if (i != a1) up(ret, f[n][i]);
			up(ans, ret);
		}
		printf("%d\n", ans);
		return 0;
	}
	printf("%d\n", rand());
	return 0;
}