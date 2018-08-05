#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#define MAXN 1010
#define MAXM 40010
typedef long long lnt;
const lnt INF = 0x3F3F3F3F3F3F3F3FLL;
lnt head[MAXN], to[MAXM], cap[MAXM], cost[MAXM], next[MAXM], tot = 0;
inline void $(lnt u, lnt v, lnt cp, lnt ct) {
	next[tot] = head[u], to[tot] = v, cap[tot] = cp, cost[tot] = ct, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, cap[tot] = 0, cost[tot] = -ct, head[v] = tot++;
}
lnt n, m, s, t, a[MAXN];
std::deque<lnt> Q;
lnt vis[MAXN], dis[MAXN];
inline bool SPFA() {
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3F, sizeof(dis));
	dis[t] = 0;
	vis[t] = 1;
	Q.push_back(t);
	while (Q.size()) {
		lnt x = Q.front();
		Q.pop_front();
		for (lnt i = head[x]; ~i; i = next[i]) {
			if (cap[i ^ 1] && dis[to[i]] > dis[x] + cost[i ^ 1]) {
				dis[to[i]] = dis[x] + cost[i ^ 1];
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
	return dis[s] != INF;
}
lnt minCost = 0;
lnt dfs(lnt x, lnt flow) {
	vis[x] = 1;
	if (x == t) return flow;
	lnt ret = 0, tmp;
	for (lnt i = head[x]; ~i; i = next[i]) {
		if (!vis[to[i]] && cap[i] && dis[x] == dis[to[i]] + cost[i]) {
			tmp = dfs(to[i], std::min(cap[i], flow));
			minCost += tmp * cost[i];
			flow -= tmp, cap[i] -= tmp, ret += tmp, cap[i ^ 1] += tmp;
			if (!flow) return ret;
		}
	}
	return ret;
}
inline lnt MCMF() {
	lnt ret = 0;
	while (SPFA()) {
		do {
			memset(vis, 0, sizeof(vis));
			ret += dfs(s, INF);
		} while (vis[t]);
	}
	return ret;
}
int main() {
	scanf("%lld%lld", &n, &m);
	memset(head, -1, sizeof(head));
	for (lnt i = 1; i <= n; i++) scanf("%lld", &a[i]);
	$(s = 0, 1, INF, 0);
	for (lnt i = 1; i <= n; i++) $(i, i + 1, INF - a[i], 0);
	$(n + 1, t = n + 2, INF, 0);
	for (lnt l, r, c; m; m--) {
		scanf("%lld%lld%lld", &l, &r, &c);
		$(l, r + 1, INF, c);
	}
	MCMF();
	printf("%lld\n", minCost);
	return 0;
}