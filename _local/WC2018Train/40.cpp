#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 10010
const int N = 20;
const int INF = 0x3F3F3F3F;
int t, n, m, k, l, a[MAXN], b[MAXN], p[N], dis[N][N], tmp[MAXN], f[1 << N];
std::queue<int> Q;
int main() {
	for (scanf("%d", &t); t; t--) {
		scanf("%d%d%d", &n, &k, &l);
		memset(a, 0, sizeof(a));
		for (int i = 1, x; i <= k; i++) scanf("%d", &x), a[x] = 1;
		for (int i = 1; i <= l; i++) scanf("%d", b + i);
		m = 0;
		for (int i = 0; i <= n; i++) {
			if (a[i] != a[i + 1]) {
				p[m++] = i;
			}
		}
		if (m & 1) {
			puts("-1");
			continue;
		}
		for (int i = 0; i < m; i++) {
			memset(tmp, 0x3F, sizeof(tmp)), tmp[p[i]] = 0, Q.push(p[i]);
			while (Q.size()) {
				int x = Q.front();
				Q.pop();
				for (int j = 1; j <= l; j++) {
					if (x - b[j] >= 0 && tmp[x - b[j]] > tmp[x] + 1) tmp[x - b[j]] = tmp[x] + 1, Q.push(x - b[j]);
					if (x + b[j] <= n && tmp[x + b[j]] > tmp[x] + 1) tmp[x + b[j]] = tmp[x] + 1, Q.push(x + b[j]);
				}
			}
			for (int j = 0; j < m; j++) dis[i][j] = tmp[p[j]];
		}
		memset(f, 0x3F, sizeof(f));
		f[0] = 0;
		for (int d = 1; d < (1 << m); d++) {
			for (int i = 0; i < m; i++) {
				if ((d >> i) & 1) {
					for (int j = i + 1; j < m; j++) {
						if ((d >> j) & 1) {
							f[d] = std::min(f[d], f[d - (1 << i) - (1 << j)] + dis[i][j]);
						}
					}
					break;
				}
			}
		}
		printf("%d\n", f[(1 << m) - 1] == INF ? -1 : f[(1 << m) - 1]);
	}
	return 0;
}