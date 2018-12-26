#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MAXK 110
#define MOD 998244353
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int n, k, l, ans, f[MAXN][MAXK], s[MAXN], a[MAXN], pre[MAXN], dif[MAXN];
int main() {
	scanf("%d%d%d", &n, &k, &l);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) pre[i] = a[i] == -1 ? pre[i - 1] : i;
	for (int i = 1; i <= n; i++) dif[i] = a[i] == a[pre[i - 1]] ? dif[pre[i - 1]] : pre[i - 1];
	s[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int p = i - 1; p > i - l && p >= 0; p--) {
			for (int j = 1; j <= k; j++) {
				bool ok = true;
				for (int t = p + 1; t <= i; t++)
					if (a[t] != -1 && a[t] != j) {
						ok = false;
						break;
					}
				if (!ok) continue;
				up(f[i][j], s[p] - f[p][j]);
			}
		}
		for (int j = 1; j <= k; j++) up(s[i], f[i][j]);
	}
	for (int i = 1; i <= k; i++) up(ans, f[n][i]);
	printf("%d\n", ans);
	return 0;
}