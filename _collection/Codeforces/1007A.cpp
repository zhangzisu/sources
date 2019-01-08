#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, a[MAXN], ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + n + 1);
	for (int i = 1, cur = 1; i <= n; i++) {
		if (a[cur] < a[i]) ans++, cur++;
	}
	printf("%d\n", ans);
	return 0;
}