#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
#define G 3
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
				trim(a[j + k] = x + y), trim(a[j + k + i] = MOD + x - y);
			}
		}
	}
}
const int N = 21;
const int MAXN = 1 << N;
const int inv = fp(MAXN, MOD - 2);
int n, a[MAXN], b[MAXN], f[MAXN], g[MAXN], c[MAXN];
char buf[MAXN];
int main() {
	scanf("%s", buf);
	n = strlen(buf);
	for (int i = 0; i < n; i++) {
		if (buf[i] == '0') a[i] = 1;
		if (buf[i] == '1') b[i] = 1;
	}
	memcpy(f, a, sizeof(f)), memcpy(g, b, sizeof(g)), std::reverse(g, g + n), NTT(f, MAXN), NTT(g, MAXN);
	for (int i = 0; i < MAXN; i++) f[i] = 1LL * f[i] * g[i] % MOD;
	NTT(f, MAXN), std::reverse(f + 1, f + MAXN);
	for (int i = 0; i < MAXN; i++) f[i] = 1LL * f[i] * inv % MOD;
	for (int i = 0; i < n; i++) c[i] |= !!f[i + n - 1];
	memcpy(f, a, sizeof(f)), memcpy(g, b, sizeof(g)), std::reverse(f, f + n), NTT(f, MAXN), NTT(g, MAXN);
	for (int i = 0; i < MAXN; i++) f[i] = 1LL * f[i] * g[i] % MOD;
	NTT(f, MAXN), std::reverse(f + 1, f + MAXN);
	for (int i = 0; i < MAXN; i++) f[i] = 1LL * f[i] * inv % MOD;
	for (int i = 0; i < n; i++) c[i] |= !!f[i + n - 1];
	long long ans = 1LL * n * n;
	for (int i = n - 1; i >= 1; i--) {
		for (int j = i + i; j < n; j += i) c[i] |= c[j];
		if (!c[i]) ans ^= 1LL * (n - i) * (n - i);
	}
	printf("%lld\n", ans);
	return 0;
}
