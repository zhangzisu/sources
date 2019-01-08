#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <list>
#define MAXN 100010
typedef long long lnt;
int n, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int size[MAXN], height[MAXN], pre[MAXN], pos[MAXN];
lnt pool[MAXN << 5], *f[MAXN], *g[MAXN], *top = pool, ans = 0;
void split(int x, int fa) {
	pos[x] = x;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		height[x] = std::max(height[x], height[to[i]] + 1);
		split(to[i], x);
		if (height[to[i]] > height[pre[x]]) {
			pos[x] = pos[to[i]];
			height[x] = height[pre[x] = to[i]] + 1;
		}
	}
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa || (to[i] == pre[x] && x != 1)) continue;
		top += height[to[i]] + 5;
		f[pos[to[i]]] = top;
		top += 5;
		g[pos[to[i]]] = top;
		top += 2 * height[to[i]] + 5;
	}
}
void dfs(int x, int fa) {
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		dfs(to[i], x);
		if (to[i] == pre[x]) f[x] = f[to[i]] - 1, g[x] = g[to[i]] + 1;
	}
	ans += g[x][0];
	f[x][0] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa || to[i] == pre[x]) continue;
		ans += g[x][1];
		for (int j = 1; j <= height[to[i]]; j++) {
			ans += g[x][j + 1] * f[to[i]][j];
			ans += f[x][j - 1] * g[to[i]][j];
		}
		for (int j = 0; j <= height[to[i]]; j++) {
			g[x][j - 1] += g[to[i]][j];
			g[x][j + 1] += f[x][j + 1] * f[to[i]][j];
			f[x][j + 1] += f[to[i]][j];
		}
	}
}
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
	split(1, 0);
	dfs(1, 0);
	printf("%lld\n", ans);
	return 0;
}
