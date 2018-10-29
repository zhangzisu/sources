#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#define MAXN 1000010
#define MAXM 5000010
const int IMP = 0x80808080;
int n, m, p, q, t[MAXN];
std::vector<int> v[MAXN], u;
int head[MAXN], to[MAXM], next[MAXM], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
inline int cmp(int a, int b) {
	return t[a] < t[b];
}
std::priority_queue<std::pair<int, int>> Q;
int dis[MAXN];
inline void bfs() {
	memset(dis, 0x80, sizeof(dis));
	for (auto x : v[1]) Q.emplace(dis[x] = t[x], x);
	while (Q.size()) {
		auto x = Q.top();
		Q.pop();
		if (x.first != dis[x.second]) continue;
		for (int i = head[x.second]; ~i; i = next[i]) {
			if (dis[to[i]] < x.first) {
				Q.emplace(dis[to[i]] = x.first, to[i]);
			}
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	memset(head, -1, sizeof(head));
	for (int i = 1, a, b, x, y; i <= m; i++) {
		scanf("%d%d%d%d", &a, &b, &x, &y);
		v[a].push_back(++p);
		t[p] = x;
		v[b].push_back(++p);
		t[p] = y;
		$(p - 1, p);
	}
	for (int i = 1; i <= n; i++) {
		std::sort(v[i].begin(), v[i].end(), cmp);
		for (int j = 1; j < (int)v[i].size(); j++) {
			$(v[i][j - 1], v[i][j]);
		}
	}
	bfs();
	scanf("%d", &q);
	for (auto x : v[n]) u.push_back(t[x]);
	for (int i = 1, d; i <= q; i++) {
		scanf("%d", &d);
		int pos = std::upper_bound(u.begin(), u.end(), d) - u.begin();
		int ans = pos ? dis[v[n][pos - 1]] : IMP;
		printf("%d\n", (ans == IMP) ? -1 : ans);
	}
	return 0;
}