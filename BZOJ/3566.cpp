#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 500010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
double val[MAXN << 1], p[MAXN], f[MAXN], g[MAXN], ans;
inline void $(int u, int v, double w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int n;
void dfs1(int x, int fa) {
	f[x] = 1 - p[x];
	for (int i = head[x]; ~i; i = next[i]) {
		if (i == fa) continue;
		dfs1(to[i], i ^ 1);
		f[x] = f[x] * (f[to[i]] + (1 - f[to[i]]) * (1 - val[i]));
	}
}
void dfs2(int x, int fa) {
	if (x == 1) {
		g[x] = 1;
	} else {
		double tmp = g[to[fa]] * f[to[fa]] / (f[x] + (1 - f[x]) * (1 - val[fa]));
		g[x] = tmp + (1 - tmp) * (1 - val[fa]);
	}
	for (int i = head[x]; ~i; i = next[i]) {
		if (i == fa) continue;
		dfs2(to[i], i ^ 1);
	}
}
int main() {
	scanf("%d", &n);
    memset(head, -1, sizeof(head));
	for (int i = 1, u, v, w; i < n; i++) scanf("%d%d%d", &u, &v, &w), $(u, v, 1. * w / 100);
	for (int i = 1, w; i <= n; i++) scanf("%d", &w), p[i] = 1. * w / 100;
	dfs1(1, -1);
	dfs2(1, -1);
	for (int i = 1; i <= n; i++) ans += 1 - f[i] * g[i];
	printf("%.6f\n", ans);
	return 0;
}