#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 500010
#define MAXM 500010
constexpr int INF = (~0U) >> 1;
int t, n, m, q, k, s;
int head[MAXN], to[MAXM << 1], val[MAXM << 1], next[MAXM << 1], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
std::priority_queue<std::pair<int, int>> Q;
int dis[MAXN], key[MAXN], fa[MAXN][18], p[MAXN], all;
inline void d(int x) {
	memset(dis, 0x3F, sizeof(dis));
    Q.emplace(dis[x] = 0, x);
	while (Q.size()) {
		auto t = Q.top();
		Q.pop();
		if (dis[t.second] != -t.first) continue;
		for (int x = t.second, i = head[x]; ~i; i = next[i]) {
			if (dis[to[i]] > dis[x] + val[i]) {
				Q.emplace(-(dis[to[i]] = dis[x] + val[i]), to[i]);
			}
		}
	}
}
struct _ {
	int u, v, l, a;
} e[MAXM];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int main() {
	for (scanf("%d", &t); t; t--) {
		scanf("%d%d", &n, &m);
		memset(head, -1, sizeof(head));
		tot = 0, all = n;
		for (int i = 1; i <= m; i++) {
			scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].l, &e[i].a);
			$(e[i].u, e[i].v, e[i].l);
		}
		d(1);
		std::sort(e + 1, e + m + 1, [](_ a, _ b) { return a.a > b.a; });
		for (int i = 1; i <= n; i++) key[i] = INF;
		for (int i = 1; i <= 2 * n; i++) p[i] = i;
		for (int i = 1; i <= m; i++) {
			int U = find(e[i].u), V = find(e[i].v);
			if (U == V) continue;
			key[++all] = e[i].a;
			dis[all] = std::min(dis[U], dis[V]);
			fa[U][0] = fa[V][0] = p[U] = p[V] = all;
		}
		for (int d = 1; d < 18; d++) {
			for (int i = 1; i <= all; i++)
				fa[i][d] = fa[fa[i][d - 1]][d - 1];
		}
		scanf("%d%d%d", &q, &k, &s);
		for (int v, p, lans = 0; q; q--) {
			scanf("%d%d", &v, &p);
			v = (v + k * lans - 1) % n + 1;
			p = (p + k * lans) % (s + 1);
			for (int i = 17; ~i; i--)
				if (key[fa[v][i]] > p)
					v = fa[v][i];
			printf("%d\n", lans = dis[v]);
		}
	}
	return 0;
}