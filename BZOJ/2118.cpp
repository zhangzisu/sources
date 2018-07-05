#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>

#define MAXN 500010
#define MAXM 8000010

typedef long long lnt;

int head[MAXN], to[MAXM], val[MAXM], next[MAXM], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
}
int n, a[50], m;
lnt dis[MAXN], bmin, bmax;
std::priority_queue<std::pair<lnt, int>> Q;

inline void BFS() {
	Q.push(std::make_pair(dis[0] = 0, 0));
	while (Q.size()) {
		std::pair<lnt, int> t = Q.top();
		Q.pop();
		int x = t.second;
		if (t.first != -dis[x]) continue;
		for (int i = head[x]; ~i; i = next[i]) {
			if (dis[to[i]] > dis[x] + val[i]) {
				dis[to[i]] = dis[x] + val[i];
				Q.push(std::make_pair(-dis[to[i]], to[i]));
			}
		}
	}
}

inline lnt calc(lnt x) {
	lnt ret = 0;
	for (int i = 0; i < m; i++) {
		if (dis[i] > x) continue;
		ret += ((x - dis[i]) / m) + 1;
	}
	return ret;
}

int main() {
	memset(head, -1, sizeof(head));
	memset(dis, 0x3F, sizeof(dis));
	scanf("%d%lld%lld", &n, &bmin, &bmax);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	m = a[1];
	for (int i = 2; i <= n; i++)
		m = std::min(m, a[i]);
	// printf("M : %d\n", m);
	for (int i = 0; i < m; i++) {
		for (int j = 1; j <= n; j++) {
			$(i, (i + a[j]) % m, a[j]);
		}
	}
	BFS();
	// for (int i = 0; i < m; i++) printf("DIS[%d] = %d\n", i, dis[i]);
	printf("%lld\n", calc(bmax) - calc(bmin - 1));
	return 0;
}