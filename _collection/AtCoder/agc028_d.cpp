#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 610
#define MOD 1000000007
int n, m, a[MAXN], b[MAXN], f[MAXN][MAXN];
int g[MAXN], s[MAXN], ans, in, out;
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int main() {
	scanf("%d%d", &n, &m);
	g[0] = 1;
	for (int i = 2; i <= 2 * n; i += 2) g[i] = 1LL * g[i - 2] * (i - 1) % MOD;
	for (int i = 1; i <= 2 * n; i++) s[i] = 1;
	for (int i = 1; i <= m; i++) scanf("%d%d", a + i, b + i), s[a[i]]--, s[b[i]]--;
	for (int i = 1; i <= 2 * n; i++) s[i] += s[i - 1];
	// for (int i = 1; i <= 2 * n; i++) printf("%d ", s[i]);
	// puts("");
	for (int i = 2 * n; i >= 1; i--) {
		for (int j = i; j <= 2 * n; j++) {
			for (int k = 1; k <= m; k++) {
				if ((i <= a[k] && a[k] <= j) != (i <= b[k] && b[k] <= j)) goto fail;
			}
			in = s[j] - s[i - 1];
			// printf("in %d out %d\n", in, out);
			f[i][j] = 1LL * g[in] * g[out] % MOD;
			for (int k = i; k < j; k++) {
				int rest = s[j] - s[k];
				up(f[i][j], MOD - 1LL * f[i][k] * g[rest] % MOD);
			}
			// printf("f[%d][%d] = %d\n", i, j, f[i][j]);
		fail:;
		}
	}
	for(int i = 1;i <= 2 * n;i++){
		for(int j = i;j <= 2 * n;j++){
			int out = s[2 * n] - s[j] + s[i - 1];
			up(ans, 1LL * f[i][j] * g[out] % MOD);
		}
	}
	printf("%d\n", ans);
	return 0;
}