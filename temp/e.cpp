#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 5000010
int n, m, head[MAXN], to[MAXN], next[MAXN], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int dfn[MAXN], low[MAXN], dfsclk;
void tarjan(int x, int fa) {
	dfn[x] = low[x] = ++dfsclk;
	for (int i = head[x]; ~i; i = next[i]) {
		if (dfn[to[i]]) {
			if (to[i] != fa) low[x] = std::min(low[x], dfn[to[i]]);
		} else {
			tarjan(to[i], x);
			low[x] = std::min(low[x], low[to[i]]);
			if (low[to[i]] > low[x]) puts("impossible"), exit(0);
		}
	}
}
int color[MAXN];
void dfs(int x) {
	dfn[x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (~color[i >> 1]) continue;
		color[i >> 1] = (i & 1);
		if (!dfn[to[i]]) dfs(to[i]);
	}
}
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v);
		$(u, v);
	}
	tarjan(1, 0);
	for (int i = 2; i <= n; i++)
		if (!dfn[i]) puts("impossible"), exit(0);
	memset(dfn, 0, sizeof(dfn));
	memset(color, -1, sizeof(color));
	dfs(1);
	for (int i = 0; i < m; i++) putchar('0' + color[i]);
	putchar(10);
	return 0;
}
