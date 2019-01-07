#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2010
int n, ans, MOD, c[MAXN][MAXN], frc[MAXN];
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int main() {
	scanf("%d%d", &n, &MOD);
	c[0][0] = frc[0] = 1;
	for (int i = 1; i <= n; i++) {
		c[i][0] = 1;
		for (int j = 1; j <= n; j++) {
			up(c[i][j], c[i - 1][j - 1]);
			up(c[i][j], c[i - 1][j]);
		}
		frc[i] = 1LL * frc[i - 1] * i % MOD;
	}
	for (int i = 2; i <= n; i++) {
		for (int j = n - i + 1; j >= 1; j--) {
			up(ans, 1LL * j * (n - j) * c[n - i][j - 1] % MOD * frc[j] % MOD * frc[n - j - 1] % MOD * i % MOD * (i - 1) % MOD);
		}
	}
	printf("%d\n", ans);
	return 0;
}