#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline int $() {
	register int x = 0;
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#include <queue>
#include <vector>
#define MAXN 1000010
#define MAXM 1000010
int n, m;
int head[MAXN], to[MAXM], next[MAXM], val[MAXM], can[MAXM], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
}
int dis[MAXN];
inline void dijkstra(int s) {
	memset(dis, 0x3F, sizeof(dis));
	static std::priority_queue<std::pair<int, int>> Q;
	Q.emplace(dis[s] = 0, s);
	while (Q.size()) {
		auto t = Q.top();
		Q.pop();
		if (dis[t.second] != -t.first) continue;
		for (int i = head[t.second]; ~i; i = next[i]) {
			if (val[i] - t.first < dis[to[i]]) {
				Q.emplace(-(dis[to[i]] = val[i] - t.first), to[i]);
			}
		}
	}
}
int in[MAXN];
std::queue<int> q;
typedef long long lnt;
lnt f[MAXN];
int main() {
	memset(head, -1, sizeof(head));
	n = $(), m = $();
	while (m--) {
		for (int s = $(), p = $(), q, t; s; s--) t = $(), q = $(), $(p, q, t), p = q;
	}
	dijkstra(1);
	printf("%d ", dis[n]);
	for (int x = 1; x <= n; x++) {
		for (int i = head[x]; ~i; i = next[i]) {
			if (dis[to[i]] == dis[x] + val[i]) {
				can[i] = 1;
				in[to[i]]++;
			}
		}
	}
	for (int i = 1; i <= n; i++)
		if (!in[i]) q.push(i);
	f[1] = 0;
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (int i = head[x]; ~i; i = next[i]) {
			if (!can[i]) continue;
			f[to[i]] = std::max(f[to[i]], f[x] + 1LL * val[i] * val[i]);
			if (!--in[to[i]]) q.push(to[i]);
		}
	}
	printf("%lld\n", f[n]);
	return 0;
}