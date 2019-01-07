#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
typedef long long lnt;
int n, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
lnt f[MAXN][2], s[MAXN][2], ans;
void dfs(int x, int fa) {
	f[x][0] = 0;
	s[x][0] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		dfs(to[i], x);
		f[x][0] += f[to[i]][1] + s[to[i]][1];
		f[x][1] += f[to[i]][0] + s[to[i]][0];
		s[x][0] += s[to[i]][1];
		s[x][1] += s[to[i]][0];
	}
}
void dfs1(int x, int fa) {
	ans += f[x][0] / 2;
	ans += (f[x][1] + s[x][1]) / 2;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		lnt of0 = f[to[i]][0], of1 = f[to[i]][1];
		lnt os0 = s[to[i]][0], os1 = s[to[i]][1];
		f[to[i]][0] += f[x][1] - (of0 + os0) + s[x][1] - os0;
		f[to[i]][1] += f[x][0] - (of1 + os1) + s[x][0] - os1;
		s[to[i]][0] += s[x][1] - os0;
		s[to[i]][1] += s[x][0] - os1;
		dfs1(to[i], x);
		f[to[i]][0] = of0;
		f[to[i]][1] = of1;
		s[to[i]][0] = os0;
		s[to[i]][1] = os1;
	}
}
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
	dfs(1, 0);
	dfs1(1, 0);
	printf("%lld\n", ans / 2);
	return 0;
}