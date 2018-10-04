#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2010
int n, m, x, a[MAXN], b[MAXN];
int sa[MAXN], sb[MAXN], ta[MAXN], tb[MAXN];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), sa[i] = sa[i - 1] + a[i];
	for (int i = 1; i <= m; i++) scanf("%d", &b[i]), sb[i] = sb[i - 1] + b[i];
	scanf("%d", &x);
	for (int i = 1; i <= n; i++) {
		ta[i] = 0x3F3F3F3F;
		for (int j = 1; j <= n - i + 1; j++) {
			ta[i] = std::min(ta[i], sa[j + i - 1] - sa[j - 1]);
		}
	}
	for (int i = 1; i <= m; i++) {
		tb[i] = 0x3F3F3F3F;
		for (int j = 1; j <= m - i + 1; j++) {
			tb[i] = std::min(tb[i], sb[j + i - 1] - sb[j - 1]);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (1LL * ta[i] * tb[j] <= x) {
				ans = std::max(ans, i * j);
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}