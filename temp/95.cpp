#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
typedef long long lnt;
const lnt INF = (~0ULL) >> 2;
const int MAX = 500;
int n, m, ans = MAX;
typedef lnt arr[310][310];
arr g, t, f, data[10];
inline void up(lnt &x, lnt y) {
	if (y > x) x = y;
}
inline void mul(arr &f, arr &g, arr &h) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			h[i][j] = std::min(f[i][j], g[i][j]);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {
				up(h[i][j], f[i][k] + g[k][j]);
			}
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			g[i][j] = -INF;

	for (int i = 1, a, b, c1, c2; i <= m; i++) {
		scanf("%d%d%d%d", &a, &b, &c1, &c2);
		up(g[a][b], c1);
		up(g[b][a], c2);
	}
	memcpy(t, g, sizeof(g));
	for (int i = 0; i <= 9; i++) {
		memcpy(data[i], t, sizeof(t));
		mul(t, t, f);
		memcpy(t, f, sizeof(f));
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			t[i][j] = i == j ? 0 : -INF;
		}
	}
	for (int i = 9, now = 0; i >= 0; i--) {
		mul(t, data[i], f);
		for (int j = 1; j <= n; j++) {
			if (f[j][j] > 0) goto succ;
		}
		memcpy(t, f, sizeof(f));
		now += (1 << i);
		continue;
	succ:
		ans = std::min(ans, now + (1 << i));
	}
	printf("%d\n", ans >= MAX ? 0 : ans);
	return 0;
}