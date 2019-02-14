#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define MAXN 100010
int T, n, x[MAXN], y[MAXN], vx[MAXN], vy[MAXN], sx[MAXN], sy[MAXN], cx, cy;
std::set<std::pair<int, int>> S;
int main() {
	scanf("%d", &T);
	for (int _t = 1; _t <= T; _t++) {
		scanf("%d", &n);
		cx = cy = n;
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", x + i, y + i);
			vx[i] = x[i], vy[i] = y[i];
		}
		std::sort(vx + 1, vx + cx + 1);
		cx = std::unique(vx + 1, vx + cx + 1) - vx - 1;
		std::sort(vy + 1, vy + cy + 1);
		cy = std::unique(vy + 1, vy + cy + 1) - vy - 1;
		memset(sx + 1, 0, sizeof(int) * cx);
		memset(sy + 1, 0, sizeof(int) * cy);
		S.clear();
		for (int i = 1; i <= n; i++) {
			sx[x[i] = std::lower_bound(vx + 1, vx + cx + 1, x[i]) - vx]++;
			sy[y[i] = std::lower_bound(vy + 1, vy + cy + 1, y[i]) - vy]++;
			S.insert({x[i], y[i]});
		}
		int max = 0, ans = 0;
		for (int i = 1; i <= cx; i++) {
			for (int j = 1; j <= cy; j++) {
				int tmp = sx[i] + sy[j] - (int)S.count({i, j});
				if (tmp > max) {
					max = tmp;
					ans = 1;
				} else if (tmp == max) {
					ans++;
				}
			}
		}
		printf("Case %d: %d %d\n", _t, max, 0);
	}
}