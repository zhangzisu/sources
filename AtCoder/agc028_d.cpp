#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 310
#define MOD 1000000007
int n, m, a[MAXN], b[MAXN], f[MAXN][MAXN];
int g[MAXN], s[MAXN], ans, in, out;
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int main() {
	scanf("%d%d", &n, &m);
	g[2] = 1;
	for (int i = 4; i <= 2 * n; i += 2) g[i] = 1LL * g[i - 2] * (i - 1) % MOD;
	for (int i = 1; i <= 2 * n; i++) s[i] = 1;
	for (int i = 1; i <= m; i++) scanf("%d%d", a + i, b + i), s[a[i]]--, s[b[i]]--;
	for (int i = 1; i <= 2 * n; i++) s[i] += s[i - 1];
	for (int i = 2 * n; i >= 1; i--) {
		for (int j = i; j <= 2 * n; j++) {
			for (int k = 1; k <= m; k++) {
				if ((i <= a[i] && a[i] <= j) != (i <= b[i] && b[i] <= j)) goto fail;
			}
			in = s[j] - s[i - 1];
			out = s[n] - in;
			f[i][j] = 1LL * in * out % MOD;
			for (int k = i; k < j; k++) {
				int rest = s[j] - s[k];
				up(f[i][j], MOD - 1LL * f[i][k] * rest % MOD * out % MOD);
			}
			up(ans, f[i][j]);
		fail:;
		}
	}
	printf("%d\n", ans);
	return 0;
}