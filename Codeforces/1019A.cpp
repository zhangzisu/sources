#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <set>
#define MAXN 3010
typedef long long lnt;
int n, m, k, c[MAXN], d[MAXN];
std::multiset<std::pair<int, int>> ms;
std::multiset<int> s;
std::priority_queue<int> Q[MAXN];
lnt ans = (~0ULL) >> 2;
int main() {
	scanf("%d%d", &n, &m);
	if (m == 1) return puts("0"), 0;
	for (int i = 1, p, c; i <= n; i++) {
		scanf("%d%d", &p, &c);
		::c[p]++;
		if (p != 1) {
			Q[p].push(-c);
			ms.emplace(c, p);
		}
	}
	lnt tmp = 0;
	for (int i = n; i >= 1; i--) {
		for (int j = 2; j <= m; j++) {
			while ((int)Q[j].size() > i) {
				int x = -Q[j].top();
				Q[j].pop();
				tmp += x;
				ms.erase(ms.find(std::make_pair(x, j)));
				c[j]--;
				c[1]++;
			}
		}
		s.clear();
		memcpy(d, c, sizeof(d));
		for (int i = 2; i <= m; i++) s.insert(d[i]);
		auto it = ms.begin();
		lnt res = 0;
		while (d[1] <= *s.rbegin() && it != ms.end()) {
			auto x = *it++;
			s.erase(s.find(d[x.second]));
			s.insert(--d[x.second]);
			res += x.first;
			d[1]++;
		}
		if (d[1] > *s.rbegin()) ans = std::min(ans, res + tmp);
	}
	printf("%lld\n", ans);
	return 0;
}