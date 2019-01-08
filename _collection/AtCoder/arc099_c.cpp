#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 710
int G[MAXN][MAXN], vis[MAXN], n, m;
std::vector<std::pair<int, int>> V;
int c1, c2;
void dfs(int x, int color) {
	(color == 1 ? c1 : c2)++;
	vis[x] = color;
	for (int y = 1; y <= n; y++)
		if (y != x && !G[x][y]) {
			if (!vis[y])
				dfs(y, 3 - color);
			else if (vis[x] == vis[y])
				puts("-1"), exit(0);
		}
}
std::bitset<MAXN> f;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v);
		G[u][v] = G[v][u] = 1;
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i]) {
			c1 = c2 = 0;
			dfs(i, 1);
			V.emplace_back(c1, c2);
		}
	f.set(0);
	for (auto x : V) f = (f << x.first) | (f << x.second);
	int ans = ~(0U) >> 1;
	for (int i = 0; i <= n; i++) {
		if (f[i]) {
			int tmp = i * (i - 1) / 2 + (n - i) * (n - i - 1) / 2;
			ans = std::min(ans, tmp);
		}
	}
	printf("%d\n", ans);
	return 0;
}