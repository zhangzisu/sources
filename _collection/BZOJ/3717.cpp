#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, m, all, a[24], b[200], f[1 << 24], g[1 << 24];
inline int cmp(int x, int y) { return x > y; }
inline void up(int x, int tmp, int pos) {
	if (pos < g[x] || (pos == g[x] && tmp < f[x])) {
		f[x] = tmp;
		g[x] = pos;
	}
}
int main() {
	scanf("%d%d", &n, &m);
	all = (1 << n) - 1;
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < m; i++) scanf("%d", &b[i]);
	std::sort(b, b + m, cmp);
	memset(g, 0x3F, sizeof(g));
	f[0] = 0;
	g[0] = 0;
	for (int i = 0; i < all; i++) {
		for (int j = 0; j < n; j++) {
			if (g[i] >= m) continue;
			if (!((i >> j) & 1)) {
				int tmp = f[i] + a[j];
				if (tmp <= b[g[i]]) {
					up(i | (1 << j), tmp, g[i]);
				} else {
					tmp = a[j];
					if (tmp <= b[g[i] + 1]) {
						up(i | (1 << j), tmp, g[i] + 1);
					}
				}
			}
		}
	}
	if (g[all] >= m) return puts("NIE"), 0;
	printf("%d\n", g[all] + 1);
	return 0;
}