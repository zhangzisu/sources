#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 3010
#define MOD 1000000007
#define INV 500000004
inline void trim(int &x) { (x >= MOD) && (x -= MOD); }
inline void up(int &x, int y) { trim(x += y); }
int n, q, b = 1, ans = 0, a[MAXN], f[MAXN][MAXN];
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			f[i][j] = a[i] > a[j];
		}
	}
	for (int x, y; q; q--) {
		scanf("%d%d", &x, &y);
		for (int i = 1; i <= n; i++) {
			if (i != x && i != y) {
				f[i][x] = f[i][y] = 1LL * INV * (f[i][x] + f[i][y]) % MOD;
				f[x][i] = f[y][i] = 1LL * INV * (f[x][i] + f[y][i]) % MOD;
			}
		}
		f[x][y] = f[y][x] = 1LL * INV * (f[x][y] + f[y][x]) % MOD;
		trim(b <<= 1);
	}
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			up(ans, f[i][j]);
		}
	}
	printf("%lld\n", 1LL * ans * b % MOD);
	return 0;
}