#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#define MAXN 100010
#define MOD 1000000007
int n, m, k, a[MAXN], b[MAXN], c[MAXN], BIT[MAXN];
std::vector<std::pair<int, int>> d;
std::vector<int> v, vl, vr;
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int v) {
	for (; x <= k; x += lowbit(x)) up(BIT[x], v);
}
inline int qry(int x) {
	int v = 0;
	for (; x; x -= lowbit(x)) up(v, BIT[x]);
	return v;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1, x; i <= m; i++) scanf("%d", &x), v.push_back(x);
	std::sort(v.begin(), v.end());
	for (int i = 1; i <= n; i++) {
		if (a[i] >= v.front() && a[i] <= v.back()) {
			int p = std::lower_bound(v.begin(), v.end(), a[i]) - v.begin();
			d.emplace_back(a[i] - v[p - 1], v[p] - a[i]);
			vl.push_back(a[i] - v[p - 1]);
			vr.push_back(v[p] - a[i]);
		}
	}
	std::sort(vl.begin(), vl.end());
	std::sort(vr.begin(), vr.end());
	std::sort(d.begin(), d.end(), [](auto a, auto b) { return a.first == b.first ? a.second > b.second : a.first < b.first; });
	vl.erase(std::unique(vl.begin(), vl.end()), vl.end());
	vr.erase(std::unique(vr.begin(), vr.end()), vr.end());
	d.erase(std::unique(d.begin(), d.end()), d.end());
	k = (n = (int)d.size()) + 1;
	add(1, 1);
	for (int i = 1; i <= n; i++) {
		a[i] = std::lower_bound(vl.begin(), vl.end(), d[i - 1].first) - vl.begin() + 1;
		b[i] = std::lower_bound(vr.begin(), vr.end(), d[i - 1].second) - vr.begin() + 1;
		add(b[i] + 1, qry(b[i]));
	}
	printf("%d\n", qry(k));
	return 0;
}