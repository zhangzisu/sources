#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
inline int fuck(int x, int y) {
	int z = 1;
	for (; y; y >>= 1) {
		if (y & 1) z = 1LL * z * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return z;
}
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int k, a, b, ia, ib, s, f[1010][1010];
inline int P(int i, int j) {
	if (j >= k) return j;
	if (i + j >= k) return (i + j + 1LL * a * ib % MOD) % MOD;
	return f[i][j];
}
int main() {
	scanf("%d%d%d", &k, &a, &b);
	s = fuck(a + b, MOD - 2);
	a = 1LL * a * s % MOD, b = 1LL * b * s % MOD;
	ia = fuck(a, MOD - 2), ib = fuck(b, MOD - 2);
	for (int i = k; i >= 0; i--) {
		for (int j = k; j >= 0; j--) {
			up(f[i][j], 1LL * P(i + 1, j) * a % MOD);
			up(f[i][j], 1LL * P(i, i + j) * b % MOD);
		}
	}
	printf("%d\n", f[1][0]);
	return 0;
}