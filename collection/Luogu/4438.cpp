#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 510
#define EPS 1e-10
int n, d, v[MAXN], k;
std::pair<int, int> g[MAXN];
double ans;
inline int check(register int x, register int y) {
	for (int i = 1; i <= n; i++) {
		if ((g[i].first * y / x + 1) * x < g[i].second * y) return 0;
	}
	return 1;
}
int main() {
	scanf("%d%d", &n, &d);
	ans = d;
	for (int i = 1; i <= n; i++) scanf("%d%d", &g[i].first, &g[i].second);
	for (int i = 1; i <= n; i++) v[++k] = g[i].second;
	std::sort(v + 1, v + k + 1);
	k = std::unique(v + 1, v + k + 1) - v - 1;
	for (register int i = k; i >= 1; i--) {
		for (register int j = 1; v[i] >= j; j++) {
			if (check(v[i], j)) {
				ans = std::min(ans, 1. * v[i] / j);
			}
		}
	}
	printf("%.10lf\n", ans);
	return 0;
}
