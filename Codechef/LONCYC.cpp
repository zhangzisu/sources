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
	f[x] = 1;
	g[x] = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x]) continue;
		if (deep[to[i]] > deep[x]) {
			if (deep[to[i]] == deep[x] + 1) {
				dfs1(to[i]);
				if (s[to[i]]) bad[i >> 1] = 1;
				s[x] += s[to[i]];
			}
			if (bad[i >> 1]) {
				g[x] += f[to[i]];
			} else {
				f[x] += f[to[i]];
				g[x] += g[to[i]];
			}
		}
	}
}
void dfs2(int x) {
	F[x] = 1;
	G[x] = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x]) {
			if (bad[i >> 1]) {
				G[x] += F[to[i]] + f[to[i]] - 1;
			} else {
				G[x] += G[to[i]] + g[to[i]] - g[x];
				F[x] += F[to[i]] + f[to[i]] - f[x] - 1;
			}
		} else {
			if (deep[to[i]] < deep[x]) {
				if (bad[i >> 1]) {
					G[x] += F[to[i]] + f[to[i]] - 1;
				} else {
					// Impossible
					F[x] += F[to[i]];
					G[x] += G[to[i]];
				}
			}
		}
	}
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x]) continue;
		if (deep[to[i]] == deep[x] + 1) dfs2(to[i]);
	}
}
int main() {
	memset(head, -1, sizeof(head));
	for (scanf("%d", &t); t; t--) {
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
		// for (int i = 1; i <= n; i++) printf("%d %d %d %d\n", f[i], g[i], F[i], G[i]);
		for (int i = 1; i <= m; i++) {
			if (deep[u[i]] > deep[v[i]]) std::swap(u[i], v[i]);
			if (bad[i - 1]) {
				printf("%lld\n", 1LL * (F[u[i]] + f[u[i]] - 1) * f[v[i]]);
			} else {
				printf("%lld\n", 1LL * (F[u[i]] + f[u[i]] - f[v[i]] - 1) * g[v[i]] + 1LL * (G[u[i]] + g[u[i]] - g[v[i]]) * f[v[i]] + 1LL * (F[u[i]] + f[u[i]] - f[v[i]] - 1) * f[v[i]]);
			}
		}
		for (int i = 1; i <= n; i++) {
			head[i] = -1;
			deep[i] = s[i] = f[i] = F[i] = g[i] = G[i] = fa[i] = 0;
		}
		for (int i = 0; i < tot; i += 2) bad[i >> 1] = 0;
		tot = 0;
	}
	return 0;
}