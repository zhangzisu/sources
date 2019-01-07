#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 151
#define MAXM 3010
const int INF = (~0U) >> 2;
int T, n, m, q;
int head[MAXN], cur[MAXN], next[MAXM << 1], to[MAXM << 1], cap[MAXM << 1], tot;
inline void $(int u, int v, int c) {
	next[tot] = head[u], to[tot] = v, cap[tot] = c, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, cap[tot] = c, head[v] = tot++;
}
int level[MAXN];
std::queue<int> Q;
inline int BFS(int s, int t) {
	memset(level, 0, sizeof(level));
	memcpy(cur, head, sizeof(cur));
	level[s] = 1;
	Q.push(s);
	while (Q.size()) {
		int x = Q.front();
		Q.pop();
		for (int i = head[x]; ~i; i = next[i]) {
			if (cap[i] && !level[to[i]]) {
				level[to[i]] = level[x] + 1;
				Q.push(to[i]);
			}
		}
	}
	return level[t];
}
int DFS(int x, int t, int flow) {
	if (x == t || !flow) return flow;
	int ret = 0, tmp;
	for (int &i = cur[x]; ~i; i = next[i]) {
		if (cap[i] && level[to[i]] == level[x] + 1) {
			tmp = DFS(to[i], t, std::min(flow, cap[i]));
			ret += tmp;
			flow -= tmp;
			cap[i ^ 1] += tmp;
			cap[i] -= tmp;
			if (!flow) return ret;
		}
	}
	return ret;
}
int p[MAXN], tmp[MAXN], vis[MAXN], mincut[MAXN][MAXN];
void fill(int x) {
	vis[x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (!vis[to[i]] && cap[i]) fill(to[i]);
	}
}
void solve(int l, int r) {
	if (l == r) return;
	for (int i = 0; i < tot; i += 2) cap[i] = cap[i + 1] = (cap[i] + cap[i + 1]) >> 1;
	int s = p[l], t = p[r], maxflow = 0;
	// printf(" => %d %d\n", s, t);
	while (BFS(s, t)) maxflow += DFS(s, t, INF);
	memset(vis, 0, sizeof(vis));
	fill(s);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (vis[i] ^ vis[j]) {
				// printf("UPD %d %d = %d\n", i, j, maxflow);
				mincut[i][j] = std::min(mincut[i][j], maxflow);
			}
		}
	}
	int L = l, R = r;
	for (int i = l; i <= r; i++) tmp[vis[p[i]] ? (L++) : (R--)] = p[i];
	memcpy(p + l, tmp + l, sizeof(int) * (r - l + 1));
	solve(l, L - 1);
	solve(R + 1, r);
}
int main() {
	for (scanf("%d", &T); T; T--) {
		scanf("%d%d", &n, &m);
		memset(head, -1, sizeof(head));
		tot = 0;
		for (int i = 1, u, v, c; i <= m; i++) scanf("%d%d%d", &u, &v, &c), $(u, v, c);
		for (int i = 1; i <= n; i++) p[i] = i;
		memset(mincut, 0x3F, sizeof(mincut));
		solve(1, n);
		for (int x = scanf("%d", &q), y; q; q--) {
			scanf("%d", &x);
			y = 0;
			for (int i = 1; i <= n; i++) {
				for (int j = i + 1; j <= n; j++) {
					if (mincut[i][j] <= x) y++;
				}
			}
			printf("%d\n", y);
		}
		puts("");
	}
	return 0;
}