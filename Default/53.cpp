#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
#define MOD 998244353
inline void trim(int &x) { (x >= MOD) && (x -= MOD); }
inline void up(int &x, int y) { trim(x += y); }
int n, p, ans, a[MAXN], b[MAXN], f[MAXN][2][2][2];
int main() {
	scanf("%d%d", &n, &p);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	b[0] = 1;
	for (int i = 1; i <= n; i++) trim(b[i] = b[i - 1] << 1);
	f[0][0][0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int all = 0; all < 2; all++) {
			for (int s0 = 0; s0 < 2; s0++) {
				for (int s1 = 0; s1 < 2; s1++) {
					int &v = f[i - 1][all][s0][s1];
					if (a[i] != 1) {
						if (s0) up(f[i][all][s0][s1], 1LL * v * b[i - s0 - 1] % MOD);
						up(f[i][all ^ 1][s0][1], 1LL * v * b[i - s0 - 1] % MOD);
					}
					if (a[i] != 0) {
						if (s1) up(f[i][all][s0][s1], 1LL * v * b[i - s1 - 1] % MOD);
						up(f[i][all ^ 1][1][s1], 1LL * v * b[i - s1 - 1] % MOD);
					}
				}
			}
		}
	}
	for (int s0 = 0; s0 < 2; s0++)
		for (int s1 = 0; s1 < 2; s1++)
			up(ans, f[n][p][s0][s1]);
	printf("%d\n", ans);
	return 0;
}