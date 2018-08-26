#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 5010
#define MOD 1000000007
int n;
std::vector<int> next[MAXN];
int d[MAXN], size[MAXN], f[MAXN][MAXN][2], g[MAXN][MAXN][2], h[MAXN][2];
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
void dfs(int x, int fa) {
	f[x][1][0] = size[x] = 1;
	for (int y : next[x]) {
		if (y == fa) continue;
		dfs(y, x);
		for (int i = 1; i <= size[x] + size[y]; i++) g[x][i][0] = g[x][i][1] = 0;
		for (int i = 1; i <= size[x]; i++) {
			for (int j = 1; j <= size[y]; j++) {
				up(g[x][i][0], 1LL * f[x][i][1] * f[y][j][0] % MOD * d[j] % MOD);
				up(g[x][i][0], 1LL * f[x][i][0] * f[y][j][1] % MOD * d[j] % MOD);
				up(g[x][i][1], 1LL * f[x][i][0] * f[y][j][0] % MOD * d[j] % MOD);
				up(g[x][i][1], 1LL * f[x][i][1] * f[y][j][1] % MOD * d[j] % MOD);
				up(g[x][i + j][0], 1LL * f[x][i][0] * f[y][j][0] % MOD);
				up(g[x][i + j][0], 1LL * f[x][i][1] * f[y][j][1] % MOD);
				up(g[x][i + j][1], 1LL * f[x][i][0] * f[y][j][1] % MOD);
				up(g[x][i + j][1], 1LL * f[x][i][1] * f[y][j][0] % MOD);
			}
		}
		for (int i = 1; i <= size[x] + size[y]; i++) f[x][i][0] = g[x][i][0], f[x][i][1] = g[x][i][1];
		size[x] += size[y];
	}
}
int ans = 0;
int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), next[u].push_back(v), next[v].push_back(u);
	d[0] = 1;
	d[1] = 0;
	for (int i = 2; i <= n; i++) d[i] = 1LL * d[i - 2] * (i - 1) % MOD;
	dfs(1, 0);
	for (int i = 1; i <= n; i++) {
		up(ans, 1LL * f[1][i][0] * d[i] % MOD);
		up(ans, MOD - (1LL * f[1][i][1] * d[i] % MOD));
	}
	printf("%d\n", ans);
	return 0;
}