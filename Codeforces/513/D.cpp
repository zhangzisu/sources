#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, l[MAXN], r[MAXN];
long long ans = 0;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &l[i], &r[i]), ans += l[i], ans += r[i], ans++;
	std::sort(l + 1, l + n + 1);
	std::sort(r + 1, r + n + 1);
	for (int i = 1; i <= n; i++) ans -= std::min(l[i], r[i]);
	printf("%lld\n", ans);
}