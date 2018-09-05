#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int t, x;
long long ans = 0;
int main() {
	for (scanf("%d", &t); t; t--) {
		scanf("%d", &x);
		ans = 0;
		for (int i = 1, j; i <= x; i = j + 1) {
			j = std::min(x / (x / i), x);
			ans += 1LL * (x / i) * (j - i + 1);
		}
		printf("%lld\n", ans);
	}
	return 0;
}