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
int t, n, m, c, all, can[MAXN][MAXN], vis[MAXN][MAXN], goal[MAXN], inv[MAXN * MAXN], sum[MAXN * MAXN], ok[MAXN];
char buf[MAXN];
int calc(int d, int k, int flag) {
	if (d > c) return flag ? MOD - sum[k] : sum[k];
	int ret = calc(d + 1, k, flag);
	if (ok[d]) {
		for (int i = 1; i <= m; i++) {
			if (!vis[d + i - 1][goal[i]]) k++;
			vis[d + i - 1][goal[i]]++;
		}
		up(ret, calc(d + 1, k, flag ^ 1));
		for (int i = 1; i <= m; i++) {
			vis[d + i - 1][goal[i]]--;
		}
	}
	return ret;
}
int f[2][MAXN * MAXN][1 << 10];
int main() {
	for (int i = 1; i < MAXN * MAXN; i++) inv[i] = fuck(i, MOD - 2);
	for (scanf("%d", &t); t; t--) {
		scanf("%d%d", &n, &m);
		c = n - m + 1;
		all = 0;
		memset(can, 0, sizeof(can));
		for (int i = 1, len; i <= n; i++) {
			scanf("%s", buf + 1);
			all += (len = strlen(buf + 1));
			for (int j = 1; j <= len; j++) can[i][buf[j] - 'a'] = 1;
		}
		scanf("%s", buf + 1);
		for (int i = 1; i <= m; i++) goal[i] = buf[i] - 'a';
		bool die = 1;
		for (int i = 1; i <= c; i++) {
			ok[i] = 1;
			for (int j = 1; j <= m; j++) {
				if (!can[i + j - 1][goal[j]]) {
					ok[i] = 0;
					break;
				}
			}
			die &= !ok[i];
		}
		if (die) {
			puts("-1");
			continue;
		}
		for (int i = 1; i <= all; i++) {
			sum[i] = sum[i - 1];
			up(sum[i], 1LL * inv[i] * all % MOD);
		}
		if (m > 10) {
			printf("%d\n", calc(1, 0, 1));
			continue;
		}
		memset(f, 0, sizeof(f));
		int limit = 1 << (m - 1), now = 0, cm = ((m - 2 >= 0) ? 1 << (m - 2) : 0);
		f[now][0][0] = -1;
		for (int i = 1; i <= n; i++) {
			now ^= 1;
			memset(f[now], 0, sizeof(f[now]));
			for (int j = 0; j < limit; j++) {
				int next = 0, delta = 0;
				for (int k = 0; k < m - 1; k++) {
					if ((j >> k) & 1) {
						if (i - m + k + 1 > 0) {
							if ((next >> goal[m - k]) & 1) continue;
							next |= 1 << goal[m - k];
							delta++;
						}
					}
				}
				for (int k = 0; k <= all; k++) {
					int &pre = f[now ^ 1][j][k];
					if (!pre) continue;
					up(f[now][j >> 1][k + delta], pre);
					if (i <= c && ok[i])
						up(f[now][j >> 1 | cm][k + delta + (((~next) >> goal[1]) & 1)], MOD - pre);
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < limit; i++)
			for (int j = 0; j <= all; j++) up(ans, 1LL * f[now][i][j] * sum[j] % MOD);
		printf("%d\n", ans);
	}
	return 0;
}