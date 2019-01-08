#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
typedef long long lnt;
lnt n, a[MAXN], sum, sum2;
int main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), sum += a[i], sum2 += a[i] * a[i];
	for (int i = 1; i <= n; i++) {
		printf("%lld", sum2 * (n - 1) - a[i] * a[i] * (n - 1) - (sum - a[i]) * (sum - a[i]));
		if (i != n) putchar(' ');
	}
	return 0;
}