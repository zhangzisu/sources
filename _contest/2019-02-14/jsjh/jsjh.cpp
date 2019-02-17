#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100
using lnt = long long;
int N, x[MAXN], y[MAXN];
lnt cross(std::pair<int, int> a, std::pair<int, int> b) {
	return 1LL * a.first * b.second - 1LL * a.second * b.first;
}
int main() {
	freopen("jsjh.in", "r", stdin);
	freopen("jsjh.out", "w", stdout);
	scanf("%d", &N);
	for (int n = 0; n < N; n++) {
		scanf("%d%d", x + n, y + n);
		int ans = 0;
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= n; j++) {
				if (x[i] >= x[j]) continue;
				bool l[2] = {true, true};
				bool r[2] = {true, true};
				for (int k = 0; k <= n; k++) {
					if (k == i || k == j) continue;
					lnt c = cross({x[k] - x[i], y[k] - y[i]}, {x[j] - x[i], y[j] - y[i]});
					int p = x[k] > 0;
					if (c < 0) {
						l[p] = 0;
						if (!l[!p] || !r[p]) goto fail;
					} else if (c > 0) {
						r[p] = 0;
						if (!r[!p] || !l[p]) goto fail;
					} else {
						if (x[k] < x[j]) goto fail;
					}
				}
				ans++;
			fail:;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
