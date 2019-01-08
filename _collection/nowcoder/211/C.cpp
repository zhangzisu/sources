#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAXN 500010
typedef long long lnt;
struct node {
	lnt x, y, z, ans, id;
	inline node(lnt x = 0, lnt y = 0, lnt z = 0, lnt ans = 0, lnt id = 0) : x(x), y(y), z(z), ans(ans), id(id) {}
	inline bool friend operator<(const node& a, const node& b) {
		if (a.y != b.y) return a.y < b.y;
		return a.id < b.id;
	}
} a[MAXN], b[MAXN], tmp[MAXN];
lnt n, c1, c2;
lnt bit[MAXN], c[MAXN], ans[MAXN], query[MAXN];
inline int lowbit(int x) { return x & -x; }
void add(int x, lnt y) {
	for (; x < MAXN; x += lowbit(x)) bit[x] += y;
}
lnt qry(int x) {
	lnt ans = 0;
	for (; x; x -= lowbit(x)) ans += bit[x];
	return ans;
}
void solve(int l, int r, node* a) {
	if (l > r) return;
	if (l == r) {
		a[l].id = l;
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid, a);
	solve(mid + 1, r, a);
	std::merge(a + l, a + mid + 1, a + mid + 1, a + r + 1, tmp + l);
	for (int i = l; i <= r; i++) {
		a[i] = tmp[i];
		if (!a[i].z && a[i].id <= mid) add(a[i].x, 1);
		if (a[i].z && a[i].id > mid) a[i].ans += qry(a[i].x);
	}
	for (int i = l; i <= r; i++)
		if (!a[i].z && a[i].id <= mid) add(a[i].x, -1);
}

signed main() {
	std::ios::sync_with_stdio(0);
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		lnt op, x, y, x2, d;
		std::cin >> op >> x >> y;
		if (op == 1) {
			a[++c1] = node(x + y, -y, 0);
			b[++c2] = node(x, y, 0);
		} else {
			std::cin >> x2 >> d;
			a[++c1] = node(x2 + d + y, -y, i);
			a[++c1] = node(x2 + d + y, -y - d - 1, -i);
			b[++c2] = node(x - 1, y + d, -i);
			b[++c2] = node(x - 1, y - 1, i);
			query[i] = 1;
		}
	}
	for (int i = 1; i <= c1; i++) c[i] = a[i].x;
	std::sort(c + 1, c + c1 + 1);
	for (int i = 1; i <= c1; i++) a[i].x = std::lower_bound(c + 1, c + c1 + 1, a[i].x) - c;
	for (int i = 1; i <= c2; i++) c[i] = b[i].x;
	std::sort(c + 1, c + c2 + 1);
	for (int i = 1; i <= c2; i++) b[i].x = std::lower_bound(c + 1, c + c2 + 1, b[i].x) - c;
	solve(1, c1, a);
	solve(1, c2, b);
	for (int i = 1; i <= c1; i++)
		if (a[i].z > 0)
			ans[a[i].z] += a[i].ans;
		else if (a[i].z < 0)
			ans[-a[i].z] -= a[i].ans;
	for (int i = 1; i <= c2; i++)
		if (b[i].z > 0)
			ans[b[i].z] += b[i].ans;
		else if (b[i].z < 0)
			ans[-b[i].z] -= b[i].ans;
	for (int i = 1; i <= n; i++)
		if (query[i]) std::cout << ans[i] << '\n';
	return 0;
}
