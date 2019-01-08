#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define LOGN 18
int n, m, p[MAXN], a[MAXN], b[MAXN], c[MAXN], s[MAXN];
long long ans = 0;
int main() {
	scanf("%d%d", &n, &m);
	for (int p, q, i = scanf("%d", &p); i < m; i++) {
		scanf("%d", &q), s[std::min(p, q)]++, s[std::max(p, q)]--, p = q;
	}
	for (int i = 1; i < n; i++) scanf("%d%d%d", &a[i], &b[i], &c[i]);
	for (int i = 1; i < n; i++) {
		s[i] += s[i - 1];
		ans += std::min(1LL * b[i] * s[i] + c[i], 1LL * a[i] * s[i]);
	}
	printf("%lld\n", ans);
	return 0;
}