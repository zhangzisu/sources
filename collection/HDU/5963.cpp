#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define MAXN 40010
int t, n, m, cnt[MAXN];
std::map<int, int> M[MAXN];
int main() {
	for (scanf("%d", &t); t; t--) {
		scanf("%d%d", &n, &m);
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1, u, v, w; i < n; i++) {
			scanf("%d%d%d", &u, &v, &w);
			if (u > v) std::swap(u, v);
			cnt[u] += w;
			cnt[v] += w;
			M[u][v] = w;
		}
		for (int op, x, y, z; m; m--) {
			scanf("%d", &op);
			if (op) {
				scanf("%d%d%d", &x, &y, &z);
				if (x > y) std::swap(x, y);
				cnt[x] -= M[x][y];
				cnt[y] -= M[x][y];
				M[x][y] = z;
				cnt[x] += z;
				cnt[y] += z;
			} else {
				scanf("%d", &x);
				puts(cnt[x] & 1 ? "Girls win!" : "Boys win!");
			}
		}
		for (int i = 1; i <= n; i++) M[i].clear();
	}
	return 0;
}