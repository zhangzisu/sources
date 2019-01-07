
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#define MAXN 3010
typedef long long lnt;
lnt n, m;
lnt x[MAXN], y[MAXN], yy[MAXN], z[MAXN];
std::vector<lnt> v, w[MAXN];
lnt res[MAXN][MAXN][2];
lnt was[MAXN][MAXN][2];
std::map<lnt, lnt> num;
lnt f[MAXN];

lnt calc() {
	std::vector<std::pair<lnt, lnt>> v;
	for (lnt i = 0; i < n; i++)
		if (z[i]) {
			v.push_back(std::make_pair(x[i], 1));
			v.push_back(std::make_pair(x[i] + y[i], -1));
		} else {
			v.push_back(std::make_pair(x[i] - y[i], 1));
			v.push_back(std::make_pair(x[i], -1));
		}
	sort(v.begin(), v.end());
	lnt cur = 0, bal = 0;
	for (lnt i = 0; i + 1 < 2 * n; i++) {
		bal += v[i].second;
		if (bal) cur += v[i + 1].first - v[i].first;
	}
	return cur;
}

lnt dp(lnt i, lnt j, lnt t) {
	if (j < i) t = 0, j = i;
	if (i == (lnt)v.size()) return 0;
	if (was[i][j][t]) return res[i][j][t];
	was[i][j][t] = 1;
	lnt cur = dp(i + 1, j, t);
	if ((!t || i < j) && f[i] > j) cur = std::max(cur, dp((t ? j : i) + 1, f[i], 0) + (v[f[i]] - v[j]));
	for (lnt k = 0; k < (lnt)w[i].size(); k++)
		if (w[i][k] > j)
			cur = std::max(cur, dp((t ? j : i) + 1, w[i][k], 1) + (v[w[i][k]] - v[j]));
	return res[i][j][t] = cur;
}

int main() {
	scanf("%lld", &n);
	for (lnt i = 0; i < n; i++) {
		scanf("%lld%lld%lld", &x[i], &y[i], &yy[i]);
		v.push_back(x[i] - y[i]);
		v.push_back(x[i]);
		v.push_back(x[i] + yy[i]);
	}
	std::sort(v.begin(), v.end());
	v.resize(std::unique(v.begin(), v.end()) - v.begin());
	for (lnt i = 0; i < (lnt)v.size(); i++) num[v[i]] = i;
	for (lnt i = 0; i < n; i++) {
		lnt a = num[x[i] - y[i]];
		lnt b = num[x[i]];
		lnt c = num[x[i] + yy[i]];
		f[b] = c;
		w[a].push_back(b);
	}
	printf("%lld\n", dp(0, 0, 0));
	return 0;
}