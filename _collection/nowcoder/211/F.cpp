#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 5000010
int n, m;
long long b[MAXN], a[MAXN], ans;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, x; i <= n; i++) scanf("%d", &x), a[x]++;
	for (int i = 1; i <= m; i++)for (int j = i; j <= m; b[j] += a[i], j += i);
	for (int i = 1; i <= m; b[i] += b[i - 1], i++);
	for (int i = m; i; a[i] += a[i + 1], i--);
	for (int i = 1; i <= m; i++)for (int j = i; j <= m; b[i] += a[j], j += i);
	for (int i = 1; i <= m; i++)ans ^= b[i];
	printf("%lld\n", ans);
	return 0;
}