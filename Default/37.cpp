#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100
int n, d, x[MAXN], y[MAXN], G[MAXN][MAXN], id[MAXN];
int ans = 0, result[MAXN], ban[MAXN];
int main() {
	scanf("%d%d", &n, &d);
	for (int i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			G[i][j] = 1LL * (x[i] - x[j]) * (x[i] - x[j]) + 1LL * (y[i] - y[j]) * (y[i] - y[j]) <= 1LL * d * d;
		}
	}
	for (int i = 0; i < n; i++) id[i] = i;
	for (int _ = 100000; _; _--) {
		std::random_shuffle(id, id + n);
		memset(ban, 0, sizeof(int) * n);
		int now = 0;
		for (int i = 0; i < n; i++) {
			if (ban[id[i]]) continue;
			++now;
			for (int j = 0; j < n; j++) ban[j] |= !G[id[i]][j];
		}
		if (now > ans) {
			ans = now;
			memcpy(result, ban, sizeof(int) * n);
		}
	}
	printf("%d\n", ans);
	for (int i = 0; i < n; i++)
		if (!result[i]) printf("%d ", i + 1);
	puts("");
	return 0;
}