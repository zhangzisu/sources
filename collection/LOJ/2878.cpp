#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 3010
typedef long long lnt;
const lnt INF = 0x3F3F3F3F3F3F3F3FLL;
int n, t;
lnt f[MAXN][MAXN];
inline void up(lnt &x, lnt y) {
	if (y < x) x = y;
}
int main() {
	scanf("%d%d", &n, &t);
	memset(f, 0x3F, sizeof(f));
	f[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		int u, v, e, d;
		scanf("%d%d%d%d", &u, &v, &d, &e);
		for (int j = 0; j <= n; j++) {
			if (f[i - 1][j] == INF) continue;
			lnt last = f[i - 1][j] + 2LL * j * t;
			up(f[i][j], last + u + v);
			if (j < n) {
				up(f[i][j + 1], last + d + v);
			}
			if (j > 0) {
				up(f[i][j - 1], last + u + e);
				up(f[i][j], last + e + d);
			}
		}
		for (int j = 1; j <= n; j++) up(f[i][j], f[i][j - 1] + d + v);
		for (int j = n; j >= 1; j--) up(f[i - 1][j], f[i][j] + u + e);
	}
	printf("%lld\n", f[n][0] + 1LL * t * (n + 1));
	return 0;
}