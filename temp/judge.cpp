#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
int n, m, head[MAXN], to[MAXN], next[MAXN], u[MAXN], v[MAXN], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
int vis[MAXN];
void dfs(int x) {
	vis[x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (!vis[to[i]]) dfs(to[i]);
	}
}
int main() {
	memset(head, -1, sizeof(head));
	freopen("E.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &u[i], &v[i]);
	}
	freopen("me.out", "r", stdin);
	for (int i = 1; i <= m; i++) {
		int x;
		scanf("%1d", &x);
		if (!x) std::swap(u[i], v[i]);
	}
	for (int i = 1; i <= m; i++) $(u[i], v[i]);
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		dfs(i);
		for (int j = 1; j <= n; j++)
			if (!vis[j]) return puts("ZERO");
	}
	puts("ONE");
	return 0;
}
