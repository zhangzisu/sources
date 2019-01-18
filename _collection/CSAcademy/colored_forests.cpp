#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 924844033
#define G 5
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
				int x = a[j + k], y = 1LL * w * a[j + k + i] % MOD;
				trim(a[j + k] = x + y);
				trim(a[j + k + i] = MOD + x - y);
			}
		}
	}
}
inline void INTT(int *a, int n) {
	NTT(a, n);
	std::reverse(a + 1, a + n);
	for (int i = 0, inv = fp(n, MOD - 2); i < n; i++) a[i] = 1LL * a[i] * inv % MOD;
}
const int MAXN = 100010, MAXM = 60, N = 20, LEN = 1 << N;
int n, m, s[MAXN][MAXM], frc[MAXN], inv[MAXN];
int f[LEN], g[LEN], a[LEN], b[LEN];
void CDQ(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	CDQ(l, mid);
	int len = 1;
	while (len <= (mid - l + 1 + r - l + 1)) len <<= 1;
	len <<= 1;
	memset(a, 0, sizeof(int) * len);
	memset(b, 0, sizeof(int) * len);
	memcpy(a, f + l, sizeof(int) * (mid - l + 1));
	memcpy(b, g, sizeof(int) * (r - l + 1));
	NTT(a, len);
	NTT(b, len);
	for (int i = 0; i < len; i++) a[i] = 1LL * a[i] * b[i] % MOD;
	INTT(a, len);
	for (int i = mid + 1; i <= r; i++) up(f[i], 1LL * fp(i, MOD - 2) * a[i - l] % MOD);
	CDQ(mid + 1, r);
}
int main() {
	scanf("%d%d", &n, &m);
	s[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			trim(s[i][j] = 1LL * j * s[i - 1][j] % MOD + s[i - 1][j - 1]);
		}
	}
	frc[0] = 1;
	for (int i = 1; i <= n; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
	inv[n] = fp(frc[n], MOD - 2);
	for (int i = n; i >= 1; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
	g[1] = 1LL * s[1][m] * frc[m] % MOD * inv[0] % MOD;
	for (int i = 2; i <= n; i++) g[i] = 1LL * fp(i, i - 2) * s[i][m] % MOD * frc[m] % MOD * inv[i - 1] % MOD;
	f[0] = 1;
	CDQ(0, n);
	for (int i = 1; i <= n; i++) {
		int ans = 1LL * f[i] * frc[i] % MOD;
		printf("%d\n", ans);
	}
	return 0;
}
