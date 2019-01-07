#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAXN 200010
#define SQRT 450
typedef long long lnt;
int count[2000000], n, m, a[MAXN], L = 0, R = -1;
lnt cur, ans[MAXN];
struct query {
	int l, r, id;
	inline int friend operator<(const query &a, const query &b) {
		return a.l / SQRT == b.l / SQRT ? a.r < b.r : a.l < b.l;
	}
} q[MAXN];
inline void add(int num, int d) {
	cur -= 1LL * num * count[num] * count[num];
	count[num] += d;
	cur += 1LL * num * count[num] * count[num];
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i <= m; i++) q[i].id = i, std::cin >> q[i].l >> q[i].r;
	std::sort(q + 1, q + m + 1);
	for (int i = 1; i <= m; i++) {
		while (L > q[i].l) add(a[--L], 1);
		while (R < q[i].r) add(a[++R], 1);
		while (L < q[i].l) add(a[L++], -1);
		while (R > q[i].r) add(a[R--], -1);
		ans[q[i].id] = cur;
	}
	for (int i = 1; i <= m; i++) std::cout << ans[i] << std::endl;
	return 0;
}