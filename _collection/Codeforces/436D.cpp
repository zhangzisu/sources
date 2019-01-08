#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MAXM 2010
inline void up(int &x, int y) {
	if (y > x) x = y;
}
int n, m;
int a[MAXN], b[MAXM], l[MAXN], r[MAXN], f[MAXN], g[MAXN];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	std::sort(a + 1, a + n + 1);
	l[1] = 1;
	for (int i = 2; i <= n; i++) l[i] = a[i] == a[i - 1] + 1 ? l[i - 1] : i;
	r[n] = n;
	for (int i = n - 1; i; i--) r[i] = a[i] + 1 == a[i + 1] ? r[i + 1] : i;

	for (int i = 1; i <= m; i++) scanf("%d", b + i);
	std::sort(b + 1, b + m + 1);
	for (int i = 1; i <= n; i++) {
		int cnt = 0;
		for (int j = m; j >= 1; j--) {
			if (b[j] > a[i]) continue;
			int delta = a[i] - b[j];
			if (i - delta <= 0) break;
			up(f[i], ++cnt + g[l[i - delta]]);
		}
		if (l[i] == i) up(f[i], g[i]);
		up(g[i + 1], f[i]);
		up(g[i + 1], g[i]);
		up(g[i + 1], f[i]);
		cnt = 0;
		for (int j = 1; j <= m; j++) {
			if (b[j] <= a[i]) continue;
			int delta = b[j] - a[i];
			if (delta > n) break;
			up(g[i + delta + 1], ++cnt + f[i]);
		}
	}
	printf("%d\n", g[n + 1]);
	return 0;
}