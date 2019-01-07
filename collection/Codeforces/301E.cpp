#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 110
#define MOD 1000000007
const int INF = (~0U) >> 2;
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
int f[2][MAXN][MAXN][MAXN], n, m, limit, c[MAXN][MAXN], ans;
// f[maxinum][splitter][count][sum]
int main() {
	c[0][0] = 1;
	for (int i = 1; i < MAXN; i++) {
		c[i][0] = 1;
		for (int j = 1; j < MAXN; j++) {
			c[i][j] = std::min(c[i - 1][j - 1] + c[i - 1][j], INF);
		}
	}
	scanf("%d%d%d", &n, &m, &limit);
	for (int j = 1; j <= n; j++) f[1][j][j][1] = 1;
	for (int i = 1; i <= m; i++) {
		int now = i & 1, next = now ^ 1, tmp = 0;
		memset(f[next], 0, sizeof(f[next]));
		for (int k = 1; k <= n; k++) {
			for (int l = 1; l <= limit; l++) {
				up(tmp, f[now][0][k][l]);
			}
		}
		up(ans, 1LL * tmp * (m - i + 1) % MOD);
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {
				for (int l = 1; l <= limit; l++) {
					int &v = f[now][j][k][l];
					if (!v) continue;
					for (int t = j; t <= n - k; t++) {
						if (1LL * l * c[t - 1][j - 1] <= limit) {
							up(f[next][t - j][k + t][l * c[t - 1][j - 1]], v);
						}
					}
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}