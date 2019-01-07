#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MAXM 200010
int n, m, k, q, u[MAXM], v[MAXM], w[MAXM], p[MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int head[MAXN], to[MAXN << 1], next[MAXN << 1], pos[MAXN << 1], tot = 0;
inline void $(int u, int v, int id) {
	next[tot] = head[u], to[tot] = v, pos[tot] = id, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, pos[tot] = id, head[v] = tot++;
}
int val[MAXN], c, x[4];
void dfs(int x, int fa, int id) {
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		dfs(to[i], x, pos[i]);
		val[x] ^= val[to[i]];
	}
	w[id] = val[x];
}
int main() {
	srand(19260817);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) p[i] = i;
	for (int i = 1; i <= m; i++) scanf("%d%d", &u[i], &v[i]);
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= m; i++) {
		int U = find(u[i]), V = find(v[i]);
		if (U == V) {
			w[i] = rand() << 16 | rand();
			val[u[i]] ^= w[i];
			val[v[i]] ^= w[i];
		} else {
			p[U] = V;
			$(u[i], v[i], i);
			k++;
		}
	}
	if (k != n - 1) {
		for (scanf("%d", &q); q; q--) puts("Disconnected");
		return 0;
	}
	dfs(1, 0, 0);
	for (int c = scanf("%d", &q); q; q--) {
		for (int i = (scanf("%d", &c), 0); i < c; i++) scanf("%d", &x[i]);
		for (int d = 1; d < (1 << c); d++) {
			int tmp = 0;
			for (int i = 0; i < c; i++) {
				if ((d >> i) & 1) {
					tmp ^= w[x[i]];
				}
			}
			if (!tmp) goto fail;
		}
		puts("Connected");
		continue;
	fail:
		puts("Disconnected");
	}
	return 0;
}