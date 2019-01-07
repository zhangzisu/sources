#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
#define MOD 1000000007
inline int fuck(int x, int p) {
	int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
int frc[MAXN], inv[MAXN];
inline int C(int n, int m) {
	return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD;
}
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
// T(n, m) = Sum_{i=0..m+1} (-1)^i * (m-i+1)^n * binomial(n+1, i).
inline int E(int n, int m) {
	int ret = 0;
	for (int i = 0; i <= m + 1; i++) {
		int now = 1LL * fuck(m - i + 1, n) * C(n + 1, i) % MOD;
		up(ret, (i & 1) ? MOD - now : now);
	}
	return ret;
}
int n, m;
int main() {
	frc[0] = 1;
	for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
	inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
	for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
	scanf("%d%d", &n, &m);
	printf("%d\n", E(n, m));
	return 0;
}