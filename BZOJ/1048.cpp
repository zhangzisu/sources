#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
bool vis[11][11][11][11][11];
double val[11][11][11][11][11], avg;
int a, b, n, v[11][11], s[11][11];
double dp(int x0, int y0, int x1, int y1, int k) {
	if (vis[x0][y0][x1][y1][k]) return val[x0][y0][x1][y1][k];
	vis[x0][y0][x1][y1][k] = 1;
	double ret = 1e100;
	if (k == 1) {
		ret = s[x1][y1] - s[x1][y0 - 1] - s[x0 - 1][y1] + s[x0 - 1][y0 - 1];
		return val[x0][y0][x1][y1][k] = (ret - avg) * (ret - avg);
	}
	for (int i = x0; i < x1; i++) {
		for (int j = 1; j < k; j++) {
			ret = std::min(ret, dp(x0, y0, i, y1, j) + dp(i + 1, y0, x1, y1, k - j));
		}
	}
	for (int i = y0; i < y1; i++) {
		for (int j = 1; j < k; j++) {
			ret = std::min(ret, dp(x0, y0, x1, i, j) + dp(x0, i + 1, x1, y1, k - j));
		}
	}
	return val[x0][y0][x1][y1][k] = ret;
}
int main() {
	scanf("%d%d%d", &a, &b, &n);
	for (int i = 1; i <= a; i++) {
		for (int j = 1; j <= b; j++) {
			scanf("%d", &v[i][j]);
			s[i][j] = v[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
		}
	}
	avg = 1. * s[a][b] / n;
	printf("%.2f\n", sqrt(dp(1, 1, a, b, n) / n));
	return 0;
}