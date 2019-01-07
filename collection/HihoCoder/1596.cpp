#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 61
#define MOD 1000000007
int f[MAXN][MAXN][MAXN][MAXN][2];
int n, m, a[MAXN], b[MAXN], ans;
std::vector<int> V;
inline bool valid(int x, int y, int z) {
	return V[x] + V[z] >= 2 * V[y];
}
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), V.push_back(a[i]);
	std::sort(V.begin(), V.end());
	V.erase(std::unique(V.begin(), V.end()), V.end());
	for (int i = 1; i <= n; i++) a[i] = std::lower_bound(V.begin(), V.end(), a[i]) - V.begin();
	std::sort(a + 1, a + n + 1);
	for (int i = n; i >= 1; i--) b[a[i]] = std::max(b[a[i]], i);
	m = (int)V.size();
	int count = 0, frc = 1;
	for (int i = 1; i <= n && a[i] == a[1]; i++) count++, frc = 1LL * frc * i % MOD;
	f[count][a[1]][a[1]][a[1]][0] = frc;
	for (int i = count; i < n; i++) {
		for (int x = 0; x < m; x++) {
			for (int y = 0; y < m; y++) {
				for (int z = 0; z < m; z++) {
					if (valid(x, a[i], a[i + 1])) {
						up(f[i + 1][a[i]][y][z][0], f[i][x][y][z][0]);
					}
					if (valid(y, z, a[i + 1])) {
						up(f[i + 1][x][z][a[i]][1], f[i][x][y][z][0]);
					}
					if (valid(x, z, a[i + 1])) {
						up(f[i + 1][z][y][a[i]][0], f[i][x][y][z][1]);
					}
					if (valid(y, a[i], a[i + 1])) {
						up(f[i + 1][x][a[i]][z][1], f[i][x][y][z][1]);
					}
				}
			}
		}
	}
	for (int x = 0; x < m; x++) {
		for (int y = 0; y < m; y++) {
			for (int z = 0; z < m; z++) {
				up(ans, f[n][x][y][z][0]);
				up(ans, f[n][x][y][z][1]);
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}