#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int t, n, a[MAXN], count[1000010], g[2];
long long cnt = 0;
int main() {
	for (scanf("%d", &t); t; t--) {
		memset(count, 0, sizeof(count));
		g[0] = g[1] = cnt = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			cnt += g[(a[i] & 1)];
			cnt -= count[a[i] ^ 2];
			cnt -= count[a[i]];
			count[a[i]]++;
			g[a[i] & 1]++;
		}
		printf("%lld\n", cnt);
	}
	return 0;
}