#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
int n;
double h, a[MAXN];
int main() {
    // freopen("alpinism.in", "r", stdin);
	// freopen("alpinism.out", "w", stdout);
	scanf("%lf%d", &h, &n);
	double ans = 1e100;
	for (int i = 1; i <= n; i++) {
		scanf("%lf", a + i);
		double rest = h - a[i];
		double tmp = .5 * a[i];
		if (tmp <= rest) {
			ans = std::min(ans, tmp + rest);
		} else {
			ans = std::min(ans, a[i]);
		}
	}
	printf("%f\n", ans);
	return 0;
}