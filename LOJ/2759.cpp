#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#define MAXN 500010
#define MAXM 1000010
typedef long long lnt;
int n, m, x, h[MAXN];
int head[MAXN], to[MAXM << 1], next[MAXM << 1], val[MAXM << 1], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
lnt dis[MAXN];
std::priority_queue<std::pair<lnt, int>> Q;
void bfs() {
	memset(dis, 0x3F, sizeof(dis));
	Q.emplace(dis[1]=x, 1);
	while (Q.size()) {
		auto top = Q.top();
		Q.pop();
		if (dis[top.second] != -top.first) continue;
		for (int i = head[top.second]; ~i; i = next[i]) {
            if(val[i] > h[top.second])continue;
			if (dis[to[i]] > val[i] - top.first) {
				Q.emplace(-(dis[to[i]] = val[i] - top.first), to[i]);
			}
		}
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &x);
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= n; i++) scanf("%d", h + i);
	for (int i = 1, u, v, w; i <= m; i++) scanf("%d%d%d", &u, &v, &w),$(u, v, w);
	bfs();
	printf("%lld\n", dis[p] == dis[0] ? -1 : -2LL * dis[n] + x + h[n]);
	return 0;
}