#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
int n, sum[MAXN];
int main() {
    freopen("blist.in", "r", stdin);
	freopen("blist.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int s, t, b;
		scanf("%d%d%d", &s, &t, &b);
		for (int i = s; i <= t; i++) sum[i] += b;
	}
	int ans = 0;
	for (int i = 1; i <= 1000; i++) ans = std::max(ans, sum[i]);
	printf("%d\n", ans);
	return 0;
}