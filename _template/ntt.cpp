#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int MOD = 998244353;
const int G = 3;
inline void trim(int &x) { x -= MOD, x += (x >> 31) & MOD; }
inline void up(int &x, int y) { trim(x += y); }
inline int fp(int x, int y) {
	int z = 1;
	for (; y; y >>= 1) {
		if (y & 1) z = 1LL * z * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return z;
}
inline void NTT(int *a, int n) {
	for (int i = 1, j = 0; i < n - 1; i++) {
		for (int t = n; ~j & t; j ^= t) t >>= 1;
		if (i < j) std::swap(a[i], a[j]);
	}
	for (int i = 1; i < n; i <<= 1) {
		int t = i << 1, wn = fp(G, (MOD - 1) / t);
		for (int j = 0; j < n; j += t) {
			for (int k = 0, w = 1; k < i; k++, w = 1LL * w * wn % MOD) {
				int x = a[j + k], y = 1LL * a[j + k + i] * w % MOD;
				trim(a[j + k] = x + y);
				trim(a[j + k + i] = MOD + x - y);
			}
		}
	}
}
const int LEN = 1 << 18;
const int INV = fp(LEN, MOD - 2);
int f[LEN], g[LEN], n, m;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++) scanf("%d", f + i);
	for (int i = 0; i <= m; i++) scanf("%d", g + i);
	NTT(f, LEN), NTT(g, LEN);
	for (int i = 0; i < LEN; i++) f[i] = 1LL * f[i] * g[i] % MOD;
	NTT(f, LEN), std::reverse(f + 1, f + LEN);
	for (int i = 0; i < LEN; i++) f[i] = 1LL * f[i] * INV % MOD;
	for (int i = 0; i <= n + m; i++) printf("%d ", f[i]);
	return 0;
}