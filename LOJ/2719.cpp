#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 6000010
#define MOD 998244353
inline int fpow(int x, int p) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
int t, n, ans, q[MAXN], a[MAXN], b[MAXN], frc[MAXN], inv[MAXN], BIT[MAXN];
inline int C(int n, int m) {
	return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD;
}
inline int F(int n, int m) {
	if (!m) return 1;
	if (m == 1) return n;
	return (C(n + m - 1, m) - C(n + m - 1, m - 2) + MOD) % MOD;
}
inline int lowbit(int x) { return x & -x; }
inline void add(int x) {
	for (; x <= n; x += lowbit(x)) BIT[x]++;
}
inline int qry(int x) {
	register int y = 0;
	for (; x; x -= lowbit(x)) y += BIT[x];
	return y;
}
inline void up(int& x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int main() {
	frc[0] = 1;
	for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
	inv[MAXN - 1] = fpow(frc[MAXN - 1], MOD - 2);
	for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;

	for (scanf("%d", &t); t; t--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &q[i]);
		memset(BIT, 0, sizeof(BIT));
		for (int i = 1; i <= n; i++) a[i] = qry(q[i]), add(q[i]);
		memset(BIT, 0, sizeof(BIT));
		for (int i = n; i >= 1; i--) b[i] = qry(n - q[i] + 1), add(n - q[i] + 1);
		ans = 0;
		for (int i = 1, lim = n, flag = 1; lim && i <= n; i++, flag = 1) {
			if (q[i] == a[i] + 1 || b[i] < lim) flag = 0;
			lim = std::min(lim, b[i]);
			if (!lim) break;
			up(ans, F(n - i + 1, lim - 1));
			if (flag) break;
		}
		printf("%d\n", ans);
	}
	return 0;
}