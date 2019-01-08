#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
int bin[MAXN], v[MAXN], p[MAXN], lmax[MAXN][20], vmax[MAXN][20], n, ans = 1;
inline std::pair<int, int> query(int l, int r) {
	int len = bin[r - l + 1];
	int delta = 1 << len;
	return std::make_pair(std::max(lmax[l][len], lmax[r - delta + 1][len]), std::max(vmax[l][len], vmax[r - delta + 1][len]));
}
int main() {
	scanf("%d", &n);
	bin[0] = -1;
	for (int i = 1; i <= n; i++) bin[i] = bin[i >> 1] + 1;
	for (int i = 1; i <= n; i++) scanf("%d", &v[i]), vmax[i][0] = v[i];
	for (int i = 1; i <= n; i++) lmax[i][0] = p[v[i]], p[v[i]] = i;
	for (int d = 1; d < 20; d++) {
		const int delta = 1 << (d - 1);
		for (int i = 1; i <= n; i++) {
			lmax[i][d] = std::max(lmax[i][d - 1], lmax[i + delta][d - 1]);
			vmax[i][d] = std::max(vmax[i][d - 1], vmax[i + delta][d - 1]);
		}
	}
	for (int i = 1; i <= n; i++) {
		register int l = i + ans - 1, r = n;
		while (l <= r) {
			int mid = (l + r) >> 1;
			std::pair<int, int> res = query(i, mid);
			if (res.first < i && res.second == mid - i + 1) {
				ans = mid - i + 1;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}