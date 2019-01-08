#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline int $() {
	register int x = 0;
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 100010
int n, m, k, root, range00, range01, range10, range11, range20, range21;
struct kdtree_t {
	int key0, key1, key2, max0, max1, max2, min0, min1, min2, l, r;
} tree[MAXN];
inline void reset(int x) {
	tree[x].min0 = tree[x].max0 = tree[x].key0;
	tree[x].min1 = tree[x].max1 = tree[x].key1;
	tree[x].min2 = tree[x].max2 = tree[x].key2;
}
inline void pushUp(int x, int y) {
	tree[x].max0 = std::max(tree[x].max0, tree[y].max0);
	tree[x].min0 = std::min(tree[x].min0, tree[y].min0);
	tree[x].max1 = std::max(tree[x].max1, tree[y].max1);
	tree[x].min1 = std::min(tree[x].min1, tree[y].min1);
	tree[x].max2 = std::max(tree[x].max2, tree[y].max2);
	tree[x].min2 = std::min(tree[x].min2, tree[y].min2);
}
int pos[MAXN], D;
inline int cmp0(const int &a, const int &b) { return tree[a].key0 < tree[b].key0; }
inline int cmp1(const int &a, const int &b) { return tree[a].key1 < tree[b].key1; }
inline int cmp2(const int &a, const int &b) { return tree[a].key2 < tree[b].key2; }
void build(int &root, int l, int r, int d) {
	int mid = (l + r) >> 1;
	D = d;
	std::nth_element(pos + l, pos + mid, pos + r + 1, d == 0 ? cmp0 : d == 1 ? cmp1 : cmp2);
	root = pos[mid];
	if (mid > l) build(tree[root].l, l, mid - 1, (d + 1) % 3), pushUp(root, tree[root].l);
	if (mid < r) build(tree[root].r, mid + 1, r, (d + 1) % 3), pushUp(root, tree[root].r);
}
int l0, r0, l1, r1, l2, r2;
int query(int n) {
	if (!n) return 0;
	kdtree_t &x = tree[n];
	if (x.min0 >= l0 && x.min1 >= l1 && x.min2 >= l2 && x.max0 <= r0 && x.max1 <= r1 && x.max2 <= r2) return 1;
	if (x.min0 > r0 || x.min1 > r1 || x.min2 > r2 || x.max0 < l0 || x.max1 < l1 || x.max2 < l2) return 0;
	if (x.key0 >= l0 && x.key1 >= l1 && x.key2 >= l2 && x.key0 <= r0 && x.key1 <= r1 && x.key2 <= r2) return 1;
	return query(x.l) || query(x.r);
}
int main() {
	range00 = $();
	range10 = $();
	range20 = $();
	n = $(), m = $(), k = $();
	range01 = range11 = range21 = 1;
	for (int i = 1, a, b, c; i <= n; i++) {
		a = $(), b = $(), c = $();
		range00 = std::min(range00, a);
		range01 = std::max(range01, a);
		range10 = std::min(range10, b);
		range11 = std::max(range11, b);
		range20 = std::min(range20, c);
		range21 = std::max(range21, c);
	}
	if (m == 0) {
		puts("CORRECT");
		for (int i = 1, a, b, c; i <= k; i++) {
			a = $(), b = $(), c = $();
			if (range00 <= a && range01 >= a && range10 <= b && range11 >= b && range20 <= c && range21 >= c) {
				puts("OPEN");
			} else {
				puts("UNKNOWN");
			}
		}
		return 0;
	}
	for (int i = 1; i <= m; i++) {
		bool flag = 1;
		tree[i].key0 = $();
		flag &= tree[i].key0 >= range00 && tree[i].key0 <= range01;
		tree[i].key1 = $();
		flag &= tree[i].key1 >= range10 && tree[i].key1 <= range11;
		tree[i].key2 = $();
		flag &= tree[i].key2 >= range20 && tree[i].key2 <= range21;
		if (flag) return puts("INCORRECT"), 0;
		pos[i] = i;
		reset(i);
	}
	puts("CORRECT");
	build(root, 1, m, 0);
	for (int i = 1, a, b, c; i <= k; i++) {
		a = $(), b = $(), c = $();
		if (range00 <= a && range01 >= a && range10 <= b && range11 >= b && range20 <= c && range21 >= c) {
			puts("OPEN");
		} else {
			l0 = std::min(range00, a), r0 = std::max(range01, a);
			l1 = std::min(range10, b), r1 = std::max(range11, b);
			l2 = std::min(range20, c), r2 = std::max(range21, c);
			if (query(root)) {
				puts("CLOSED");
			} else {
				puts("UNKNOWN");
			}
		}
	}
	return 0;
}