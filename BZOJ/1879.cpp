#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000003
int t, n, m, k, all, ans, f[100][1 << 15], g[100][26];
char buf[20][100];
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int main() {
	for (scanf("%d", &t); t; t--) {
		scanf("%d%d", &n, &k);
		for (int i = 0; i < n; i++) scanf("%s", buf[i]);
		m = strlen(buf[0]);
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		all = (1 << n) - 1;
		ans = 0;
		f[0][all] = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < 26; k++) {
					if (buf[i][j] == '?' || buf[i][j] == k + 'a')
						g[j][k] |= 1 << i;
				}
			}
		}
		for (int i = 0; i < m; i++) {
			for (int d = 0; d <= all; d++) {
				if (!f[i][d]) continue;
				for (int c = 0; c < 26; c++)
					up(f[i + 1][d & g[i][c]], f[i][d]);
			}
		}
		for (int d = 0; d <= all; d++)
			if (__builtin_popcount(d) == k) up(ans, f[m][d]);
		printf("%d\n", ans);
	}
	return 0;
}