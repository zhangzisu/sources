#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MOD 1000000009
inline int fuck(int x, int p) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
int frc[MAXN], inv[MAXN], t, n, m, a, b;
inline int C(int n, int m) { return m <= n ? 1LL * frc[n] * inv[m] * inv[n - m] % MOD : 0; }
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int main() {
	frc[0] = 1;
	for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
	inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
	for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
	for (scanf("%d", &t); t; t--) {
		scanf("%d%d%d%d", &a, &b, &n, &m);
		printf("%lld\n", 1LL * C(n - 1, m - 1) * fuck(a, n - m) % MOD * fuck(b, m - 1) % MOD);
	}
	return 0;
}