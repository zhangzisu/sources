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
int n, a1[MAXN], a2[MAXN], a3[MAXN], b1[MAXN], b2[MAXN], b3[MAXN];
char buf[MAXN];
int main() {
	scanf("%s", buf);
	n = strlen(buf);
	for (int i = 0; i < n; i++) {
		if (buf[i] == '0' || buf[i] == '1') {
			a1[i] = (buf[i] & 1) + 1;
			a2[i] = a1[i] * a1[i];
			a3[i] = a2[i] * a1[i];
		}
	}
	memcpy(b1, a1, sizeof(int) * n), std::reverse(b1, b1 + n), NTT(b1, MAXN), NTT(a1, MAXN);
	memcpy(b2, a2, sizeof(int) * n), std::reverse(b2, b2 + n), NTT(b2, MAXN), NTT(a2, MAXN);
	memcpy(b3, a3, sizeof(int) * n), std::reverse(b3, b3 + n), NTT(b3, MAXN), NTT(a3, MAXN);
	for (int i = 0; i < MAXN; i++) a1[i] = 1LL * a1[i] * b3[i] % MOD;
	for (int i = 0; i < MAXN; i++) a2[i] = 1LL * a2[i] * b2[i] % MOD;
	for (int i = 0; i < MAXN; i++) a3[i] = 1LL * a3[i] * b1[i] % MOD;
	NTT(a1, MAXN), std::reverse(a1 + 1, a1 + MAXN);
	NTT(a2, MAXN), std::reverse(a2 + 1, a2 + MAXN);
	NTT(a3, MAXN), std::reverse(a3 + 1, a3 + MAXN);
	int inv = fp(MAXN, MOD - 2);
	long long ans = 0;
	for (int i = 0; i < MAXN; i++) a1[i] = 1LL * a1[i] * inv % MOD;
	for (int i = 0; i < MAXN; i++) a2[i] = 1LL * a2[i] * inv % MOD;
	for (int i = 0; i < MAXN; i++) a3[i] = 1LL * a3[i] * inv % MOD;
	for (int i = 1; i <= n; i++) {
		int val = (a1[2 * n - i - 1] + a3[2 * n - i - 1] - 2LL * a2[2 * n - i - 1] % MOD + MOD) % MOD;
		if (!val) {
			fprintf(stderr, "PSB |> %d\n", i);
			ans = ans ^ (1LL * i * i);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
