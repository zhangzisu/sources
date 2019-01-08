#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 100010
#define MAXM 250000
const int INF = 0x3F3F3F3F;
int head[MAXN], cur[MAXN], to[MAXM << 1], next[MAXM << 1], cap[MAXM << 1], tot = 0;
inline void $(int u, int v, int c) {
	next[tot] = head[u], to[tot] = v, cap[tot] = c, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, cap[tot] = 0, head[v] = tot++;
}
int m, c, n1, n2;
int level[MAXN];
std::queue<int> Q;
inline int bfs(int s, int t) {
	memset(level, 0, sizeof(level));
	memcpy(cur, head, sizeof(head));
	level[s] = 1;
	Q.push(s);
	while (Q.size()) {
		int x = Q.front();
		Q.pop();
		for (int i = cur[x]; ~i; i = next[i]) {
			if (cap[i] && !level[to[i]]) {
				level[to[i]] = level[x] + 1;
				Q.push(to[i]);
			}
		}
	}
	return level[t];
}
inline int dfs(int x, int t, int flow) {
	if (x == t || !flow) return flow;
	int ret = 0;
	for (int &i = cur[x]; ~i; i = next[i]) {
		if (level[to[i]] == level[x] + 1 && cap[i]) {
			int now = dfs(to[i], t, std::min(flow, cap[i]));
			cap[i] -= now, cap[i ^ 1] += now;
			flow -= now, ret += now;
			if (!flow) return ret;
		}
	}
	return ret;
}
inline int dinic(int s, int t) {
	int ret = 0;
	while (bfs(s, t)) ret += dfs(s, t, INF);
	return ret;
}
int ban[MAXN];
inline void filter(int s) {
	ban[s] = 1;
	Q.push(s);
	while (Q.size()) {
		int x = Q.front();
		Q.pop();
		for (int i = head[x]; ~i; i = next[i]) {
			if (cap[i] && !ban[to[i]]) {
				ban[to[i]] = 1;
				Q.push(to[i]);
			}
		}
	}
}
int fuck[MAXN];
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d%d", &m, &c);
	scanf("%d", &n1);
	for (int i = 1, x, y; i <= n1; i++) {
		scanf("%d%d", &x, &y);
		int cur = m + c + i + 1;
		$(0, cur, 1), fuck[i] = tot - 1, $(cur, x + 1, 1), $(cur, m + y + 1, 1);
	}
	scanf("%d", &n2);
	for (int i = 1, x, y; i <= n2; i++) {
		scanf("%d%d", &x, &y);
		int cur = m + c + n1 + i + 1;
		$(x + 1, cur, 1), $(m + y + 1, cur, 1), $(cur, 1, 1);
	}
	dinic(0, 1);
	filter(0);
	for (int i = 1; i <= n1; i++) printf("%d\n", !(ban[m + c + i + 1] || !cap[fuck[i]]));
	return 0;
}