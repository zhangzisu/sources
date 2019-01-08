#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
#define MAXN 2010
int n, p[MAXN][4], w[4][4], f[2][MAXN], tmp[MAXN], ans[MAXN];
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
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d%d%d", p[i], p[i] + 1, p[i] + 2, p[i] + 3);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) scanf("%d", &w[i][j]);
	for (int d = 0; d < 4; d++) {
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for (int i = 1; i <= n; i++) {
			int now = i & 1, pre = now ^ 1;
			memset(f[now], 0, sizeof(f[now]));
			int ok = p[i][d], uok = MOD + 1 - p[i][d];
			for (int j = 0; j <= n; j++) {
				f[now][j] = 1LL * f[pre][j] * uok % MOD;
				if (j) up(f[now][j], 1LL * f[pre][j - 1] * ok % MOD);
			}
		}
		for (int i = 1; i <= n; i++) {
			int pre = n & 1, now = pre ^ 1;
			memset(f[now], 0, sizeof(f[now]));
			memcpy(tmp, f[pre], sizeof(tmp));
			int ok = p[i][d], iok = fuck(ok, MOD - 2), uok = MOD + 1 - p[i][d];
			for (int j = n; j >= 1; j--) {
				f[now][j - 1] = 1LL * tmp[j] * iok % MOD;
				up(tmp[j - 1], MOD - 1LL * f[now][j - 1] * uok % MOD);
			}
			for (int j = 0; j <= n; j++) {
				for (int k = 0; k < 4; k++) {
					if (j + (k == d) <= n / 2) continue;
					up(ans[i], 1LL * p[i][k] * w[d][k] % MOD * f[now][j] % MOD);
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}