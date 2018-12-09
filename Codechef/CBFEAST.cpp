#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 20000010
const int INF = 0x3F3F3F3F;
struct seg {
	int cnt, root;
	struct node {
		int a, b, c, d;
		int l, r;
		inline node() {
			a = b = 0;
			c = d = -INF;
		}
	} val[MAXN];
	inline seg() {
		cnt = root = 0;
		memset(val, 0, sizeof(val));
	}
	inline void ensure(int &n) {
		if (!n) n = ++cnt;
	}
	inline void pushdown(int k) {
		node &K = val[k];
		ensure(K.l);
		node &KL = val[K.l];
		KL.c = std::max(KL.c, K.c + KL.a);
		KL.d = std::max(K.d, std::max(KL.d, KL.b + K.c));
		KL.a = std::max(-INF, K.a + KL.a);
		KL.b = std::max(KL.b + K.a, K.b);
		ensure(K.r);
		node &KR = val[K.r];
		KR.c = std::max(KR.c, K.c + KR.a);
		KR.d = std::max(K.d, std::max(KR.d, KR.b + K.c));
		KR.a = std::max(-INF, K.a + KR.a);
		KR.b = std::max(KR.b + K.a, K.b);
		K.a = K.c = 0;
		K.b = K.d = -INF;
	}
	void modify(int &k, int l, int r, int x, int y, int a, int b) {
		ensure(k);
		if (l >= x && r <= y) {
			val[k].a = std::max(-INF, val[k].a + a);
			val[k].b = std::max(val[k].b + a, b);
			val[k].c = std::max(val[k].a, val[k].c);
			val[k].d = std::max(val[k].b, val[k].d);
			return;
		}
		int mid = (0LL + l + r) >> 1;
		pushdown(k);
		if (x <= mid) modify(val[k].l, l, mid, x, y, a, b);
		if (y > mid) modify(val[k].r, mid + 1, r, x, y, a, b);
	}
	inline int query_mx(int k, int l, int r, int x) {
		while (l < r) {
			if (!k) return 0;
			int mid = (0LL + l + r) >> 1;
			pushdown(k);
			x <= mid ? (k = val[k].l, r = mid) : (k = val[k].r, l = mid + 1);
		}
		return std::max(val[k].c, val[k].d);
	}
} L, R, LL, RR;
int q, k, d, u;
int main() {
	scanf("%d%d", &q, &k);
	d = 1, u = 2000000000;
	for (int opt, c, v, lans = 0; q; q--) {
		scanf("%d%d", &opt, &c);
		c ^= lans;
		if (opt == 1) {
			scanf("%d", &v);
			L.modify(L.root, d, u, std::max(d, c - k), std::min(u, c + k), v, 0);
			LL.modify(LL.root, d, u, std::max(d, c - k), std::min(u, c + k), v, -INF);
		} else if (opt == 2) {
			scanf("%d", &v);
			R.modify(R.root, d, u, std::max(d, c - k), std::min(u, c + k), v, 0);
			RR.modify(RR.root, d, u, std::max(d, c - k), std::min(u, c + k), v, -INF);
		} else {
			printf("%d\n", lans = std::max(
					   std::max(L.query_mx(L.root, d, u, c), R.query_mx(R.root, d, u, c)),
					   LL.query_mx(LL.root, d, u, c) + RR.query_mx(RR.root, d, u, c)));
		}
	}
	return 0;
}