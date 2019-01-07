#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define MAXN 2005
#define MAXM 4000010
typedef long long lnt;
const lnt INF = (~0ULL) >> 1;
int n, m, k, p[MAXM], color[MAXM];
lnt all, avg, sum[MAXM], d[MAXN][MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
inline int get(int x, int y) { return x * m + y; }
inline std::pair<int, int> restore(int p) { return std::make_pair(p / m, p % m); }
std::set<std::pair<lnt, int>> S;
std::set<int> next[MAXM];
const int _x[4] = {1, 0, -1, 0};
const int _y[4] = {0, 1, 0, -1};
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			scanf("%lld", &d[i][j]), all += d[i][j];
			S.emplace(sum[get(i, j)] = d[i][j], p[get(i, j)] = get(i, j));
			for (int l = 0; l < 4; l++) {
				int x = i + _x[l];
				int y = j + _y[l];
				if (x < 0 || x >= n) continue;
				if (y < 0 || y >= m) continue;
				next[get(i, j)].insert(get(x, y));
			}
		}
	avg = all / k;
	int colors = 0;
	for (int i = 1; i <= n * m - k; i++) {
		int s = find(S.begin()->second);
		S.erase(S.begin());
		lnt min = INF;
		int q = -1;
		for (auto it = next[s].begin(); it != next[s].end();) {
			int t = find(*it);
			if (t != s) {
				if (sum[t] < min) {
					min = sum[t];
					q = t;
				}
				it++;
			} else {
				next[s].erase(it++);
			}
		}
		if (~q) {
			auto y = *S.find(std::make_pair(sum[q], q));
			S.erase(y);
			p[s] = q;
			sum[q] += sum[s];
			if (next[s].size() > next[q].size()) std::swap(next[s], next[q]);
			for (auto it = next[s].begin(); it != next[s].end(); next[s].erase(it++)) next[q].insert(*it);
			S.emplace(sum[q], q);
		} else {
			color[s] = ++colors;
		}
	}
	for (auto x : S) color[find(x.second)] = ++colors;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d ", color[find(get(i, j))]);
		}
		puts("");
	}
	return 0;
}