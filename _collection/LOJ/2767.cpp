#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
int n, q, a[MAXN], b[MAXN], limit[31][2];
inline void query() {
	int ans = 0;
	for (int i = 0; i <= 30; i++) {
		if (limit[i][0] && limit[i][1]) return puts("-1"), void();
		if (limit[i][1]) ans |= 1 << i;
	}
	printf("%d\n", ans);
}
inline void gao(int p, int v) {
	if (!p || p == n) return;
	for (int i = 30; ~i; i--) {
		if (((a[p] >> i) & 1) != ((a[p + 1] >> i) & 1)) {
			if ((a[p] >> i) & 1) {
				limit[i][1] += v;
			} else {
				limit[i][0] += v;
			}
			break;
		}
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i < n; i++) gao(i, 1);
	query();
	for (int p, v = scanf("%d", &q); q; q--) {
		scanf("%d%d", &p, &v);
		gao(p - 1, -1);
		gao(p, -1);
		a[p] = v;
		gao(p - 1, 1);
		gao(p, 1);
		query();
	}
	return 0;
}