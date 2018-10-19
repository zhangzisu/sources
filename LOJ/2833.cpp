#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 3010
#define MOD 1000000007
int n, m, f[MAXN][MAXN], ans;
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int main() {
	scanf("%d%d", &n, &m);
	f[n][m] = 1;
	for (int i = n; i; i--) {
		up(f[i - 1][0], f[i][0]);
		for (int j = m; j; j--) {
			up(f[i - 1][j], f[i][j]);
			up(f[i - 1][j - 1], 1LL * f[i][j] * 4 % MOD * j % MOD);
			if (i > 1) up(f[i - 2][j - 1], 1LL * f[i][j] * (i - 1) % MOD * j % MOD);
			if (j > 1) up(f[i - 1][j - 2], 1LL * f[i][j] * j % MOD * (j - 1) % MOD * 500000004 % MOD);
		}
	}
	for (int j = 0; j < m; j++) up(ans, f[0][j]);
	printf("%d\n", ans);
	return 0;
}