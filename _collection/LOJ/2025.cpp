#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unordered_set>
#define F(x, y) ((x) >= 0 && (x) <= (y))
#define G (F(x3, n) && F(x4, n) && F(y3, m) && F(y4, m))
#define MAXN 2010
#define MOD 100000007
typedef long long lnt;
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
std::unordered_set<lnt> s;
int n, m, k, x[MAXN], y[MAXN], ans, c1, c2, c3, c4;
inline lnt com(int x, int y) { return 1LL * x * (m + 1) + y; }
inline int calc(int x1, int x2, int x3) {
	if (x1 > x3) std::swap(x1, x3);
	int ret = 0;
	if (x2 <= x1) return 1LL * (x2 + 3) * x2 % MOD * 50000004 % MOD;
	up(ret, 1LL * (x1 + 3) * x1 % MOD * 50000004 % MOD);
	if (x2 <= x3) return (ret + 1LL * (x2 - x1) * (x1 + 1) % MOD) % MOD;
	if (x1 < x3) up(ret, 1LL * (x3 - x1) * (x1 + 1) % MOD);
	if (!x1) return ret;
	int x4 = std::min(x1 + x3, x2);
	up(ret, 1LL * (x1 + x3 + 1) * (x4 - x3) % MOD);
	up(ret, MOD - 1LL * (x4 - x3) * (x4 + x3 + 1) % MOD * 50000004 % MOD);
	return ret;
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= k; i++) scanf("%d%d", x + i, y + i);
	for (int i = 1; i <= n && i <= m; i++) {
		up(ans, 1LL * i * (n - i + 1) % MOD * (m - i + 1) % MOD);
	}
	for (int i = 1; i <= k; i++) {
		up(c1, calc(x[i], m - y[i], n - x[i]));
		up(c1, calc(m - y[i], n - x[i], y[i]));
		up(c1, calc(n - x[i], y[i], x[i]));
		up(c1, calc(y[i], x[i], m - y[i]));
		up(c1, MOD - std::min(x[i], y[i]));
		up(c1, MOD - std::min(x[i], m - y[i]));
		up(c1, MOD - std::min(n - x[i], y[i]));
		up(c1, MOD - std::min(n - x[i], m - y[i]));
		s.insert(com(x[i], y[i]));
	}
	for (int i = 1; i <= k; i++) {
		for (int j = i + 1; j <= k; j++) {
			int x1 = x[i], y1 = y[i], x2 = x[j], y2 = y[j], x3, y3, x4, y4, r;
			if (x1 > x2) {
				std::swap(x1, x2);
				std::swap(y1, y2);
			}
			if (y1 > y2) {
				x3 = x1 + y1 - y2;
				y3 = y1 + x2 - x1;
				x4 = x2 + y1 - y2;
				y4 = y2 + x2 - x1;
				if (G) {
					r = s.count(com(x3, y3)) + s.count(com(x4, y4));
					up(c2, 1), up(c3, r), up(c4, r >= 2);
				}
				x3 = x1 - y1 + y2;
				y3 = y1 - x2 + x1;
				x4 = x2 - y1 + y2;
				y4 = y2 - x2 + x1;
				if (G) {
					r = s.count(com(x3, y3)) + s.count(com(x4, y4));
					up(c2, 1), up(c3, r), up(c4, r >= 2);
				}
				if (((x1 + x2) ^ (y1 + y2)) & 1) continue;
				x3 = (x1 + x2 - y1 + y2) / 2;
				y3 = (y1 + y2 - x2 + x1) / 2;
				x4 = (x1 + x2 + y1 - y2) / 2;
				y4 = (y1 + y2 + x2 - x1) / 2;
				if (G) {
					r = s.count(com(x3, y3)) + s.count(com(x4, y4));
					up(c2, 1), up(c3, r), up(c4, r >= 2);
				}
			} else {
				x3 = x1 + y2 - y1;
				y3 = y1 - x2 + x1;
				x4 = x2 + y2 - y1;
				y4 = y2 - x2 + x1;
				if (G) {
					r = s.count(com(x3, y3)) + s.count(com(x4, y4));
					up(c2, 1), up(c3, r), up(c4, r >= 2);
				}
				x3 = x1 - y2 + y1;
				y3 = y1 + x2 - x1;
				x4 = x2 - y2 + y1;
				y4 = y2 + x2 - x1;
				if (G) {
					r = s.count(com(x3, y3)) + s.count(com(x4, y4));
					up(c2, 1), up(c3, r), up(c4, r >= 2);
				}
				if (((x1 + x2) ^ (y1 + y2)) & 1) continue;
				x3 = (x1 + x2 + y2 - y1) / 2;
				y3 = (y1 + y2 - x2 + x1) / 2;
				x4 = (x1 + x2 - y2 + y1) / 2;
				y4 = (y1 + y2 + x2 - x1) / 2;
				if (G) {
					r = s.count(com(x3, y3)) + s.count(com(x4, y4));
					up(c2, 1), up(c3, r), up(c4, r >= 2);
				}
			}
		}
	}
	c3 = 1LL * c3 * 33333336 % MOD;
	c4 = 1LL * c4 * 16666668 % MOD;
	up(ans, MOD - c1);
	up(ans, c2);
	up(ans, MOD - c3);
	up(ans, c4);
	printf("%d\n", ans);
	return 0;
}