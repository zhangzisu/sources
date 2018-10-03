#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
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
int n, m, a[201][201], s[4][201][201][101], ans[201][201];
inline bool valid(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m;
}
inline int $(int x, int y) {
	return valid(x, y) ? a[x][y] : 0;
}
int main() {
	scanf("%d%d", &n, &m);
	int fucker = std::min(n, m) / 2;
	for (int i = 1, x; i <= n; i++) {
		for (int j = 1, y; j <= m; j++) {
			scanf("%d%d", &x, &y);
			a[i][j] = 1LL * x * fuck(y, MOD - 2) % MOD;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int *p = s[0][i][j];
			p[0] = a[i][j];
			for (int k = 1; k <= fucker; k++) {
				p[k] = 1LL * p[k - 1] * $(i + k, j + k) % MOD;
			}
			p = s[1][i][j];
			p[0] = a[i][j];
			for (int k = 1; k <= fucker; k++) {
				p[k] = 1LL * p[k - 1] * $(i + k, j - k) % MOD;
			}
			p = s[2][i][j];
			p[0] = a[i][j];
			for (int k = 1; k <= fucker; k++) {
				p[k] = 1LL * p[k - 1] * $(i - k, j + k) % MOD;
			}
			p = s[3][i][j];
			p[0] = a[i][j];
			for (int k = 1; k <= fucker; k++) {
				p[k] = 1LL * p[k - 1] * $(i - k, j - k) % MOD;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int p = a[i][j];
			up(ans[i][j], p);
			for (int k = 1; k <= fucker; k++) {
				if (!valid(i - k, j) || !valid(i, j - k) || !valid(i + k, j) || !valid(i, j + k)) break;
				int *q = s[0][i - k][j];
				int *w = s[1][i][j + k];
				int *e = s[3][i + k][j];
				int *r = s[2][i][j - k];
				p = 1LL * p * q[k - 1] % MOD * e[k - 1] % MOD * w[k - 1] % MOD * r[k - 1] % MOD;
				up(ans[i][j], p);
				if (!p) break;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) printf("%d ", ans[i][j]);
		puts("");
	}
	return 0;
}
