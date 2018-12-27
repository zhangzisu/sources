#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MAXK 110
#define MOD 998244353
inline int trim(int &x) { (x >= MOD) && (x -= MOD); }
inline void up(int &x, int y) { trim(x += y); }
int n, k, l, ans, f[MAXN][MAXK], s[MAXN], a[MAXN], pre[MAXN], dif[MAXN];
int main() {
	scanf("%d%d%d", &n, &k, &l);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) pre[i] = a[i] == -1 ? pre[i - 1] : i;
	for (int i = 1; i <= n; i++) dif[i] = a[i] == a[pre[i - 1]] ? dif[pre[i - 1]] : pre[i - 1];
	s[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			int limit = std::max(i - l, pre[i] - 1);
			up(f[i][j], s[i - 1]);
			up(f[i][j], MOD - f[i - 1][j]);
			if (limit >= 0) {
				up(f[i][j], MOD - s[limit]);
				up(f[i][j], f[limit][j]);
			}
		}
		if (pre[i] >= 0 && pre[i] > i - l + 1) {
			int limit = std::max(i - l, dif[pre[i]] - 1), &j = a[pre[i]];
			up(f[i][j], s[pre[i] - 1]);
			up(f[i][j], MOD - f[pre[i] - 1][j]);
			if (limit >= 0) {
				up(f[i][j], MOD - s[limit]);
				up(f[i][j], f[limit][j]);
			}
		}
		for (int j = 1; j <= k; j++) {
			up(s[i], f[i][j]);
			up(f[i][j], f[i - 1][j]);
		}
		up(s[i], s[i - 1]);
	}
	ans = s[n];
	up(ans, MOD - s[n - 1]);
	printf("%d\n", ans);
	return 0;
}