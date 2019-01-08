#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <set>
#define MAXN 860
#define MAXM 20010
const int INF = (~0U) >> 1;
int n, m;
int head[MAXN], cur[MAXN], to[MAXM], cap[MAXM], next[MAXM], tot = 0;
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
		if (level[to[i]] == level[x] + 1 && cap[i]) {
			tmp = DFS(to[i], t, std::min(flow, cap[i]));
			cap[i] -= tmp, flow -= tmp;
			cap[i ^ 1] += tmp, ret += tmp;
			if (!flow) return ret;
		}
	}
	return ret;
}
int vis[MAXN];
void fill(int x) {
	vis[x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (!vis[to[i]] && cap[i]) fill(to[i]);
	}
}
int p[MAXN], t[MAXN], mincut[MAXN][MAXN];
void solve(int l, int r) {
	if (l >= r) return;
	for (int i = 0; i < tot; i += 2) cap[i] = cap[i + 1] = (cap[i] + cap[i + 1]) >> 1;
	int x = p[l], y = p[r], maxflow = 0;
	memset(vis, 0, sizeof(vis));
	while (BFS(x, y)) maxflow += DFS(x, y, INF);
	fill(x);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (vis[i] ^ vis[j]) {
				mincut[i][j] = std::min(mincut[i][j], maxflow);
			}
		}
	}
	int L = l, R = r;
	for (int i = l; i <= r; i++) t[vis[p[i]] ? L++ : R--] = p[i];
	memcpy(p + l, t + l, sizeof(int) * (r - l + 1));
	solve(l, L - 1);
	solve(R + 1, r);
}
std::set<int> S;
int main() {
	scanf("%d%d", &n, &m);
	memset(mincut, 0x3F, sizeof(mincut));
	memset(head, -1, sizeof(head));
	for (int i = 1, u, v, c; i <= m; i++) scanf("%d%d%d", &u, &v, &c), $(u, v, c);
	for (int i = 1; i <= n; i++) p[i] = i;
	solve(1, n);
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			S.insert(mincut[i][j]);
		}
	}
	printf("%lu\n", S.size());
	return 0;
}