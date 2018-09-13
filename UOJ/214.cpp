#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 50
#define MOD 998244353
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
int t, n, m, all, can[MAXN][MAXN], vis[MAXN][MAXN], goal[MAXN], inv[MAXN];
char buf[MAXN];
int main() {
	for (int i = 1; i < MAXN; i++) inv[i] = fuck(i, MOD - 2);
	for (scanf("%d", &t); t; t--) {
		scanf("%d%d", &n, &m);
		memset(can, 0, sizeof(can));
		for (int i = 1, len; i <= n; i++) {
			scanf("%s", buf + 1);
			len = strlen(buf + 1);
			for (int j = 1; j <= len; j++) can[i][buf[j] - 'a'] = 1, all++;
		}
		scanf("%s", buf + 1);
		for (int i = 1; i <= m; i++) goal[i] = buf[i] - 'a';
		for (int i = 1; i <= n - m + 1; i++) {
			for (int j = 1; j <= m; j++) {
				if (!a[i + j - 1][goal[j]]) goto fail;
			}
			goto succ;
		fail:;
		}
		puts("-1");
		continue;
	succ:
		int count = n - m + 1;
		for (int i = 1; i < (1 << count); i++) {
			int need = 0, sum = 0;
			for (int j = 0; j < count; j++) {
				for (int k = 1; k <= m; k++) {
					if (can[j + k][goal[k]] && !vis[j + k][goal[k]]) {
						vis[j + k][goal[k]] = 1;
						need++;
					}
				}
			}
			for (int i = 1; i <= count; i++) up(sum, 1LL * inv[i] * all);
            //
			for (int j = 0; j < count; j++) {
				for (int k = 1; k <= m; k++) {
					if (can[j + k][goal[k]]) {
						vis[j + k][goal[k]] = 0;
					}
				}
			}
		}
	}
	return 0;
}