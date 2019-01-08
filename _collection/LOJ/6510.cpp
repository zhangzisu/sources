#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 510
#define MAXM 150010
typedef long long lnt;
const lnt INF = (~0ULL) >> 1;
int n, m, u[MAXM], v[MAXM];
lnt w[MAXM], d[MAXN], inf = 1;
int p[MAXN], id[MAXN], vis[MAXN];
lnt liu(int root, int n, int m) {
	lnt ret = 0;
	while (true) {
		for (int i = 1; i <= n; i++) {
			d[i] = INF;
		}
		for (int i = 1; i <= m; i++) {
			if (u[i] != v[i] && d[v[i]] > w[i]) {
				d[v[i]] = w[i];
				p[v[i]] = u[i];
			}
		}
		for (int i = 1; i <= n; i++) {
			if (d[i] == INF && i != root) return -1;
		}
		int count = 0;
		memset(id, 0, sizeof(id));
		memset(vis, 0, sizeof(vis));
		d[root] = 0;
		for (int i = 1; i <= n; i++) {
			int v = i;
			ret += d[i];
			while (!id[v] && vis[v] != i && v != root) {
				vis[v] = i;
				v = p[v];
			}
			if (!id[v] && v != root) {
				id[v] = ++count;
				for (int u = p[v]; u != v; u = p[u]) {
					id[u] = count;
				}
			}
		}
		if (!count) break;
		for (int i = 1; i <= n; i++) {
			if (!id[i]) id[i] = ++count;
		}
		for (int i = 1; i <= m; i++) {
			if (id[u[i]] != id[v[i]]) w[i] -= d[v[i]];
			u[i] = id[u[i]];
			v[i] = id[v[i]];
		}
		n = count;
		root = id[root];
	}
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%lld", u + i, v + i, w + i);
		inf += w[i];
	}
	for (int i = 1; i <= n; i++) {
		m++;
		u[m] = n + 1, v[m] = i, w[m] = inf;
	}
	n++;
	lnt ans = liu(n, n, m);
	if (ans == -1 || (ans -= inf) >= inf) return puts("-1"), 0;
	printf("%lld\n", ans);
	return 0;
}