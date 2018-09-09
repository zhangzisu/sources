#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, m, p, k, a[1010][1010], vis[1010][1010];
struct data_t {
	int x, y, v;
	inline bool friend operator<(const data_t &a, const data_t &b) {
		return a.v > b.v;
	}
} data[1000010];
inline void dfs(int x, int y, int l, int r, int c) {
	if (vis[x][y] || x < 1 || x > n || y < 1 || y > m || a[x][y] < l || a[x][y] > r) return;
	vis[x][y] = c;
	dfs(x - 1, y, l, r, c);
	dfs(x + 1, y, l, r, c);
	dfs(x, y + 1, l, r, c);
	dfs(x, y - 1, l, r, c);
}
inline bool judge(int mid) {
	memset(vis, 0, sizeof(vis));
	for (int i = 1, j = k; i <= p; i++) {
		if (!vis[data[i].x][data[i].y]) {
			if (j)
				dfs(data[i].x, data[i].y, data[i].v - mid, data[i].v, j), --j;
			else
				return 0;
		}
	}
	return 1;
}
int min = 1000000010, max = 0;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &a[i][j]);
			data[++p] = (data_t){i, j, a[i][j]};
			min = std::min(min, a[i][j]);
			max = std::max(max, a[i][j]);
		}
	}
	std::sort(data + 1, data + p + 1);
	int l = 0, r = max - min, ans = max - min;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (judge(mid))
			ans = mid, r = mid - 1;
		else
			l = mid + 1;
	}
	judge(ans);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			printf("%d ", vis[i][j]);
		}
		puts("");
	}
}