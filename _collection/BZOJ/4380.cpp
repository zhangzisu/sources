#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 60
#define MAXM 4010
const int INF = (~0U) >> 1;
int n, m, k, a[MAXM], b[MAXM], c[MAXM], sum[MAXN][MAXM];
int f[MAXN][MAXN][MAXM], g[MAXN][MAXN][MAXM], p[MAXN][MAXN][MAXM];
std::vector<int> V;
int ans[MAXN];
void dfs(int l, int r, int t) {
	t = g[l][r][t];
	int pos = p[l][r][t];
	ans[pos] = V[t];
	if (pos > l) dfs(l, pos - 1, t);
	if (pos < r) dfs(pos + 1, r, t);
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &a[i], &b[i], &c[i]), V.push_back(c[i]);
	std::sort(V.begin(), V.end());
	V.erase(std::unique(V.begin(), V.end()), V.end());
	k = V.size();
	for (int i = 1; i <= m; i++) c[i] = std::lower_bound(V.begin(), V.end(), c[i]) - V.begin();
	for (int l = n; l >= 1; l--) {
		for (int r = l; r <= n; r++) {
			memset(sum, 0, sizeof(sum));
			for (int i = 1; i <= m; i++) {
				if (a[i] >= l && b[i] <= r) {
					for (int j = a[i]; j <= b[i]; j++) sum[j][c[i]]++;
				}
			}
			for (int i = l; i <= r; i++) {
				for (int j = k - 1; ~j; j--) sum[i][j] += sum[i][j + 1];
			}
			for (int i = k - 1; ~i; i--) {
				int max = -INF, pos = 0;
				for (int j = l; j <= r; j++) {
					int tmp = V[i] * sum[j][i] + f[l][j - 1][i] + f[j + 1][r][i];
					if (tmp > max) {
						max = tmp;
						pos = j;
					}
				}
				f[l][r][i] = max;
				p[l][r][i] = pos;
				if (f[l][r][i + 1] > f[l][r][i]) {
					f[l][r][i] = f[l][r][i + 1];
					g[l][r][i] = g[l][r][i + 1];
				} else {
					g[l][r][i] = i;
				}
			}
		}
	}
	printf("%d\n", f[1][n][0]);
	dfs(1, n, 0);
	for (int i = 1; i <= n; i++) printf("%d%c", ans[i], " \n"[i == n]);
	return 0;
}