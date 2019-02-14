#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
using lnt = long long;
lnt T, n, x[MAXN], y[MAXN], vx[MAXN], vy[MAXN], sx[MAXN], sy[MAXN], cx, cy, mx, my;
int main() {
	scanf("%lld", &T);
	for (lnt _t = 1; _t <= T; _t++) {
		scanf("%lld", &n);
		cx = cy = n;
		for (lnt i = 1; i <= n; i++) {
			scanf("%lld%lld", x + i, y + i);
			vx[i] = x[i], vy[i] = y[i];
		}
		std::sort(vx + 1, vx + cx + 1);
		cx = std::unique(vx + 1, vx + cx + 1) - vx - 1;
		std::sort(vy + 1, vy + cy + 1);
		cy = std::unique(vy + 1, vy + cy + 1) - vy - 1;
		if (cx == 1 || cy == 1) {
			printf("Case %lld: %lld 1\n", _t, n);
			continue;
		}
		memset(sx + 1, 0, sizeof(lnt) * cx);
		memset(sy + 1, 0, sizeof(lnt) * cy);
		for (lnt i = 1; i <= n; i++) {
			sx[x[i] = std::lower_bound(vx + 1, vx + cx + 1, x[i]) - vx]++;
			sy[y[i] = std::lower_bound(vy + 1, vy + cy + 1, y[i]) - vy]++;
		}
		mx = my = 0;
		for (lnt i = 1; i <= cx; i++) mx = std::max(mx, sx[i]);
		for (lnt i = 1; i <= cy; i++) my = std::max(my, sy[i]);
		lnt cx0 = 0, cx1 = 0, cy0 = 0, cy1 = 0;
		for (lnt i = 1; i <= cx; i++) {
			cx0 += (sx[i] == mx);
			cx1 += (sx[i] == mx - 1);
		}
		for (lnt i = 1; i <= cy; i++) {
			cy0 += (sy[i] == my);
			cy1 += (sy[i] == my - 1);
		}
		lnt d00 = 0, d01 = 0, d10 = 0;
		for (lnt i = 1; i <= n; i++) {
			d00 += (sx[x[i]] == mx && sy[y[i]] == my);
			d01 += (sx[x[i]] == mx && sy[y[i]] == my - 1);
			d10 += (sx[x[i]] == mx - 1 && sy[y[i]] == my);
		}
		if (d00 < cx0 * cy0) {
			lnt ans = cx0 * cy0 - d00;
			if (mx + my == 2) ans /= 2;
			printf("Case %lld: %lld %lld\n", _t, mx + my, ans);
			continue;
		} else {
			lnt ans = cx0 * cy1 - d01 + cx1 * cy0 - d10 + d00;
			printf("Case %lld: %lld %lld\n", _t, mx + my - 1, ans);
		}
	}
}