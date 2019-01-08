#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 500010
typedef long long lnt;
int n, m, o;
std::pair<int, int> a[MAXN], b[MAXN];
lnt ans = 0;
int main() {
	scanf("%d%d%d", &n, &m, &o);
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].second, &a[i].first);
	for (int i = 1; i <= m; i++) scanf("%d%d", &b[i].second, &b[i].first);
	std::sort(a + 1, a + n + 1);
	std::sort(b + 1, b + m + 1);
	int l = -1000000000, r = 1000000000;
	while (l <= r) {
		int mid = (l + r) >> 1, cnt = 0;
		lnt tmp = 0;
		std::priority_queue<int> Q;
		for (int i = 1, j = 1; i <= n; i++) {
			while (j <= m && b[j].first <= a[i].first) Q.push(b[j++].second);
			if (Q.size() && Q.top() - mid > a[i].second) {
				cnt++;
				tmp += Q.top() - a[i].second;
				Q.pop();
			}
		}
		if (cnt <= o) {
			r = mid - 1;
			ans = std::max(ans, tmp);
		} else {
			l = mid + 1;
		}
	}
	printf("%lld\n", ans);
	return 0;
}