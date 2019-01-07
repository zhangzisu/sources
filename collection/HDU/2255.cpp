#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 310
int n, G[MAXN][MAXN], match[MAXN], lx[MAXN], ly[MAXN], slack[MAXN];
bool visx[MAXN], visy[MAXN];
bool dfs(int x) {
	visx[x] = 1;
	for (int y = 1; y <= n; y++) {
		if (visy[y]) continue;
		int tmp = lx[x] + ly[y] - G[x][y];
		if (!tmp) {
			visy[y] = 1;
			if (!~match[y] || dfs(match[y])) return match[y] = x, 1;
		} else {
			slack[y] = std::min(slack[y], tmp);
		}
	}
    return 0;
}
inline void KM() {
	for (int x = 1; x <= n; x++) {
		memset(slack, 0x3F, sizeof(slack));
		for (;;) {
			memset(visx, 0, sizeof(visx));
			memset(visy, 0, sizeof(visy));
			if (dfs(x)) break;
			int delta = 0x3F3F3F3F;
			for (int i = 1; i <= n; i++)
				if (!visy[i] && slack[i] < delta) delta = slack[i];
			for (int i = 1; i <= n; i++)
				if (visx[i]) lx[i] -= delta;
			for (int i = 1; i <= n; i++) {
				if (visy[i]) {
					ly[i] += delta;
				} else {
					slack[i] -= delta;
				}
			}
		}
	}
}
inline void solve() {
	memset(match, -1, sizeof(match));
	memset(ly, 0, sizeof(ly));
	for (int i = 1; i <= n; i++) {
		lx[i] = 0x80808080;
		for (int j = 1; j <= n; j++)
			lx[i] = std::max(lx[i], G[i][j]);
	}
	KM();
}
int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d", &G[i][j]);
			}
		}
		solve();
		int ans = 0;
		for (int i = 1; i <= n; i++)
			if (~match[i])
				ans += G[match[i]][i];
		printf("%d\n", ans);
	}
	return 0;
}