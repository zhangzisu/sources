#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 100010
int n, m, d[MAXN];
int head[MAXN], next[MAXN], to[MAXN], col[MAXN], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, col[tot] = w, head[u] = tot++;
	d[v]++;
}
unsigned f[MAXN], g[MAXN], h[MAXN], ans = 0;
char buf[3];
std::queue<int> Q;
inline void sol() {
	while (Q.size()) {
		int x = Q.front();
		Q.pop();
		ans += h[x];
		g[x] += 1;
		// printf("%d: f = %d, g = %d, h = %d\n", x, f[x], g[x], h[x]);
		for (int i = head[x]; ~i; i = next[i]) {
			if (col[i] == 0) {
				g[to[i]] += g[x];
				h[to[i]] += h[x];
				f[to[i]] += f[x];
			} else if (col[i] == 1) {
				h[to[i]] += f[x];
			} else if (col[i] == 2) {
				f[to[i]] += g[x];
			} else {
				f[to[i]] += f[x];
			}
			if (!--d[to[i]]) Q.push(to[i]);
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	memset(head, -1, sizeof(head));
	for (int i = 1, x, y; i <= m; i++) {
		scanf("%d%d%s", &x, &y, buf);
		if (buf[0] == '_')
			$(x, y, 0);
		else if (buf[0] == '.')
			$(x, y, 1);
		else if (buf[0] >= 'A' && buf[0] <= 'Z')
			$(x, y, 2);
		else
			$(x, y, 3);
	}
	for (int i = 1; i <= n; i++) {
		if (!d[i]) Q.push(i);
	}
	sol();
	printf("%u\n", ans);
	return 0;
}