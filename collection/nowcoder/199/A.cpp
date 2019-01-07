#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define N 20
int n, m, to[N][3], t[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v);
		to[v][++t[v]] = u;
		to[u][++t[u]] = v;
	}
	for (int i = 0; i < (1 << n); i++) {
		for (int j = 1; j <= n; j++) {
			int cj = (i >> (j - 1)) & 1, d = 0;
			for (int k = 1; k <= t[j]; k++) {
				int ck = (i >> (to[j][k] - 1)) & 1;
				if (cj == ck) {
					if (++d > 1) break;
				}
			}
			if (d > 1) goto fail;
		}
		for (int j = 0; j < n; j++) printf("%d%c", 1 + ((i >> j) & 1), " \n"[j == n - 1]);
		return 0;
	fail:;
	}
	puts("-1");
	return 0;
}