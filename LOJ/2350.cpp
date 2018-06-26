#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#define MAXN 100010
#define MAXM 200010
typedef long long lnt;
inline int $() {
	int x = 0;
	char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
const lnt MAXLL = (~0ULL) >> 1;
const lnt INFLL = MAXLL >> 1;

int n, m, s, t, u, v;
int head[MAXN], to[MAXM << 1], next[MAXM << 1], val[MAXM << 1], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
lnt disS[MAXN], disT[MAXN], disU[MAXN], disV[MAXN], path;
std::priority_queue<std::pair<lnt, int>> PQ;
inline void sp(int s, lnt *dis) {
	memset(dis, 0x3F, sizeof(lnt) * MAXN);
	PQ.push({dis[s] = 0, s});
	while (PQ.size()) {
		auto d = PQ.top();
		PQ.pop();
		int x = d.second;
		if (-d.first != dis[x]) continue;
		for (int i = head[x]; ~i; i = next[i]) {
			if (dis[to[i]] > dis[x] + val[i]) {
				dis[to[i]] = dis[x] + val[i];
				PQ.push({-dis[to[i]], to[i]});
			}
		}
	}
}

std::vector<int> pa[MAXN];
int d[MAXN], vis[MAXN];
lnt f[MAXN], ans = INFLL;
inline void bfs(int s, lnt *dis) {
	PQ.push({-dis[s], s});
	while (PQ.size()) {
		auto d = PQ.top();
		PQ.pop();
		int x = d.second;
		if (-d.first != dis[x]) continue;
		for (int i = head[x]; ~i; i = next[i]) {
			if (dis[to[i]] == dis[x] + val[i]) {
				PQ.push({-dis[to[i]], to[i]});
				if (disS[to[i]] + disT[to[i]] == path) {
					pa[x].push_back(to[i]);
					::d[to[i]]++;
				}
			}
		}
	}
}
std::queue<int> Q;
inline void calc(int s, lnt *dis) {
	memset(d, 0, sizeof(d));
	memset(vis, 0, sizeof(vis));
	memset(f, 0x3F, sizeof(f));

	for (int i = 1; i <= n; i++) pa[i].clear();
	bfs(s, dis);
    puts("BFS OK");
	Q.push(s);
	while (Q.size()) {
		int x = Q.front();
		Q.pop();
		f[x] = std::min(f[x], disU[x]);
		ans = std::min(ans, f[x] + disV[x]);
		for (int y : pa[x]) {
			if (!--d[y]) Q.push(y);
			f[y] = std::min(f[y], f[x]);
		}
        printf("%d\n", Q.size());
	}
}
int main() {
	n = $(), m = $(), s = $(), t = $(), u = $(), v = $();
	memset(head, -1, sizeof(head));
	for (int i = 1, u, v, w; i <= m; i++) {
		u = $(), v = $(), w = $();
		$(u, v, w);
	}
    printf("%d\n", tot);
	sp(s, disS);
	sp(t, disT);
    puts("OK");
	assert(disS[t] == disT[s]);
	path = disS[t];
	sp(u, disU);
	sp(v, disV);
    puts("OK");
	assert(disU[v] == disV[u]);
	ans = disU[v];
	calc(s, disS);
	calc(t, disT);
	printf("%lld\n", ans);
	return 0;
}