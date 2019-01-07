#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAXN 200010
int t, n, m, q, u[MAXN], v[MAXN], block;
struct query_t {
	int l, r, id;
	inline friend operator<(const query_t &a, const query_t &b) {
		return a.l / block == b.l / block ? a.r < b.r : a.l < b.l;
	}
} queries[MAXN];
struct history_t {
	int *p, v;
} history[MAXN];
int p[MAXN], s[MAXN], cnt, top = 0;
inline int find(int x) {
	while (p[x] != x) x = p[x];
	return x;
}
inline int merge(int x, int y) {
	x = find(x);
	y = find(y);
	if (x == y) return 0;
	if (size[x] > size[y]) std::swap(x, y);
	history[++top] = {&p[x], p[x]};
	history[++top] = {&s[y], s[y]};
	history[++top] = {&cnt, cnt};
	p[x] = y;
	s[y] += s[x];
	cnt--;
	return 1;
}
inline void rollback(int goal) {
	for (; top > goal; top--) (*history[top].p) = history[top].v;
}
int ans[MAXN];
int main() {
	std::ios::sync_with_stdio(0);
	for (std::cin >> t; t; t--) {
		std::cin >> n >> m >> q;
		block = (int)ceil(sqrt(m));
		for (int i = 1; i <= n; i++) p[i] = i, s[i] = 1;
		top = 0;
		cnt = n;
		for (int i = 1; i <= q; i++) {
			queries[i].id = i;
			std::cin >> queries[i].l >> queries[i].r;
			if (queries[i].l / block == queries[i].r / block) {
				for (int j = queries[i].l; j <= queries[i].r; j++) {
					merge(u[j], v[j]);
				}
				ans[i] = cnt;
				rollback(0);
			}
		}
		std::sort(queries + 1, queries + q + 1);
		//
	}
	return 0;
}