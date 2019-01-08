#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 10010
int n, m, k, ans, p[MAXN], c[MAXN], e[MAXN], f[MAXN];
int main() {
	scanf("%d%d", &m, &n), k = m;
	for (int i = 1; i <= m; i++) scanf("%d", &p[i]);
	for (int i = 1; i <= n; i++) scanf("%d%d", &c[i], &e[i]), k = std::max(k, c[i]);
	std::sort(p + 1, p + m + 1, [](int a, int b) { return a > b; });
	for (int i = 1; i <= m; i++) p[i] += p[i - 1];
	for (int i = 1; i <= k; i++) f[i] = 0x3F3F3F3F;
	for (int i = 1; i <= n; i++) {
		for (int j = k; j >= c[i]; j--) {
			f[j] = std::min(f[j], f[j - c[i]] + e[i]);
		}
		for (int j = k; j >= 1; j--) f[j - 1] = std::min(f[j - 1], f[j]);
	}
	for (int i = 0; i <= m; i++) ans = std::max(ans, p[i] - f[i]);
	printf("%d\n", ans);
	return 0;
}