#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int t, n, m;
std::pair<int, int> a[MAXN];
int main() {
	scanf("%d", &t);
	for (int T = 1; T <= t; T++) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i].first);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i].second);
		std::sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; i++) {
			if ((m -= a[i].second) < 0) {
				printf("Case %d: %d\n", T, i - 1);
				goto fin;
			}
		}
		printf("Case %d: %d\n", T, n);
	fin:;
	}
	return 0;
}