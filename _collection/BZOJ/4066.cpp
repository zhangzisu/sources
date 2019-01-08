#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline int $() {
	register int x = 0;register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 200010
int f[MAXN], root = 0, cnt = 0;
struct node {
	int val[2], max[2], min[2], l, r, f, dat, sum;
	inline node(int x = 0, int y = 0, int v = 0) {
		val[0] = max[0] = min[0] = x;
		val[1] = max[1] = min[1] = y;
		dat = sum = v;l = r = f = 0;
	}
	inline void reset() {
		max[0] = min[0] = val[0];
		max[1] = min[1] = val[1];
		sum = dat;l = r = f = 0;
	}
	inline void get(const node &b){
		max[0] = std::max(max[0], b.max[0]);
		min[0] = std::min(min[0], b.min[0]);
		max[1] = std::max(max[1], b.max[1]);
		min[1] = std::min(min[1], b.min[1]);
		sum += b.sum;
	}
} tree[MAXN];
inline void insert(int x) {
	register int f = 0, d = 0;
	register int *p = &root;
	while (*p) {
		f = *p;
		if (tree[x].val[d] <= tree[*p].val[d])p = &(tree[*p].l);
		else p = &(tree[*p].r);
		d = !d;
	}
	*p = x;
	tree[x].f = f;
	while (f) {
		tree[f].sum = tree[f].dat;
		if (tree[f].l) tree[f].get(tree[tree[f].l]);
		if (tree[f].r) tree[f].get(tree[tree[f].r]);
		f = tree[f].f;
	}
}
int d;
inline int cmp(const int &a, const int &b) { return tree[a].val[d] < tree[b].val[d]; }
void build(int &n, int l, int r, int d) {
	int mid = (l + r) >> 1;::d = d;
	std::nth_element(f + l, f + mid, f + r, cmp);
	n = f[mid];
	if (l < mid) build(tree[n].l, l, mid - 1, !d), tree[n].get(tree[tree[n].l]);
	if (r > mid) build(tree[n].r, mid + 1, r, !d), tree[n].get(tree[tree[n].r]);
	if (tree[n].l) tree[tree[n].l].f = n;
	if (tree[n].r) tree[tree[n].r].f = n;
}
inline void rebuild() {
	for (int i = 1; i <= cnt; i++) f[i] = i, tree[i].reset();
	build(root, 1, cnt, 0);
}
int query(int n, int x1, int y1, int x2, int y2) {
	if (!n) return 0;
	if (tree[n].max[0] < x1 || tree[n].min[0] > x2 || tree[n].max[1] < y1 || tree[n].min[1] > y2) return 0;
	if (tree[n].min[0] >= x1 && tree[n].max[0] <= x2 && tree[n].min[1] >= y1 && tree[n].max[1] <= y2) return tree[n].sum;
	int ret = 0;
	if (tree[n].val[0] >= x1 && tree[n].val[0] <= x2 && tree[n].val[1] >= y1 && tree[n].val[1] <= y2) ret += tree[n].dat;
	ret += query(tree[n].l, x1, y1, x2, y2);
	ret += query(tree[n].r, x1, y1, x2, y2);
	return ret;
}
int main() {
	register int last_ans, op;$();
	for(;;) {
		op = $();
		if (op == 1) {
			register int x1 = $(), y1 = $(), v = $();
			//x1 ^= last_ans;y1 ^= last_ans;v ^= last_ans;
			tree[++cnt] = node(x1, y1, v);
			if (!(cnt % 10000))rebuild();
			else insert(cnt);
		} else if (op == 2) {
			register int x1 = $(), y1 = $(), x2 = $(), y2 = $();
			//x1 ^= last_ans;y1 ^= last_ans;
			//x2 ^= last_ans;y2 ^= last_ans;
			printf("%d\n", last_ans = query(root, x1, y1, x2, y2));
		} else return 0;
	}
	return 0;
}
