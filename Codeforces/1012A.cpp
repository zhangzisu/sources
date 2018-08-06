#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
int n, m, a[MAXN];
long long ans;
int main() {
	scanf("%d", &m);
	n = m << 1;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + n + 1);
	ans = 1LL * (a[m] - a[1]) * (a[n] - a[m + 1]);
	for (int i = 2; i <= m; i++)
		ans = std::min(ans, 1LL * (a[n] - a[1]) * (a[i + m - 1] - a[i]));
	printf("%lld\n", ans);
	return 0;
}