#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2010
#define MOD 998244353
int f[MAXN][MAXN][2][2], n, k;
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int main() {
	scanf("%d%d", &n, &k);
	f[1][1][0][0] = 1;
	f[1][1][1][1] = 1;
	f[1][2][0][1] = 1;
	f[1][2][1][0] = 1;
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= n * 2; j++) {
			up(f[i + 1][j][0][0], f[i][j][0][0]);
			up(f[i + 1][j + 1][1][0], f[i][j][0][0]);
			up(f[i + 1][j + 1][0][1], f[i][j][0][0]);
			up(f[i + 1][j + 1][1][1], f[i][j][0][0]);

			up(f[i + 1][j][0][0], f[i][j][1][0]);
			up(f[i + 1][j][1][0], f[i][j][1][0]);
			up(f[i + 1][j + 2][0][1], f[i][j][1][0]);
			up(f[i + 1][j][1][1], f[i][j][1][0]);

			up(f[i + 1][j][0][0], f[i][j][0][1]);
			up(f[i + 1][j + 2][1][0], f[i][j][0][1]);
			up(f[i + 1][j][0][1], f[i][j][0][1]);
			up(f[i + 1][j][1][1], f[i][j][0][1]);

			up(f[i + 1][j + 1][0][0], f[i][j][1][1]);
			up(f[i + 1][j + 1][1][0], f[i][j][1][1]);
			up(f[i + 1][j + 1][0][1], f[i][j][1][1]);
			up(f[i + 1][j][1][1], f[i][j][1][1]);
		}
	}
	printf("%lld\n", ((long long)f[n][k][0][0] + f[n][k][0][1] + f[n][k][1][0] + f[n][k][1][1]) % MOD);
	return 0;
}