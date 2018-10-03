#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
#define MAXM 5000010
int head[MAXN], to[MAXM << 1], next[MAXM << 1], tot;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
inline void init() {
	memset(head, -1, sizeof(head));
	tot = 0;
}
int t, n, m, deep[MAXN], fa[MAXN], f[MAXN], g[MAXN], F[MAXN], G[MAXN];
int bad[MAXM], u[MAXM], v[MAXM], s[MAXN];
void dfs0(int x) {
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x]) continue;
		if (!deep[to[i]]) {
			deep[to[i]] = deep[x] + 1;
			fa[to[i]] = x;
			dfs0(to[i]);
		} else {
			if (deep[to[i]] < deep[x]) {
				s[to[i]]--;
				s[x]++;
				bad[i >> 1] = 1;
			}
		}
	}
}
void dfs1(int x) {
	f[x] = g[x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x]) continue;
		if (deep[to[i]] == deep[x] + 1) {
			dfs1(to[i]);
			if (s[to[i]]) bad[i >> 1] = 1;
			if (bad[i >> 1]) {
				g[x]++;
			} else {
				f[x] += f[to[i]];
				g[x] += g[to[i]];
			}
			s[x] += s[to[i]];
		} else {
			if (deep[to[i]] < deep[x]) {
				g[to[i]]++;
			}
		}
	}
}
void dfs2(int x) {
	F[x]++, G[x]++;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x]) continue;
		if (deep[to[i]] == deep[x] + 1) {
			if (bad[i >> 1]) {
				G[to[i]]++;
			} else {
				G[to[i]] += G[x] + g[x] - g[to[i]];
				F[to[i]] += F[x] + f[x] - f[to[i]];
			}
			dfs2(to[i]);
		}
	}
}
int main() {
	for (scanf("%d", &t); t; t--) {
		init();
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++) {
			scanf("%d%d", &u[i], &v[i]);
			$(u[i], v[i]);
		}
		for (int i = 1; i <= n; i++) {
			if (!deep[i]) {
				deep[i] = 1;
				dfs0(i);
				dfs1(i);
				dfs2(i);
			}
		}
		for(int i = 1;i <= n;i++)printf("%d %d %d %d\n", f[i], g[i], F[i], G[i]);
		for (int i = 1; i <= m; i++) {
			if (deep[u[i]] > deep[v[i]]) std::swap(u[i], v[i]);
			if (bad[i - 1]) {
				printf("%lld\n", 1LL * F[u[i]] * f[v[i]]);
			} else {
				printf("%lld\n", 1LL * F[u[i]] * g[v[i]] + 1LL * G[u[i]] * f[v[i]]);
			}
		}
	}
	return 0;
}