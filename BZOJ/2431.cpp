#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
#define MOD 10000
int n, k, f[MAXN][MAXN];
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int main() {
	scanf("%d%d", &n, &k);
	f[1][0] = 1;
	for (int j = 1; j <= k; j++) up(f[1][j], f[1][j - 1]);
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j <= k; j++) {
			f[i][j] = f[i - 1][j];
			if (j - i >= 0) up(f[i][j], MOD - f[i - 1][j - i]);
		}
		for (int j = 1; j <= k; j++) up(f[i][j], f[i][j - 1]);
	}
	printf("%d\n", (f[n][k] - f[n][k - 1] + MOD) % MOD);
	return 0;
}