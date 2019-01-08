#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
#define G 3
inline int fuck(int x, int p) {
	int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline void DFT(int *a, int n) {
	for (int i = 1, j = 0; i < n - 1; i++) {
		for (int t = n; ~j & t; j ^= t) t >>= 1;
		if (i < j) std::swap(a[i], a[j]);
	}
	for (int i = 1; i < n; i <<= 1) {
		int t = i << 1;
		int wn = fuck(G, (MOD - 1) / t);
		for (int j = 0; j < n; j += t) {
			for (int k = 0, w = 1; k < i; k++, w = 1LL * w * wn % MOD) {
				int x = a[j + k], y = 1LL * a[j + k + i] * w % MOD;
				a[j + k + i] = x;
				up(a[j + k + i], MOD - y);
				up(a[j + k], y);
			}
		}
	}
}
const int MAXN = 1 << 17;
const int N = 1 << 18;
int a[N], b[N], n;
int main() {
	scanf("%d", &n);
	a[0] = 1;
	a[1] = n + 1;
	b[0] = 1;
	b[1] = MOD - 1;
	for (int inv = 1, i = 2, lst = 1; i < MAXN; i++) {
		int now = fuck(i, MOD - 2);
		inv = 1LL * inv * now % MOD;
		a[i] = 1LL * (fuck(i, n + 1) + MOD - 1) * inv % MOD * lst % MOD;
		b[i] = 1LL * ((i & 1) ? MOD - 1 : 1) * inv % MOD;
		lst = now;
	}
	DFT(a, N);
	DFT(b, N);
	for (int i = 0; i < N; i++) a[i] = 1LL * a[i] * b[i] % MOD;
	DFT(a, N);
	std::reverse(a + 1, a + N);
	for (int i = 0, inv = fuck(N, MOD - 2); i < N; i++) a[i] = 1LL * a[i] * inv % MOD;
	int ans = a[0];
	for (int i = 1, pow = 1, frc = 1; i <= n; i++) {
        frc = 1LL * frc * i % MOD;
		pow = 1LL * pow * 2 % MOD;
		up(ans, 1LL * pow * frc % MOD * a[i] % MOD);
	}
	printf("%d\n", ans);
	return 0;
}