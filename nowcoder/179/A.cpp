#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int N = 210;
const int dx[] = {-1, 1, 0, 0, 1, 1, -1, -1};
const int dy[] = {0, 0, -1, 1, 1, -1, 1, -1};
int n, m, t, x, y, xdl, max, wxz = 0, a[N][N], b[N][N], vis[N][N];
inline int in(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }
int main() {
	scanf("%d%d%d", &n, &m, &max);
	xdl = max;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &b[i][j]);
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &x, &y);
		if (!in(x, y)) return puts("-1 -1"), 0;
		if (!b[x][y]) return puts("-1 -1"), 0;
		if (vis[x][y]) return puts("-1 -1"), 0;
		vis[x][y] = 1;
		for (int d = 0; d < 8; d++)
			if (in(x + dx[d], y + dy[d]))
				b[x + dx[d]][y + dy[d]] = 1;
		if (a[x][y] > 0) {
			xdl = std::min(max, xdl + a[x][y]);
		} else {
			xdl -= 10;
			wxz += 10;
			if (xdl < 0) return puts("-1 -1"), 0;
		}
	}
	printf("%d %d\n", xdl, wxz);
	return 0;
}