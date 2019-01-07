#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#define MAXN 510
#define MAXM 10010
const int INF = 0x3F3F3F3F;
int C, n, m, k, w, s[MAXN], t[MAXN], S[MAXN], T[MAXN], c[MAXN], op[MAXN], q;
int head[MAXN], next[MAXM << 1], to[MAXM << 1], cap[MAXM << 1], val[MAXM << 1], tot;
inline void $(int u, int v, int c, int w) {
	next[tot] = head[u], to[tot] = v, cap[tot] = c, val[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, cap[tot] = 0, val[tot] = -w, head[v] = tot++;
}
std::deque<int> Q;
int vis[MAXN], dis[MAXN], minCost;
inline bool SPFA() {
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3F, sizeof(dis));
	dis[2] = 0;
	vis[2] = 1;
	Q.push_back(2);
	while (Q.size()) {
		int x = Q.front();
		Q.pop_front();
		for (int i = head[x]; ~i; i = next[i]) {
			if (cap[i ^ 1] && dis[to[i]] > dis[x] + val[i ^ 1]) {
				dis[to[i]] = dis[x] + val[i ^ 1];
				if (!vis[to[i]]) {
					vis[to[i]] = 1;
					if (Q.size() && dis[to[i]] < dis[Q.front()]) {
						Q.push_front(to[i]);
					} else {
						Q.push_back(to[i]);
					}
				}
			}
		}
		vis[x] = 0;
	}
	return dis[0] != INF;
}
int dfs(int x, int flow) {
	vis[x] = 1;
	if (x == 2) return flow;
	int ret = 0, tmp;
	for (int i = head[x]; ~i; i = next[i]) {
		if (!vis[to[i]] && cap[i] && dis[x] == dis[to[i]] + val[i]) {
			tmp = dfs(to[i], std::min(cap[i], flow));
			minCost += tmp * val[i];
			flow -= tmp, cap[i] -= tmp, ret += tmp, cap[i ^ 1] += tmp;
			if (!flow) return ret;
		}
	}
	return ret;
}
inline int MCMF() {
	int ret = 0;
	while (SPFA()) {
		do {
			memset(vis, 0, sizeof(vis));
			ret += dfs(0, INF);
		} while (vis[2]);
	}
	return ret;
}
int main() {
	for (scanf("%d", &C); C; C--) {
		scanf("%d%d%d%d", &n, &m, &k, &w);
		memset(head, -1, sizeof(head));
		tot = minCost = 0;
		$(0, 1, k, 0), q = 2;
		for (int i = 1; i <= m; i++) {
			scanf("%d%d%d%d", &s[i], &t[i], &c[i], &op[i]);
			S[i] = ++q, T[i] = ++q;
			$(S[i], T[i], 1, -c[i]);
			$(1, S[i], 1, 0);
			$(T[i], 2, 1, 0);
		}
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= m; j++) {
				if (t[i] <= s[j]) {
					$(T[i], S[j], INF, (op[i] == op[j]) * w);
				}
			}
		}
		MCMF();
		printf("%d\n", -minCost);
	}
	return 0;
}