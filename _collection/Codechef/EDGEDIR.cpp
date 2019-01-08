#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 100010
int T, n, m, d[MAXN];
int u[MAXN], v[MAXN], e[MAXN], p[MAXN], ans[MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int head[MAXN], to[MAXN << 1], next[MAXN << 1], id[MAXN << 1], tot;
inline void $(int u, int v, int i) {
	next[tot] = head[u], to[tot] = v, id[tot] = i, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, id[tot] = i, head[v] = tot++;
}
std::queue<int> Q;
int bfn[MAXN], bfp[MAXN], fa[MAXN], pa[MAXN], bfsclk;
inline void bfs(int x) {
	Q.push(x);
	while (Q.size()) {
		x = Q.front();
		Q.pop();
		bfp[bfn[x] = ++bfsclk] = x;
		for (int i = head[x]; ~i; i = next[i]) {
			if (to[i] == fa[x]) continue;
			fa[to[i]] = x;
			pa[to[i]] = id[i];
			Q.push(to[i]);
		}
	}
}
int main() {
	for (scanf("%d", &T); T; T--) {
		tot = bfsclk = 0;
		memset(head, -1, sizeof(head));
		memset(d, 0, sizeof(d));
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) p[i] = i;
		for (int i = 1; i <= m; i++) {
			scanf("%d%d", u + i, v + i);
			if (find(u[i]) != find(v[i])) {
				p[find(u[i])] = find(v[i]);
				$(u[i], v[i], i);
			}
			ans[i] = 0;
			d[v[i]] ^= 1;
		}
		bfs(1);
		for (int t = n; t > 1; t--) {
			int x = bfp[t];
			if (d[x]) {
				d[fa[x]] ^= 1;
				ans[pa[x]] ^= 1;
			}
		}
		if (d[1]) {
			puts("-1");
		} else {
			for (int i = 1; i <= m; i++) printf("%d%c", ans[i], " \n"[i == m]);
		}
	}
	return 0;
}