#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 3010
typedef long long lnt;
lnt calc(std::vector<std::pair<int, int>> &ranges) {
	std::sort(ranges.begin(), ranges.end());
	lnt ans = 0;
	int l = ranges[0].first, r = ranges[0].second;
	for (int i = 1; i < (int)ranges.size(); i++) {
		if (ranges[i].first <= r) {
			r = std::max(r, ranges[i].second);
		} else {
			ans += r - l;
			l = ranges[i].first;
			r = ranges[i].second;
		}
	}
	ans += r - l;
	return ans;
}
std::vector<std::pair<int, int>> v;
int n, p[MAXN], l[MAXN], r[MAXN], flag = 1;
lnt ans = 0;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", p + i, l + i, r + i), flag &= r[i] == 0;
	if (n <= 15) {
		for (int i = 0; i < (1 << n); i++) {
			v.clear();
			for (int j = 0; j < n; j++) {
				if ((i >> j) & 1) {
					v.emplace_back(p[j + 1] - l[j + 1], p[j + 1]);
				} else {
					v.emplace_back(p[j + 1], p[j + 1] + r[j + 1]);
				}
			}
			ans = std::max(ans, calc(v));
		}
	} else if (flag) {
		for (int i = 1; i <= n; i++) v.emplace_back(p[i] - l[i], p[i]);
		ans = std::max(ans, calc(v));
	}
	printf("%lld\n", ans);
	return 0;
}