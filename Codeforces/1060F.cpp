#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>
#define MAXN 110
typedef long double lb;
int n, size[MAXN];
std::vector<int> next[MAXN];
lb frc[MAXN], f[MAXN][MAXN], g[MAXN], h[MAXN];
inline lb C(int x, int y) {
	return frc[x] / frc[y] / frc[x - y];
}
inline lb calc(int x, int y) {
	return C(x + y, y);
}
void dp(int x, int fa) {
	size[x] = 1;
	f[x][0] = 1;
	for (int y : next[x]) {
		if (y == fa) continue;
		dp(y, x);
		for (int i = 0; i <= size[x] + size[y]; i++) g[i] = h[i] = 0;
		for (int i = 0; i <= size[y]; i++) {
			for (int j = 1; j <= size[y]; j++) {
				g[i] += j <= i ? f[y][j - 1] * 0.5 : f[y][i];
			}
		}
		for (int i = 0; i < size[x]; i++) {
			for (int j = 0; j <= size[y]; j++) {
				h[i + j] += f[x][i] * g[j] * calc(i, j) * calc(size[x] - i - 1, size[y] - j);
			}
		}
		for (int i = 0; i <= size[x] + size[y]; i++) f[x][i] = h[i];
		size[x] += size[y];
	}
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin >> n;
	for (int i = 1, u, v; i < n; i++) {
		std::cin >> u >> v;
		next[u].push_back(v);
		next[v].push_back(u);
	}
	frc[0] = 1;
	for (int i = 1; i < MAXN; i++) frc[i] = frc[i - 1] * i;
	for (int i = 1; i <= n; i++) {
		memset(f, 0, sizeof(f));
		dp(i, 0);
		std::cout << std::fixed << std::setprecision(10) << (f[i][n - 1] / frc[n - 1]) << std::endl;
	}
	return 0;
}