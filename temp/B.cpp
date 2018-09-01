#include <algorithm>
#include <cmath>
#include <iostream>
#define MAXN 100005
using namespace std;

struct node_t {
	int left, right, mid;
	int lx, rx, mx;
	int dist() { return right - left + 1; }
} node[MAXN << 2];

int val[MAXN], a, b;

void pushUp(int root) {
	int lChild = root * 2;
	int rChild = lChild + 1;
	node[root].lx = node[lChild].lx + ((node[lChild].lx == node[lChild].dist() && val[node[rChild].left] > val[node[lChild].right]) ? node[rChild].lx : 0);
	node[root].rx = node[rChild].rx + ((node[rChild].rx == node[rChild].dist() && val[node[rChild].left] > val[node[lChild].right]) ? node[lChild].rx : 0);
	node[root].mx = max(max(node[lChild].mx, node[rChild].mx), val[node[rChild].left] > val[node[lChild].right] ? (node[lChild].rx + node[rChild].lx) : 0);
}

void build(int root, int l, int r) {
	node[root].left = l;
	node[root].right = r;
	node[root].mid = (l + r) / 2;
	if (l == r) {
		node[root].lx = node[root].rx = node[root].mx = 1;
		return;
	}

	build(root * 2, l, (l + r) / 2);
	build(root * 2 + 1, (l + r) / 2 + 1, r);

	pushUp(root);
}

void update(int root, int pos) {
	if (node[root].left == node[root].right) {
		node[root].lx = node[root].rx = node[root].mx = 1;
		return;
	}

	if (pos <= node[root].mid)
		update(root * 2, pos);
	else
		update(root * 2 + 1, pos);

	pushUp(root);
}

int query(int root, int l, int r) {
	if (node[root].left == l && node[root].right == r)
		return node[root].mx;

	if (r <= node[root].mid)
		return query(root * 2, l, r);
	else if (l > node[root].mid)
		return query(root * 2 + 1, l, r);
	else {
		int lSum = query(root * 2, l, node[root].mid);
		int rSum = query(root * 2 + 1, node[root].mid + 1, r);

		int mSum = 0;
		if (val[node[root * 2 + 1].left] > val[node[root * 2].right])
			mSum = min(node[root * 2].rx, node[root].mid - l + 1) + min(node[root * 2 + 1].lx, r - node[root].mid);

		return max(max(lSum, rSum), mSum);
	}
}
int n, m;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
	build(1, 1, n);
	printf("%d\n", query(1, 1, n));
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &a, &b);
		val[a] = b;
		update(1, a);
		printf("%d\n", query(1, 1, n));
	}
	return 0;
}