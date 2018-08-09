#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 4010
int n, a[MAXN], c[MAXN], f[MAXN][MAXN], p[2][MAXN];
int g[2][MAXN][MAXN], h[2][MAXN][MAXN];
char buf[3];
inline void up(int &x, int y) {
	if (y < x) x = y;
}
int main() {
	scanf("%d", &n);
	n <<= 1;
	for (int i = 1; i <= n; i++) {
		scanf("%s%d", buf, a + i);
		p[c[i] = buf[0] == 'B'][a[i]] = i;
	}
	for (int j = 0; j < 2; j++) {
		for (int i = 1; i <= n; i++) {
			for (int k = 1; k <= n; k++) {
				g[j][i][k] = g[j][i - 1][k] + (a[i] == k && c[i] == j);
			}
		}
	}
	for (int j = 0; j < 2; j++) {
		for (int i = 1; i <= n; i++) {
			for (int k = n; k >= 1; k--) {
				g[j][i][k] += g[j][i][k + 1];
			}
		}
	}
	for (int j = 0; j < 2; j++) {
		for (int i = n; i >= 1; i--) {
			for (int k = 1; k <= n; k++) {
				h[j][i][k] = h[j][i][k - 1];
			}
		}
	}
	memset(f, 0x3F, sizeof(f));
	f[0][0] = 0;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			for (int k = 0; k < 2; k++) {
				int pos = p[k][(k ? j : i) + 1];
				int cost = 0;
				cost += g[0][pos - 1][i + 1];
				cost += g[1][pos - 1][j + 1];
				cost += h[0][pos + 1][i - 1];
				cost += h[1][pos + 1][j - 1];
				up(f[i + !k][j + k], f[i][j] + cost);
			}
		}
	}
	printf("%d\n", f[n][n]);
	return 0;
}