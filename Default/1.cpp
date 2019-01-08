#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 1210
#define MAXM 120010
typedef long long lnt;
const lnt INF = (~0ULL) >> 2;
int head[MAXN], to[MAXM << 1], next[MAXM << 1], cap[MAXM << 1], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, cap[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, cap[tot] = 0, head[v] = tot++;
}
int n, m, s, t, h[MAXN], gap[MAXN], inq[MAXN];
lnt prs[MAXN];
inline int HLPP() {
	std::priority_queue<std::pair<int, int>> Q;
	h[s] = n;
	prs[s] = INF;
	inq[s] = 1;
	Q.emplace(h[s], s);
	gap[0] = n - 1;
	while (Q.size()) {
		int x = Q.top().second;
		Q.pop();
		if (!prs[x] || x == t) continue;
		for (int i = head[x]; ~i; i = next[i]) {
			if (x == s || h[to[i]] + 1 == h[x]) {
				int flow = std::min(prs[x], (lnt)cap[i]);
				if (flow) {
					cap[i] -= flow, cap[i ^ 1] += flow, prs[x] -= flow, prs[to[i]] += flow;
					if (to[i] != s && !inq[to[i]]) {
						Q.emplace(h[to[i]], to[i]);
						inq[to[i]] = 1;
					}
					if (!prs[x]) break;
				}
			}
		}
		if (x != s && prs[x]) {
			if (!--gap[h[x]]) {
				int th = h[x];
				for (int i = 1; i <= n; i++) {
					if (i != s && i != t && h[i] >= th) h[i] = n, prs[i] = 0;
				}
				continue;
			}
			h[x] = n;
			for (int i = head[x]; ~i; i = next[i]) {
				if (cap[i]) {
					h[x] = std::min(h[x], h[to[i]] + 1);
				}
			}
			++gap[h[x]];
			Q.emplace(h[x], x);
		} else {
			inq[x] = 0;
		}
	}
	return prs[t];
}
int main() {
	scanf("%d%d%d%d", &n, &m, &s, &t);
	memset(head, -1, sizeof(head));
	for (int u, v, c; m; m--) {
		scanf("%d%d%d", &u, &v, &c);
		$(u, v, c);
	}
	printf("%d\n", HLPP());
	return 0;
}