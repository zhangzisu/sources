#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 3010
typedef long long lnt;
lnt calc(std::vector<std::pair<int, int>> &ranges) {
	if (ranges.empty()) return 0;
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
std::vector<std::pair<int, int>> V;
int n, g[MAXN];
lnt f[MAXN], ans;
struct d {
	int p, l, r;
	inline int friend operator<(const d &a, const d &b) {
		return a.p < b.p;
	}
} dd[MAXN];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &dd[i].p, &dd[i].l, &dd[i].r);
		dd[i].l = dd[i].p - dd[i].l;
		dd[i].r = dd[i].r + dd[i].p;
	}
	std::sort(dd + 1, dd + n + 1);
	for (int i = 1; i <= n; i++) {
		// tf0
		f[i] = dd[i].p - dd[i].l;
		g[i] = dd[i].p;
		// tf1
		for (int j = i - 1, max = dd[i].p; j >= 1; j--) {
			if (dd[j].l >= dd[i].l) continue;
			lnt nxt = f[j] + dd[i].p - g[j] + max - dd[i].p;
			if (nxt > f[i]) {
				f[i] = nxt;
				g[i] = max;
			}
			max = std::max(max, dd[j].r);
		}
	}
	for (int i = 1; i <= n; i++) V.emplace_back(dd[i].p, dd[i].r);
	ans = calc(V);
	for (int i = 1; i <= n; i++) {
		V.clear();
		for (int j = i + 1; j <= n; j++)
			if (dd[j].r >= g[i]) V.emplace_back(std::max(dd[j].p, g[i]), dd[j].r);
		ans = std::max(ans, calc(V) + f[i]);
	}
	printf("%lld\n", ans);
}