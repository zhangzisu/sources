#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 300010
int n, a[MAXN], m, b[MAXN], pa, pb, ans;
long long sa, sb;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) scanf("%d", &b[i]);
	while (pa < n && pb < m) {
		sa = a[++pa];
		sb = b[++pb];
		ans++;
		while (sa != sb && (pa < n || pb < m)) {
			if (sa < sb) {
				if (pa >= n) return puts("-1"), 0;
				sa += a[++pa];
			}
			if (sa > sb) {
				if (pb >= m) return puts("-1"), 0;
				sb += b[++pb];
			}
		}
		if (sa != sb) return puts("-1"), 0;
	}
	if (pa < n || pb < m) return puts("-1"), 0;
	printf("%d\n", ans);
	return 0;
}