const int MAXN = 500100;
const lnt INF = 0X3f3f3f3f3f3f3f3fll;
int n, cnt = 0;
struct node {
	lnt a, b, c, d;
	int l, r;
} val[MAXN << 2];
inline void ensure(int &n) {
	if (!n) n = ++cnt;
}
inline void pushdown(int k) {
	node &K = val[k];
	ensure(K.l);
    node &KL = val[K.l];
	KL.c = std::max(KL.c, val[k].c + KL.a);
	KL.d = std::max(val[k].d, std::max(KL.d, KL.b + val[k].c));
	KL.a = std::max(-INF, val[k].a + KL.a);
	KL.b = std::max(KL.b + val[k].a, val[k].b);
	ensure(K.r);
    node &KR = val[K.r];
	KR.c = std::max(KR.c, val[k].c + KR.a);
	KR.d = std::max(val[k].d, std::max(KR.d, KR.b + val[k].c));
	KR.a = std::max(-INF, val[k].a + KR.a);
	KR.b = std::max(KR.b + val[k].a, val[k].b);
	val[k].a = val[k].b = val[k].c = val[k].d = 0;
}
void modify(int &k, int l, int r, int x, int y, lnt a, lnt b) {
	ensure(k);
	if (l >= x && r <= y) {
		val[k].a = std::max(-INF, val[k].a + a);
		val[k].b = std::max(val[k].b + a, b);
		val[k].c = std::max(val[k].a, val[k].c);
		val[k].d = std::max(val[k].b, val[k].d);
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(k);
	if (x <= mid) modify(val[k].l, l, mid, x, y, a, b);
	if (y > mid) modify(val[k].r, mid + 1, r, x, y, a, b);
}
inline lnt query_mx(int x) {
	register int l = 1, r = n, mid, k = 1;
	while (l < r) {
		if (!k) return 0;
		mid = (l + r) >> 1;
		pushdown(k);
		x <= mid ? (k = val[k].l, r = mid) : (k = val[k].r, l = mid + 1);
	}
	return std::max(val[k].c, val[k].d);
}

int main() {
	n = read();
	int Q = read();
	build(1, 1, n);
	register int opt, x, y, val;
	while (Q--) {
		opt = read();
		x = read();
		switch (opt) {
			case 1:
				y = read(), val = read();
				modify(1, 1, n, x, y, val, 0);
				break;
			case 2:
				y = read(), val = read();
				modify(1, 1, n, x, y, -val, 0);
				break;
			case 3:
				y = read(), val = read();
				modify(1, 1, n, x, y, -INF, val);
				break;
			case 4:
				print(query(x));
				puts("");
				break;
			case 5:
				print(query_mx(x));
				puts("");
				break;
		}
	}
	return 0;
}