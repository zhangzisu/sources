#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
const int N = 20;
inline void trim(int &x) { (x >= MOD) && (x -= MOD); }
inline void up(int &x, int y) { trim(x += y); }
inline int lowbit(int x) { return x & -x; }
inline int fuck(int x, int y) {
	int z = 1;
	for (; y; y >>= 1) {
		if (y & 1) z = 1LL * z * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return z;
}
int n, m, frc[N + 1], inv[N + 1], to[N], f[N + 1][1 << N];
inline int A(int n, int m) { return 1LL * frc[n] * inv[n - m] % MOD; }
int main() {
	scanf("%d%d", &n, &m);
	for (int u, v; m; m--) {
		scanf("%d%d", &u, &v), u--, v--;
		to[u] |= 1 << v;
		to[v] |= 1 << u;
	}
	frc[0] = 1;
	for (int i = 1; i <= n; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
	inv[n] = fuck(frc[n], MOD - 2);
	for (int i = n; i >= 1; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
	f[0][0] = inv[n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (1 << n); j++) {
			int &v = f[i][j];
			if (!v) continue;
			int rest = n - __builtin_popcount(j) - 1;
			for (int k = 0; k < n; k++) {
				if ((j >> k) & 1) continue;
				int next = j | to[k] | (1 << k);
				up(f[i + 1][next], 1LL * v * A(rest, __builtin_popcount(to[k] & ~j)) % MOD);
			}
		}
	}
	for (int i = n; i >= 0; i--)
		if (f[i][(1 << n) - 1]) return printf("%d\n", f[i][(1 << n) - 1]), 0;
}