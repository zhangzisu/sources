#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
#define MOD 998244353
#define G 3
inline void trim(int &x) { (x >= MOD) && (x -= MOD); }
inline void up(int &x, int y) { trim(x += y); }
inline int fuck(int x, int y) {
	int z = 1;
	for (; y; y >>= 1) {
		if (y & 1) z = 1LL * z * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return z;
}
const int LEN = 1 << 20;
int rev[LEN];
inline void pre(int n) {
	for (int i = 1, j = 0; i < n - 1; i++) {
		for (int t = n; ~j & t; j ^= t) t >>= 1;
		rev[i] = j;
	}
}
inline void NTT(int *a, int n) {
	for (int i = 1; i < n - 1; i++) {
		if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	}
	for (int i = 1; i < n; i <<= 1) {
		int t = i << 1, wn = fuck(G, (MOD - 1) / t);
		for (int j = 0; j < n; j += t) {
			for (int k = 0, w = 1; k < i; k++, w = 1LL * w * wn % MOD) {
				int x = a[j + k], y = 1LL * w * a[j + k + i] % MOD;
				trim(a[j + k] = x + y);
				trim(a[j + k + i] = x - y + MOD);
			}
		}
	}
}
int n, k, len = 1, ans, inv[MAXN], frc[MAXN], f[LEN], g[LEN];
int main() {
	scanf("%d%d", &n, &k);
	frc[0] = 1;
	for (int i = 1; i <= k; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
	inv[k] = fuck(frc[k], MOD - 2);
	for (int i = k; i >= 1; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
	for (int i = 0; i <= k; i++) f[i] = 1LL * inv[i] * (i & 1 ? MOD - 1 : 1) % MOD;
	for (int i = 0; i <= k; i++) g[i] = 1LL * fuck(i, k) * inv[i] % MOD;
	while ((len >> 1) <= k) len <<= 1;
	pre(len), NTT(f, len), NTT(g, len);
	for (int i = 0; i < len; i++) f[i] = 1LL * f[i] * g[i] % MOD;
	NTT(f, len), std::reverse(f + 1, f + len);
	for (int i = 0, inv = fuck(len, MOD - 2); i < len; i++) f[i] = 1LL * f[i] * inv % MOD;
	for (int i = 0, t = 1; i <= std::min(n - 1, k); i++) {
		up(ans, 1LL * f[i] * frc[i] % MOD * fuck(2, n - 1 - i) % MOD * t % MOD);
		t = 1LL * t * (n - 1 - i) % MOD * fuck(i + 1, MOD - 2) % MOD;
	}
	ans = 1LL * ans * n % MOD;
	for (long long t = 1LL * (n - 1) * (n - 2) / 2, v = 2; t; t >>= 1) {
		if (t & 1) ans = v * ans % MOD;
		v = v * v % MOD;
	}
	printf("%d\n", ans);
	return 0;
}