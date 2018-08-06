#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 5010
int n, m, a[MAXN], f[MAXN][MAXN], pfx[MAXN][MAXN];
int main() {
	for (int i = scanf("%d", &n); i <= n; i++) scanf("%d", &a[i]);
	a[n + 1] = -0x3F3F3F3F;
	m = ceil(1. * n / 2);
	memset(f, 0x3F, sizeof(f));
	memset(pfx, 0x3F, sizeof(pfx));

	f[1][1] = 0;
	f[2][1] = std::max(0, a[1] - a[2] + 1);
	pfx[1][1] = std::max(0, a[2] - a[1] + 1);
	pfx[2][1] = f[2][1] + std::max(0, a[3] - a[2] + 1);
	pfx[2][1] = std::min(pfx[2][1], pfx[1][1]);
	for (int i = 3; i <= n; i++) {
		int dl = std::max(a[i - 1] - a[i] + 1, 0);
		int dr = std::max(a[i + 1] - a[i] + 1, 0);
		f[i][1] = dl;
		pfx[i][1] = std::min(pfx[i - 1][1], f[i][1] + dr);
		for (int j = 2; j <= m; j++) {
			f[i][j] = f[i - 2][j - 1] + std::max(a[i - 1] - std::min(a[i - 2], a[i]) + 1, 0);
			f[i][j] = std::min(f[i][j], pfx[i - 3][j - 1] + dl);
			pfx[i][j] = std::min(pfx[i - 1][j], f[i][j] + dr);
		}
	}
	for (int i = 1; i <= m; i++) printf("%d%c", pfx[n][i], " \n"[i == m]);
	return 0;
}