#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 122
#define MAXM 1010
typedef long long lnt;
const lnt INF = (~0ULL) >> 4;
typedef lnt matrix[MAXN][MAXN];
inline void clear(matrix &a, int n) {
	for (int i = 0; i < n; i++) memset(a[i], 0, sizeof(lnt) * n);
}
inline void copy(const matrix &a, matrix &b, int n) {
	for (int i = 0; i < n; i++) memcpy(b[i], a[i], sizeof(lnt) * n);
}
inline void init(matrix &a, int n) {
	clear(a, n);
	for (int i = 0; i < n; i++) a[i][i] = 1;
}
inline void mul(const matrix &a, const matrix &b, matrix &c, int n) {
	clear(c, n);
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			if (!a[i][k]) continue;
			for (int j = 0; j < n; j++) {
				if (!b[k][j]) continue;
				if ((a[i][k] == -1) || (b[k][j] == -1) || (c[i][j] == -1) || (a[i][k] > INF / b[k][j]) || (a[i][k] * b[k][j] > INF) || ((c[i][j] += a[i][k] * b[k][j]) > INF)) c[i][j] = -1;
			}
		}
	}
}
int n, m, d[MAXN], u[MAXM], v[MAXM], c[MAXM], p[MAXM][3], pnt, s, t;
matrix F, G, H[63], T;
lnt k;
int main() {
	scanf("%d%d%lld", &n, &m, &k);
	k += n;
	std::fill(d + 1, d + n + 1, 1);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &u[i], &v[i], &c[i]), d[v[i]] = std::max(d[v[i]], c[i]);
	s = pnt++;
	t = pnt++;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < d[i]; j++) {
			p[i][j] = pnt++;
			if (j) G[p[i][j]][p[i][j - 1]] = 1;
		}
		G[s][p[i][0]] = G[p[i][0]][t] = 1;
	}
	G[s][s] = 1;
	for (int i = 1; i <= m; i++) G[p[u[i]][0]][p[v[i]][c[i] - 1]]++;
	copy(G, H[0], pnt);
	for (int i = 1; i < 63; i++) mul(H[i - 1], H[i - 1], H[i], pnt);
	lnt ans = 0;
	F[s][s] = 1;
	for (int i = 62; ~i; i--) {
		mul(F, H[i], T, pnt);
		if (T[s][t] != -1 && T[s][t] < k) {
			ans |= 1LL << i;
			copy(T, F, pnt);
		}
	}
	ans--;
	printf("%lld\n", ans >= 3 * k ? -1 : ans);
	return 0;
}