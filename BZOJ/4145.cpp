#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int MAXN = 101;
const int MAXM = 16;
int n, m, d[MAXN], c[MAXN][MAXM], f[MAXN][1 << MAXM];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &d[i]);
		for (int j = 0; j < m; j++) scanf("%d", &c[i][j]);
	}
	memset(f, 0x3F, sizeof(f));
	f[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < (1 << m); j++) f[i][j] = f[i - 1][j] + d[i];
		for (int j = 0; j < (1 << m); j++)
			for (int k = 0; k < m; k++)
				if ((j >> k) & 1)
					f[i][j] = std::min(f[i][j], f[i][j - (1 << k)] + c[i][k]);
		for (int j = 0; j < (1 << m); j++) f[i][j] = std::min(f[i][j], f[i - 1][j]);
	}
	printf("%d\n", f[n][(1 << m) - 1]);
	return 0;
}