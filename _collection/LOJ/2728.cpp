#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 4010
int n, m, l, p, bit[MAXN * 2];
std::vector<int> px[MAXN], py[MAXN];
std::vector<int> sop[MAXN * 2];
std::vector<std::pair<int, int>> pos[MAXN * 2];
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int y) {
	for (; x <= n + m; x += lowbit(x)) bit[x] += y;
}
inline int qry(int x) {
	int y = 0;
	for (; x; x -= lowbit(x)) y += bit[x];
	return y;
}
long long ans = 0;
int main() {
	scanf("%d%d%d%d", &n, &m, &l, &p);
	for (int i = 1, x, y; i <= p; i++) {
		scanf("%d%d", &x, &y);
		px[y].push_back(x);
		py[x].push_back(y);
	}
	for (int i = 1; i <= n; i++) {
		std::vector<int> &v = py[i];
		v.push_back(0);
		v.push_back(m + 1);
		std::sort(v.begin(), v.end());
		v.erase(std::unique(v.begin(), v.end()), v.end());
	}
	for (int i = 1; i <= m; i++) {
		std::vector<int> &v = px[i];
		v.push_back(0);
		v.push_back(n + 1);
		std::sort(v.begin(), v.end());
		v.erase(std::unique(v.begin(), v.end()), v.end());
	}
	for (int i = 1; i <= n + m - 1; i++) pos[i].emplace_back(0, 0);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int p = i - j + m, q = pos[p].size();
			int prex = *--std::upper_bound(px[j].begin(), px[j].end(), i);
			int prey = *--std::upper_bound(py[i].begin(), py[i].end(), j);
			int pre = std::max(q - (i - prex), q - (j - prey));
			int nxtx = *std::lower_bound(px[j].begin(), px[j].end(), i);
			int nxty = *std::lower_bound(py[i].begin(), py[i].end(), j);
			int nxt = std::min(q + (nxtx - i), q + (nxty - j));
			pos[p].emplace_back(pre, nxt);
		}
	}
	for (int i = 1; i <= n + m - 1; i++) {
		int k = (int)pos[i].size() - 1;
		memset(bit, 0, sizeof(bit));
		for (int j = 1; j <= k; j++) sop[pos[i][j].first].push_back(j);
		for (int j = 1; j <= k - l + 1; j++) {
			for (auto v : sop[j - 1]) add(v, 1);
			if (j + l - 1 > pos[i][j].second - 1) continue;
			ans += qry(pos[i][j].second - 1) - qry(j + l - 2);
		}
		for (int j = 1; j <= k; j++) sop[pos[i][j].first].clear();
	}
	printf("%lld\n", ans);
	return 0;
}