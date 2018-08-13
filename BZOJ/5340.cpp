#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline void pc(char c) {
	if (_4 == _2 + BUF) fwrite(_2, 1, BUF, stdout), _4 = _2;
	*_4++ = c;
}
inline void rt() { fwrite(_2, 1, _4 - _2, stdout), exit(0); }
inline void $(int x) {
	static int _5[32];
	if (!x) {
		pc('0');
		return;
	}
	if (x < 0) {
		pc(45);
		x = -x;
	}
	register int _6;
	for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
	while (_6) pc(_5[_6--] ^ 48);
}
inline int $() {
	register int x = 0;
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 210
#define MOD 998244353
inline int fuck(int x, int p) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
int n, q, f[MAXN][MAXN], t[MAXN], p[MAXN], g[MAXN], h[MAXN], inv[100010];
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline int getInv(int x) { return x < 100010 ? inv[x] : fuck(x, MOD - 2); }
int main() {
	for (int i = 1; i < 100010; i++) inv[i] = fuck(i, MOD - 2);
	n = $();
	for (int i = 1; i <= n; i++) f[i][t[i] = $()] = 1;
	for (q = $(); q; q--) {
		if ($()) {
			int k = $();
			memset(g, 0, sizeof(g));
			g[0] = 1;
			for (int i = 1; i <= k; i++) {
				p[i] = $();
				for (int j = k; j >= 0; j--) {
					int x = g[j];
					g[j] = 1LL * x * f[p[i]][0] % MOD;
					up(g[j + 1], 1LL * x * (MOD + 1 - f[p[i]][0]) % MOD);
				}
			}
			for (int i = 1; i <= k; i++) {
				if (f[p[i]][0] == 0) {
					memcpy(h, g, sizeof(h));
					int pi = 0;
					for (int j = 1; j <= k; j++)
						up(pi, 1LL * getInv(j) * h[j] % MOD);
					$(pi);
					pc(' ');
				} else {
					memcpy(h, g, sizeof(h));
					int inv = getInv(f[p[i]][0]);
					h[0] = 1LL * h[0] * inv % MOD;
					int pi = h[0];
					for (int j = 1; j <= k; j++) {
						up(h[j], MOD - 1LL * h[j - 1] * (MOD + 1 - f[p[i]][0]) % MOD);
						h[j] = 1LL * h[j] * inv % MOD;
						up(pi, 1LL * getInv(j + 1) * h[j] % MOD);
					}
					pi = 1LL * pi * (MOD + 1 - f[p[i]][0]) % MOD;
					$(pi);
					pc(' ');
				}
			}
			pc(10);
		} else {
			int id = $(), u = $(), v = $(), p;
			p = 1LL * u * getInv(v) % MOD;
			for (int i = 1; i <= t[id]; i++) {
				int x = f[id][i];
				f[id][i] = 1LL * x * (MOD + 1 - p) % MOD;
				up(f[id][i - 1], 1LL * x * p % MOD);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		int ex = 0;
		for (int j = 0; j <= t[i]; j++) up(ex, 1LL * j * f[i][j] % MOD);
		$(ex);
		pc(' ');
	}
	pc(10);
	rt();
}