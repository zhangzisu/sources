#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
int n, m, p, k, a[1010][1010], vis[1010][1010];
struct data_t {
	int x, y, v;
	inline bool friend operator<(const data_t &a, const data_t &b) {
		return a.v > b.v;
	}
} data[1000010];
std::queue<int> Q;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &a[i][j]);
			data[++p] = (data_t){i, j, a[i][j]};
			min = std::min(min, a[i][j]);
			max = std::max(max, a[i][j]);
		}
	}
	std::sort(data + 1, data + p + 1);
	while (Q.size()) {
		//
	}
}