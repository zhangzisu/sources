#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, k, a[MAXN], ans = 0x3F3F3F3F;
inline int dis(int x, int y) {
	if (1LL * x * y >= 0) {
		return std::max(std::abs(x), std::abs(y));
	} else {
		return std::min(std::abs(x), std::abs(y)) * 2 + std::max(std::abs(x), std::abs(y));
	}
}
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		if (i + k - 1 <= n)
			ans = std::min(ans, dis(a[i + k - 1], a[i]));
	}
	printf("%d\n", ans);
	return 0;
}