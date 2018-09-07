#include <algorithm>
#include <cstdio>
#include <iostream>
#define MAXN 100010
int n, k;
double p[MAXN], g[MAXN], f[MAXN][110];

int main() {
	std::cin >> n >> k;
	for (int i = 1; i <= n; i++) std::cin >> p[i];
	g[1] = p[1];
	for (int i = 2; i <= n; i++) g[i] = g[i - 1] + p[i];
	printf("%.4lf\n", g[n]);
	f[1][1] = p[1];
	f[1][0] = 1 - p[1];
	for (int i = 2; i <= n; i++) {
		f[i][0] = f[i - 1][0] * (1 - p[i]);
		for (int j = 1; j <= std::min(i, k); j++)
			f[i][j] = f[i - 1][j - 1] * p[i] + f[i - 1][j] * (1 - p[i]);
	}
	printf("%.4lf\n", f[n][k]);
	return 0;
}