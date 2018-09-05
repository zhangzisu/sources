#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 6000000
int n, p, q, prime[MAXN], cnt[MAXN], vis[MAXN], ans[MAXN];
inline void shai() {
	for (int i = 2; i < MAXN; i++) {
		if (!vis[i]) {
			cnt[i] = 1;
			prime[++p] = i;
		}
		for (int j = 1; j <= p && prime[j] * i < MAXN; j++) {
			vis[i * prime[j]] = 1;
			cnt[i * prime[j]] = cnt[i] + 1;
			if (i % prime[j] == 0) break;
		}
	}
}
std::vector<std::pair<int, int>> query[MAXN];
int a[MAXN], f[MAXN][14], g[14];
inline void up(int &x, int y) {
	if (y > x) x = y;
}
int main() {
	shai();
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		for (int j = 1; prime[j] * prime[j] <= a[i]; j++) {
			while (a[i] % (prime[j] * prime[j]) == 0) a[i] /= prime[j], a[i] /= prime[j];
		}
	}
	for (int i = 1, l, r; i <= q; i++) {
		scanf("%d%d", &l, &r);
		query[r].emplace_back(l, i);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j * j <= a[i]; j++) {
			if (a[i] % j == 0) {
				for (int k = 0; cnt[j] + k < 14; k++) up(g[cnt[j] + k], f[a[i] / j][k]);
				for (int k = 0; cnt[a[i] / j] + k < 14; k++) up(g[cnt[a[i] / j] + k], f[j][k]);
			}
		}
		for (int j = 1; j * j <= a[i]; j++) {
			if (a[i] % j == 0) {
				up(f[a[i] / j][cnt[j]], i);
				up(f[j][cnt[a[i] / j]], i);
			}
		}
		for (auto x : query[i]) {
			for (int j = 0; j < 14; j++) {
				if (g[j] >= x.first) {
					ans[x.second] = j;
					break;
				}
			}
		}
	}
	for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
	return 0;
}
