#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 2010
const double EPS = 1e-8;
int n, x0[MAXN], x1[MAXN], y[MAXN], ans = 0;
std::vector<std::pair<long double, int> > ranges;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", x0 + i, x1 + i, y + i);
		if (x0[i] > x1[i]) std::swap(x0[i], x1[i]);
	}
	for (int i = 1; i <= n; i++) {
		int now = x1[i] - x0[i];
		ranges.clear();
		for (int j = 1; j <= n; j++) {
			if (y[j] == y[i]) continue;
			long double l = 1. * (x0[j] - x0[i]) / (y[j] - y[i]), r = 1. * (x1[j] - x0[i]) / (y[j] - y[i]);
			if (l > r) std::swap(l, r);
			ranges.push_back(std::make_pair(l - EPS, x1[j] - x0[j]));
			ranges.push_back(std::make_pair(r + EPS, x0[j] - x1[j]));
		}
		std::sort(ranges.begin(), ranges.end());
		ans = std::max(ans, now);
		for (int j = 0; j < (int)ranges.size(); j++) ans = std::max(ans, now += ranges[j].second);
	}
	printf("%d\n", ans);
	return 0;
}