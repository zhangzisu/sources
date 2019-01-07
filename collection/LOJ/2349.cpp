#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 3010
int n, m, f[MAXN][3], ans = 0;
char buf[MAXN][MAXN], tmp[3][MAXN];
inline void upd(int &x, int y) {
	if (y > x) x = y;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%s", buf[i] + 1);
	for (int i = 2; i < n + m; i++) {
		memset(tmp, 0, sizeof(tmp));
		for (int j = 0; j < 3; j++)
			for (int k = 1; k <= m; k++) {
				int pos = i + j - k;
				if (pos >= 1 && pos <= n) tmp[j][k] = buf[pos][k];
			}
		memset(f, 0, sizeof(f));
		for (int j = 1; j <= m; j++) {
			upd(f[j][0], f[j - 1][0]);
			upd(f[j][0], f[j - 1][1]);
			upd(f[j][0], f[j - 1][2]);
			if (tmp[1][j] != 'G') continue;
			if (tmp[0][j] == 'R' && tmp[2][j] == 'W')
				upd(f[j][1], std::max(f[j - 1][0], f[j - 1][1]) + 1);
			if (tmp[0][j - 1] == 'R' && tmp[2][j + 1] == 'W')
				upd(f[j][2], std::max(f[j - 1][0], f[j - 1][2]) + 1);
		}
		ans += std::max(f[m][0], std::max(f[m][1], f[m][2]));
	}
	printf("%d\n", ans);
	return 0;
}
