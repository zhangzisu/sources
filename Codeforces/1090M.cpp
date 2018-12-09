#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, k, a[MAXN], ans;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1, now = 0; i <= n; i++) {
		scanf("%d", a + i);
		if (a[i] != a[i - 1])
			ans = std::max(ans, ++now);
		else
			now = 1;
	}
	printf("%d\n", ans);
	return 0;
}