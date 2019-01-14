#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
#define G 3
#define MAXN 400010
inline void trim(int &x) { x -= MOD, x += (x >> 31) & MOD; }
inline int fuck(int x, int y) {
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
		int t = i << 1, wn = fuck(G, (MOD - 1) / t);
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
	int inv = fuck(n, MOD - 2);
	for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * inv % MOD;
}
int tmp[MAXN];
inline void INV(int *src, int *dst, int n) {
	memset(dst, 0, sizeof(int) * n * 2);
	dst[0] = fuck(src[0], MOD - 2);
	for (int i = 2; i <= n; i <<= 1) {
		memcpy(tmp, src, sizeof(int) * i);
		memset(tmp + i, 0, sizeof(int) * i);
		int t = i << 1;
		NTT(dst, t), NTT(tmp, t);
		for (int j = 0; j < t; j++) dst[j] = 1LL * dst[j] * (2 - 1LL * tmp[j] * dst[j] % MOD + MOD) % MOD;
		INTT(dst, t);
		memset(dst + i, 0, sizeof(int) * i);
	}
}
int n, a[MAXN], b[MAXN];
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", a + i);
	INV(a, b, n);
	for (int i = 0; i < n; i++) printf("%d ", b[i]);
	puts("");
	return 0;
}
