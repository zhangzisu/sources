#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 100010
#define MAXM 300010
int n, m, dis[MAXN];
int head[MAXN], to[MAXM << 1], next[MAXM << 1], val[MAXM << 1], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
std::priority_queue<std::pair<int, int>> Q;
inline void bfs(int s) {
	std::fill(dis + 1, dis + n + 1, 1000000000);
	Q.emplace(dis[s] = 0, s);
	while (Q.size()) {
		auto t = Q.top();
		Q.pop();
		if (dis[t.second] != -t.first) continue;
		for (int i = head[t.second]; ~i; i = next[i])
			if (dis[to[i]] > std::max(val[i], -t.first))
				Q.emplace(-(dis[to[i]] = std::max(val[i], -t.first)), to[i]);
	}
}
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v);
		$(u, v, i);
	}
	bfs(1);
	for (int i = 1; i <= n; i++) printf("%d\n", dis[i]);
	return 0;
}