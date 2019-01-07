#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 310
int n, k, m, f[MAXN][MAXN], g[MAXN][MAXN], c[MAXN][MAXN];
inline void up(int &x, int y) {
	if ((x += y) >= m) x -= m;
}
int main() {
	scanf("%d%d%d", &n, &k, &m);
	c[0][0] = 1;
	for (int i = 1; i < 300; i++) {
		c[i][0] = 1;
		for (int j = 1; j <= i; j++)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % m;
	}
	f[1][0] = 1;
	g[1][0] = 1;
	for (int i = 0; i <= k; i++) f[1][i] = 1;
	for (int i = k; i >= 0; i--) g[1][i] = (g[1][i + 1] + f[1][i]) % m;
	for (int i = 2; i <= n + 1; i++) {
		for (int j = 0; j <= k; j++) {
			for (int l = 1; l < i; l++) {
				up(f[i][j], 1LL * f[i - l][j] * g[l][j + 1] % m * c[i - 2][l - 1] % m);
			}
		}
		for (int j = k; j >= 0; j--) {
			g[i][j] = (g[i][j + 1] + f[i][j]) % m;
		}
	}
	printf("%d\n", f[n + 1][0]);
	return 0;
}