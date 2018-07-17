#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#define MAXN 800010
#define MOD 998244353
#define DOM 1000000007
#define G 3
inline int fuck(int x, int p, int m) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % m;
		x = 1LL * x * x % m;
	}
	return y;
}
inline void NTT(int *a, int n, int e) {
	for (int i = 1, j = 0; i < n - 1; i++) {
		for (int t = n; ~j & t; j ^= t) t >>= 1;
		if (i < j) std::swap(a[i], a[j]);
	}
	for (int k = 1; k < n; k <<= 1) {
		int t = k << 1;
		int fucker = fuck(G, (MOD - 1) / t, MOD);
		for (int i = 0; i < n; i += t) {
			int fucked = 1;
			for (int j = 0; j < k; j++, fucked = 1LL * fucked * fucker % MOD) {
				int x = a[i + j];
				int y = 1LL * fucked * a[i + j + k] % MOD;
				a[i + j] = (x + y) % MOD;
				a[i + j + k] = (x - y + MOD) % MOD;
			}
		}
	}
	if (e) {
		int inv = fuck(n, MOD - 2, MOD);
		std::reverse(a + 1, a + n);
		for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * inv % MOD;
	}
}
int n, m, a[MAXN], b[MAXN], p[MAXN], ans;
inline void up(int &x, int y) {
	if ((x += y) >= DOM) x -= DOM;
}
inline void down(int &x, int y) {
	if ((x -= y) < 0) x += DOM;
}
char buf[MAXN], fub[MAXN];
int main() {
	scanf("%s", buf);
	n = strlen(buf);
	for (int i = 0; i < 2 * n - 1; i++) fub[i] = i & 1 ? '#' : buf[i >> 1];
	for (m = 1; m < 2 * n;) m <<= 1;
	for (int i = 0; i < n; i++) a[i] = buf[i] == 'a';
	for (int i = 0; i < n; i++) b[i] = buf[i] == 'b';
	NTT(a, m, 0);
	NTT(b, m, 0);
	for (int i = 0; i < m; i++) a[i] = 1LL * a[i] * a[i] % MOD;
	for (int i = 0; i < m; i++) b[i] = 1LL * b[i] * b[i] % MOD;
	NTT(a, m, 1);
	NTT(b, m, 1);
	for (int i = 0; i < 2 * n - 1; i++) a[i] = (a[i] + b[i] + 1) >> 1;
	for (int i = 0; i < 2 * n - 1; i++) up(ans, fuck(2, a[i], DOM) - 1);
	for (int i = 0, mx = -1, id = -1; i < 2 * n - 1; i++) {
		if (i < mx) {
			p[i] = std::min(mx - i, p[2 * id - i]);
		} else {
			p[i] = 1;
		}
		while (i - p[i] >= 0 && i + p[i] < 2 * n - 1 && fub[i - p[i]] == fub[i + p[i]]) p[i]++;
		if (p[i] + i > mx) mx = p[i] + i, id = i;
		if (i & 1) {
			down(ans, p[i] >> 1);
		} else {
			down(ans, (p[i] + 1) >> 1);
		}
	}
	printf("%d\n", ans);
	return 0;
}