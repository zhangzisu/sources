#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
int n, ans, a[MAXN], sum[8][MAXN];
inline int findPos(int start, int val, int count) {
	if (!count) return start - 1;
	register int l = start, r = n, ans = -1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (sum[val][mid] - sum[val][start - 1] >= count)
			ans = mid, r = mid - 1;
		else
			l = mid + 1;
	}
	return ans;
}
const int all = 1 << 8;
int g[MAXN][all], f[MAXN][all];
inline void up(int &x, int y) {
	if (y > x) x = y;
}
inline int judgeAndUpdate(int x) {
	memset(g, 0, sizeof(g));
	memset(f, 0, sizeof(f));
	g[0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int d = 0; d < all; d++) {
			if (!g[i][d]) continue;
			for (int j = 0, pos; j < 8; j++) {
				if ((d >> j) & 1) continue;
				if (~(pos = findPos(i + 1, j, x))) {
					g[pos][d | (1 << j)] = 1;
					up(f[pos][d | (1 << j)], f[i][d]);
				}
				if (~(pos = findPos(i + 1, j, x + 1))) {
					g[pos][d | (1 << j)] = 1;
					up(f[pos][d | (1 << j)], f[i][d] + 1);
				}
			}
		}
	}
	int ok = 0, tmp = 0;
	for (int i = 1; i <= n; i++) tmp = std::max(tmp, f[i][all - 1]), ok |= g[i][all - 1];
	if (ok) ans = std::max(ans, x * 8 + tmp);
	return ok;
}
int main() {
	for (int i = scanf("%d", &n); i <= n; i++) {
		scanf("%d", &a[i]), a[i]--;
		for (int j = 0; j < 8; j++) sum[j][i] = sum[j][i - 1] + (a[i] == j);
	}
	register int l = 0, r = n;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (judgeAndUpdate(mid))
			l = mid + 1;
		else
			r = mid - 1;
	}
	printf("%d\n", ans);
	return 0;
}