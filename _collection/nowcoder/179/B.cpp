#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 500010
int n, c[MAXN], ans = 1;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", c + i);
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j * j <= i; j++) {
			if (i % j) continue;
			if (c[i] != c[j]) {
				ans++;
				break;
			}
			if (c[i] != c[i / j]) {
				ans++;
				break;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}