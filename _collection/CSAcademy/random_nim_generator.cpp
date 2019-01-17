#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int N = 19, MOD = 30011, INV = 15006, LEN = 1 << N;
inline void trim(int &x) { x -= MOD, x += (x >> 31) & MOD; }
inline void up(int &x, int y) { trim(x += y); }
inline void FWT(int *a, int n) {
	for (int i = 1; i < n; i <<= 1) {
		int t = i << 1;
		for (int j = 0; j < n; j += t) {
			for (int k = 0; k < i; k++) {
				int x = a[j + k], y = a[j + k + i];
				trim(a[j + k] = x + y);
				trim(a[j + k + i] = MOD + x - y);
			}
		}
	}
}
inline void IFWT(int *a, int n) {
	for (int i = 1; i < n; i <<= 1) {
		int t = i << 1;
		for (int j = 0; j < n; j += t) {
			for (int k = 0; k < i; k++) {
				int x = a[j + k], y = a[j + k + i];
				a[j + k] = INV * (x + y) % MOD;
				a[j + k + i] = INV * (MOD + x - y) % MOD;
			}
		}
	}
}
int n, k, f[LEN], g[LEN];
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i <= k; i++) f[i] = 1;
	g[0] = 1;
	FWT(f, LEN), FWT(g, LEN);
	for (; n; n >>= 1) {
		if (n & 1) {
			for (int i = 0; i < LEN; i++) g[i] = g[i] * f[i] % MOD;
		}
		for (int i = 0; i < LEN; i++) f[i] = f[i] * f[i] % MOD;
	}
	IFWT(g, LEN);
	int ans = 0;
	for (int i = 1; i < LEN; i++) up(ans, g[i]);
	printf("%d\n", ans);
	return 0;
}
