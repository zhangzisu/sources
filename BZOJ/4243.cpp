#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#define MAXN 2000010
typedef long long lnt;
int n, m, p[MAXN], s[MAXN], u[MAXN], v[MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
std::vector<int> next[MAXN];
std::queue<int> Q;
lnt ans = 0;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", u + i, v + i);
		next[u[i]].push_back(v[i]);
	}
	for (int i = 1; i <= n; i++) p[i] = i;
	for (int i = 1; i <= n; i++) s[i] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < (int)next[i].size(); j++) {
			if (find(next[i][0]) != find(next[i][j])) {
				s[find(next[i][0])] += s[find(next[i][j])];
				p[find(next[i][j])] = find(next[i][0]);
			}
		}
	}
	for (int i = 1; i <= n; i++)
		if (s[find(i)] > 1) Q.push(i);
	while (Q.size()) {
		int x = Q.front();
		Q.pop();
		if (next[x].empty()) continue;
		int y = next[x][0];
		if (find(x) == find(y)) continue;
		s[find(y)] += s[find(x)];
		p[find(x)] = find(y);
		Q.push(y);
	}
	// printf("Finally n = %d m = %d\n", N, M);
	for (int i = 1; i <= n; i++) {
		if (find(i) != i) continue;
		ans += 1LL * s[i] * (s[i] - 1);
	}
	for (int i = 1; i <= m; i++) {
		if (find(u[i]) == find(v[i])) continue;
		ans++;
	}
	printf("%lld\n", ans);
	return 0;
}