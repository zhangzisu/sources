#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 500010
typedef long long lnt;
int n, m, b[MAXN];
lnt a[MAXN], ans;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), a[i] ^= a[i - 1];
	for (int i = 62; ~i; i--) {
		int sum = 0;
		for (int j = 1; j <= n; j++)
			if (!b[j]) sum += (~a[j] >> i) & 1;
		if (sum < m || ((a[n] >> i) & 1)) {
			ans |= 1ULL << i;
			continue;
		}
		for (int j = 1; j <= n; j++)
			if ((a[j] >> i) & 1) b[j] = 1;
	}
	printf("%lld\n", ans);
	return 0;
}