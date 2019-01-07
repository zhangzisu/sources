#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline int $() {
	register int x = 0;
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 101
#define MAXM 5010
#define EPS 1e-9
int t, n, k, bit[MAXN];
inline int lowbit(int x) { return x & -x; }
double F[MAXN][MAXM], g[MAXN][MAXM], p[MAXN][MAXM], P[MAXN][MAXM];
int main() {
	p[1][0] = 1;
	for (register int i = 1; i < MAXN; i++) {
		const int up = i * (i - 1) / 2;
		for (register int j = 0; j <= up; j++) {
			for (register int k = 0; k <= i; k++) {
				p[i + 1][j + k] += p[i][j] / (i + 1);
			}
		}
	}
	for (register int i = 1; i < MAXN; i++) {
		const int up = i * (i - 1) / 2;
		for (register int j = 0; j <= up; j++) {
			F[i][j] = F[i][j - 1] + p[i][j] * j;
			P[i][j] = P[i][j - 1] + p[i][j];
		}
	}
	for (register int i = 1; i < MAXN; i++) {
		const int up = i * (i - 1) / 2;
		g[i][0] = F[i][up];
		for (register int j = 1; j <= up; j++) {
			register int s = std::min((int)(j + g[i][j - 1]), up);
			g[i][j] += F[i][s] - F[i][j];
			g[i][j] -= j * (P[i][s] - P[i][j]);
			g[i][j] += g[i][j - 1] * (P[i][up] - P[i][s]);
		}
	}
	for (t = $(); t; t--) {
		n = $(), k = $();
		memset(bit, 0, sizeof(bit));
		register int tot = 0;
		for (register int i = 1, x, y; i <= n; i++) {
			y = x = $();
			for (; y <= n; y += lowbit(y)) tot += bit[y];
			for (; x; x -= lowbit(x)) bit[x]++;
		}
		printf("%f\n", std::min((double)std::max(tot - k, 0), g[n][std::min(k - 1, n * (n - 1) / 2)]));
	}
	return 0;
}