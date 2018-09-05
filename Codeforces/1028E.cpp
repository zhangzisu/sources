#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200000
int n, m, ans, c[MAXN], b[MAXN];
long long a[MAXN], s;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
		m = std::max(m, b[i]);
	}
	ans = 1;
	for (int i = 1; i <= n; i++) ans &= b[i] == m;
	if (ans) {
		if (m) return puts("NO"), 0;
		puts("YES");
		for (int i = 1; i <= n; i++) printf("%d ", 1);
		puts("");
		return 0;
	}
	b[0] = b[n];
	for (int x = 1; x <= n; x++)
		if (b[x] == m && b[x - 1] != m) {
			puts("YES");
			a[x] = 2LL * b[x];
			for (int i = n - 2; ~i; i--) a[(x + i) % n + 1] = b[(x + i) % n + 1] + a[(x + i + 1) % n + 1];
			a[x] = b[x];
			for (int i = 1; i <= n; i++) printf("%lld ", a[i]);
			puts("");
			return 0;
		}
	puts("NO");
	return 0;
}