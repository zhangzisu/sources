#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 10010
const int MAXD = 8;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], val[MAXN << 1], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
std::priority_queue<std::pair<int, int>> Q;
int f[1 << MAXD][MAXN];
inline void update(int s) {
	int *dis = f[s];
	while (Q.size()) {
		std::pair<int, int> top = Q.top();
		Q.pop();
		if (-top.first != dis[top.second]) continue;
		for (int i = head[top.second]; ~i; i = next[i]) {
			if (dis[to[i]] > val[i] - top.first) {
				Q.push(std::make_pair(-(dis[to[i]] = val[i] - top.first), to[i]));
			}
		}
	}
}
int n, m, d, k, g[1 << 4];
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d%d%d", &n, &m, &d);
	for (int i = 1, u, v, w; i <= m; i++) scanf("%d%d%d", &u, &v, &w), $(u, v, w);
	memset(f, 0x3F, sizeof(f));
	memset(g, 0x3F, sizeof(g));
	for (int i = 1; i <= d; i++) {
		int p1 = 1 << (i - 1);
		int p2 = 1 << (d + i - 1);
		Q.push(std::make_pair(f[p1][i] = 0, i));
		update(p1);
		Q.push(std::make_pair(f[p2][n - d + 1] = 0, n - d + 1));
		update(p2);
	}
	k = d << 1;
	for (int i = 1; i < (1 << k); i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = (i - 1) & i; k; k = (k - 1) & i) {
				f[i][j] = std::min(f[i][j], f[k][j] + f[i - k][j]);
			}
			Q.push(std::make_pair(-f[i][j], j));
		}
		update(i);
		int val = i & (i >> d);
		for (int j = 1; j <= n; j++) g[val] = std::min(g[val], f[i][j]);
	}
	for (int i = 1; i < (1 << d); i++) {
		for (int j = (i - 1); j; j = (j - 1) & i) g[i] = std::min(g[i], g[j] + g[i - j]);
	}
	printf("%d\n", g[(1 << d) - 1] != 0x3F3F3F3F ? g[(1 << d) - 1] : -1);
	return 0;
}