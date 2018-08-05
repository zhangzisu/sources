#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MAXM 500010
int n, m, k, q, u[MAXM], v[MAXM], w[MAXM], p[MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int head[MAXN], to[MAXN << 1], pos[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v, int id) {
	next[tot] = head[u], to[tot] = v, pos[tot] = id, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, pos[tot] = id, head[v] = tot++;
}
int val[MAXN];
void dfs(int x, int fa, int id) {
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		dfs(to[i], x, pos[i]);
		val[x] ^= val[to[i]];
	}
	if (id) {
		w[id] = val[x];
	}
}
int base[32], ok;
inline void insert(int x) {
	for (int i = 31; ~i; i--) {
		if (x >> i) {
			if (base[i]) {
				x ^= base[i];
			} else {
				base[i] = x;
				return;
			}
		}
	}
	ok = 1;
}
int main() {
	srand(19260817);
	scanf("%d%d", &n, &m);
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= m; i++) scanf("%d%d", &u[i], &v[i]);
	for (int i = 1; i <= n; i++) p[i] = i;
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
	for (int c = scanf("%d", &q), lans = 0; q; q--) {
		memset(base, 0, sizeof(base));
		ok = 0;
		scanf("%d", &c);
		// c ^= lans;
		for (int x; c; c--) scanf("%d", &x), insert(w[x ^ lans]);
		puts(ok ? "Disconnected" : (lans++, "Connected"));
	}
	return 0;
}