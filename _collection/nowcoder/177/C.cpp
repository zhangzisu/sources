#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 4010
#define MOD 1000000007
int a, b, c, d;
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
	return n >= m ? 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD : 0;
}
inline int insert(int x, int y) {
	return C(x + y - 1, y - 1);
}
int main() {
	frc[0] = 1;
	for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
	inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
	for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
	scanf("%d%d%d%d", &a, &b, &c, &d);
	//
	return 0;
}