#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 400010

int n, a[MAXN];
double ans = 0;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < 2 * n; i++) scanf("%d", &a[i]);
	std::sort(a, a + 2 * n);
	for (int i = 0; i < 2 * n; i++) ans += 1. * i * a[i] / (2 * n - 1);
	printf("%.10lf\n", ans);
	return 0;
}