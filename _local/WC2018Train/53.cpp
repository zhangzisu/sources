#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
#define MOD 998244353
inline void trim(int &x) { (x >= MOD) && (x -= MOD); }
inline void up(int &x, int y) { trim(x += y); }
int n, p, a[MAXN], f[MAXN][4];
int main() {
	scanf("%d%d", &n, &p);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	f[0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int s0 = 0; s0 < 2; s0++) {
			for (int s1 = 0; s1 < 2; s1++) {
				int s = s1 << 1 | s0;
				int &v = f[i][s];
				if (!v) continue;
				if (a[i + 1] != 1) {
					int t = s1 << 1 | (s0 ^ s1 ^ 1);
					up(f[i + 1][t], v);
				}
				if (a[i + 1] != 0) {
					int t = (s0 ^ s1 ^ 1) << 1 | s0;
					up(f[i + 1][t], v);
				}
			}
		}
	}
	printf("%d\n", (p ? f[n][1] + f[n][2] : f[n][0] + f[n][3]) % MOD);
	return 0;
}