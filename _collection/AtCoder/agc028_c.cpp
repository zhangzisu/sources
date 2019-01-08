#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 100010
int n, m, a[MAXN], b[MAXN], c[MAXN << 1];
typedef long long lnt;
lnt sum[MAXN << 1], suma, sumb, ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &a[i], &b[i]);
		suma += (c[++m] = a[i]);
		sumb += (c[++m] = b[i]);
	}
	ans = std::min(suma, sumb);
	std::sort(c + 1, c + m + 1);
	for (int i = 1; i <= m; i++) sum[i] = sum[i - 1] + c[i];
	for (int i = 1; i <= n; i++) {
		int pa = std::upper_bound(c + 1, c + m + 1, a[i]) - c - 1;
		int pb = std::upper_bound(c + 1, c + m + 1, b[i]) - c - 1;
		if (pa > n - 2 && pb > n - 2) {
			ans = std::min(ans, sum[n - 2] + a[i] + b[i]);
		} else if (pa > n - 1) {
			ans = std::min(ans, a[i] + sum[n - 1]);
		} else if (pb > n - 1) {
			ans = std::min(ans, b[i] + sum[n - 1]);
		} else {
			ans = std::min(ans, sum[n]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}