#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
const int MAXN = 21;
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int t, n, k, l, ans, f[2][1 << MAXN];
int main() {
	for (scanf("%d", &t); t; t--) {
		scanf("%d%d%d", &n, &k, &l);
		memset(f, 0, sizeof(f));
		ans = 0;
		f[0][1] = 1;
		int mask = (1 << (k + 1)) - 1;
		for (int i = 0; i < n; i++) {
			int now = i & 1, next = now ^ 1;
			memset(f[next], 0, sizeof(f[next]));
			for (int d = 1; d <= mask; d++) {
				int &t = f[now][d];
				if (!t) continue;
				for (int j = 0; j <= k && j <= l; j++) {
					up(f[next][(d | (d << j)) & mask], t);
				}
				int rest = std::max(l - k, 0);
				up(f[next][d], 1LL * t * rest % MOD);
			}
		}
		for (int d = 1; d <= mask; d++)
			if ((d >> k) & 1) up(ans, f[n & 1][d]);
		printf("%d\n", ans);
	}
	return 0;
}