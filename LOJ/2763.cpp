#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <queue>
#define MAXN 400010
#define MAXM 2000010
typedef long long lnt;
const lnt INF = 0x3F3F3F3F3F3F3F3FLL;
int n, m, k, p;
std::map<int, int> px[MAXN], py[MAXN];
int head[MAXN], to[MAXM], val[MAXM], next[MAXM], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
lnt dis[MAXN];
std::priority_queue<std::pair<lnt, int>> Q;
inline void d(int s) {
	memset(dis, 0x3F, sizeof(dis));
	Q.emplace(dis[s] = 0, s);
	while (Q.size()) {
		auto t = Q.top();
		Q.pop();
		if (-t.first != dis[t.second]) continue;
		for (int i = head[t.second]; ~i; i = next[i]) {
			if (dis[to[i]] > val[i] - t.first) {
				Q.emplace(-(dis[to[i]] = val[i] - t.first), to[i]);
			}
		}
	}
}
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1, x, y; i <= k; i++) {
		scanf("%d%d", &x, &y);
		if (!px[x][y]) {
			px[x][y] = py[y][x] = ++p;
			$(p << 1, p << 1 | 1, 1);
		}
	}
	if (!px[1][1]) {
		px[1][1] = py[1][1] = ++p;
	}
	if (!px[n][m]) {
		px[n][m] = py[m][n] = ++p;
	}
	for (int i = 1; i <= n; i++) {
		std::pair<int, int> last(0, 0);
		for (auto v : px[i]) {
			if (last.second) {
				$(v.second << 1, last.second << 1, v.first - last.first);
			}
			last = v;
		}
	}
	for (int i = 1; i <= m; i++) {
		std::pair<int, int> last(0, 0);
		for (auto v : py[i]) {
			if (last.second) {
				$(v.second << 1 | 1, last.second << 1 | 1, v.first - last.first);
			}
			last = v;
		}
	}
	d(px[1][1] << 1);
    lnt ans = std::min(dis[px[n][m] << 1], dis[px[n][m] << 1 | 1]);
    printf("%lld\n", ans == INF ? -1LL : ans);
    return 0;
}