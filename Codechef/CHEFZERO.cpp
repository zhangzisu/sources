#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2005
typedef long long lnt;
const lnt INF = (~0ULL) >> 1;
int n, m, k;
lnt all, opt = INF, a[MAXN][MAXN], b[MAXN][MAXN], c[MAXN][MAXN], d[MAXN][MAXN];
inline lnt solve() {
	lnt sum = 0, pre = 0, cnt = 1, min = INF, max = 0;
	for (int i = 1; i <= n; i++) {
		if (i & 1) {
			for (int j = 1; j <= m; j++) {
				if (sum + a[i][j] > (double)all * cnt / k) {
					if (cnt < k) {
						min = std::min(min, sum - pre);
						max = std::max(max, sum - pre);
						b[i][j] = ++cnt;
						pre = sum;
					} else {
						b[i][j] = cnt;
					}
				} else {
					b[i][j] = cnt;
				}
				sum += a[i][j];
			}
		} else {
			for (int j = m; j; j--) {
				if (sum + a[i][j] > (double)all * cnt / k) {
					if (cnt < k) {
						min = std::min(min, sum - pre);
						max = std::max(max, sum - pre);
						b[i][j] = ++cnt;
						pre = sum;
					} else {
						b[i][j] = cnt;
					}
				} else {
					b[i][j] = cnt;
				}
				sum += a[i][j];
			}
		}
	}
	return max - min;
}
inline bool upmin(lnt &x, lnt v) {
	if (v < x) return x = v, 1;
	return 0;
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) scanf("%lld", &d[i][j]), all += d[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			a[i][j] = d[i][j];
	if (upmin(opt, solve())) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				c[i][j] = b[i][j];
			}
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			a[i][j] = d[n - i + 1][j];
	if (upmin(opt, solve())) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				c[i][j] = b[n - i + 1][j];
			}
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			a[i][j] = d[i][m - j + 1];
	if (upmin(opt, solve())) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				c[i][j] = b[i][m - j + 1];
			}
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			a[i][j] = d[n - i + 1][m - j + 1];
	if (upmin(opt, solve())) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				c[i][j] = b[n - i + 1][m - j + 1];
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) printf("%lld ", c[i][j]);
		puts("");
	}
	return 0;
}