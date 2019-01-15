#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MOD 998244353
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
int n, k, a[MAXN], frc[MAXN], inv[MAXN], ans[MAXN], id[MAXN];
inline int C(int n, int m) { return n >= 0 && m >= 0 && n >= m ? 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD : 0; }
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", a + (id[i] = i));
	frc[0] = 1;
	for (int i = 1; i <= n; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
	inv[n] = fp(frc[n], MOD - 2);
	for (int i = n; i >= 1; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
	std::sort(id + 1, id + n + 1, [](int x, int y) { return a[x] < a[y]; });
	a[id[n + 1] = n + 1] = (~0U) >> 1;
	for (int i = 1, p1 = 0, p2 = 1, p3 = 1; i <= n; i++) {
		while (2 * a[id[p1 + 1]] < a[id[i]]) p1++;
		while (a[id[p2]] < a[id[i]]) p2++;
		while (a[id[p3 + 1]] < 2 * a[id[i]]) p3++;
		trim(ans[id[i]] = C(p1 + n - p2, k) + C(p2 - 1 + n - p3, k - p3 + p2 - 1));
	}
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
