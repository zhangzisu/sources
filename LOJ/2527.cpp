#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1004535809
#define MAXN 10000010
#define MAXM 100010
#define MAXP 262144
#define G 3
int frc[MAXN], ifrc[MAXN], inv[MAXN], t[MAXP];
inline int fuck(int x, int p) {
	int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
inline void NTT(int *a, int n) {
	for (int i = 1, j = 0; i < n - 1; i++) {
		for (int t = n; ~j & t; j ^= t) t >>= 1;
		if (i < j) std::swap(a[i], a[j]);
	}
	for (int i = 1; i < n; i <<= 1) {
		int t = i << 1, wn = fuck(G, (MOD - 1) / t);
		for (int j = 0; j < n; j += t) {
			for (int k = 0, w = 1; k < i; k++, w = 1LL * w * wn % MOD) {
				int x = a[j + k], y = 1LL * w * a[j + k + i] % MOD;
				a[j + k] = (x + y) % MOD;
				a[j + k + i] = (x - y + MOD) % MOD;
			}
		}
	}
}
inline void DFT(int *a, int n) { NTT(a, n); }
inline void IDFT(int *a, int n) {
	NTT(a, n);
	std::reverse(a + 1, a + n);
	for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * inv[n] % MOD;
}
inline void INV(int *src, int *dst, int n) {
	memset(dst, 0, sizeof(int) * n * 2);
	dst[0] = inv[src[0]];
	for (int i = 2; i <= n; i <<= 1) {
		memcpy(t, src, sizeof(int) * i);
		memset(t + i, 0, sizeof(int) * i);
		DFT(dst, i << 1), DFT(t, i << 1);
		for (int j = 0; j < (i << 1); j++) dst[j] = 1LL * dst[j] * (2 - 1LL * t[j] * dst[j] % MOD + MOD) % MOD;
		IDFT(dst, i << 1);
		memset(dst + i, 0, sizeof(int) * i);
	}
}
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline int C(int n, int m) {
	return n >= m ? 1LL * frc[n] * ifrc[m] % MOD * ifrc[n - m] % MOD : 0;
}
int n, m, s, k, w[MAXP], f[MAXP], g[MAXP];
int main() {
	scanf("%d%d%d", &n, &m, &s);
	for (int i = 0; i <= m; i++) scanf("%d", &w[i]);
	frc[0] = frc[1] = ifrc[0] = ifrc[1] = inv[1] = 1;
	for (int i = 2; i <= n; i++) {
		inv[i] = 1LL * (MOD - MOD / i) * inv[MOD % i] % MOD;
		frc[i] = 1LL * frc[i - 1] * i % MOD;
		ifrc[i] = 1LL * ifrc[i - 1] * inv[i] % MOD;
	}
	int len = 1, max = std::min(m, n / s) + 1;
	while (len < max) len <<= 1;
	for (int i = 0; i < max; i++) w[i] = 1LL * w[i] * ifrc[i] % MOD;
	for (int i = 0; i < max; i++) f[i] = ifrc[i];
	memset(w + max, 0, sizeof(int) * (m - max + 1));
	printf("F:");
	for (int i = 0; i < len; i++) printf("%d ", f[i]);
	puts("");
	INV(f, g, len);
	len <<= 1;
	printf("G:");
	for (int i = 0; i < len; i++) printf("%d ", g[i]);
	puts("");
	printf("W:");
	for (int i = 0; i < len; i++) printf("%d ", w[i]);
	puts("");
	DFT(g, len), DFT(w, len);
	for (int i = 0; i < len; i++) f[i] = 1LL * g[i] * w[i] % MOD;
	IDFT(f, len);
	for (int i = 0; i < len; i++) f[i] = 1LL * f[i] * frc[i] % MOD;
	for (int i = 0; i < len; i++) printf("%d ", f[i]);
	puts("");
	int ans = 0;
	for (int i = 0; i < max; i++) up(ans, 1LL * C(m, i) * C(n, i * s) % MOD * frc[i * s] % MOD * fuck(ifrc[s], i) % MOD * f[i] % MOD * fuck(m - i, n - i * s) % MOD);
	printf("%d\n", ans);
	return 0;
}