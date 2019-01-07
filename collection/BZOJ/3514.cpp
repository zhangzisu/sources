#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#define MAXN 400010
#define MAXM 8000010
inline int $() {
	register int x = 0;
	register char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
const int INF = (~0U) >> 1;
struct splay_t {
	splay_t *f, *l, *r;
	int val, min, rev;
} pool[MAXN];
inline bool isRoot(splay_t *x) {
	return !(x->f && (x->f->l == x || x->f->r == x));
}
inline void pushUp(splay_t *x) {
	x->min = x->val;
	if (x->l) x->min = std::min(x->min, x->l->min);
	if (x->r) x->min = std::min(x->min, x->r->min);
}
inline void pushDown(splay_t *x) {
	if (x->rev) {
		splay_t *t = x->l;
		x->l = x->r;
		x->r = t;
		if (x->l) x->l->rev ^= 1;
		if (x->r) x->r->rev ^= 1;
		x->rev = 0;
	}
}
inline void left_rotate(splay_t *x) {
	splay_t *f = x->f, *p = f->f;
	if (f->r = x->l) f->r->f = f;
	x->f = p;
	if (p && p->l == f) p->l = x;
	if (p && p->r == f) p->r = x;
	(x->l = f)->f = x;
	pushUp(f);
	pushUp(x);
}
inline void right_rotate(splay_t *x) {
	splay_t *f = x->f, *p = f->f;
	if (f->l = x->r) f->l->f = f;
	x->f = p;
	if (p && p->l == f) p->l = x;
	if (p && p->r == f) p->r = x;
	(x->r = f)->f = x;
	pushUp(f);
	pushUp(x);
}
std::stack<splay_t *> stack;
inline void splay(splay_t *x) {
	stack.push(x);
	for (splay_t *p = x; !isRoot(p); p = p->f) stack.push(p->f);
	for (; stack.size(); stack.pop()) pushDown(stack.top());
	while (!isRoot(x)) {
		splay_t *f = x->f, *p = f->f;
		if (isRoot(f)) {
			if (f->l == x) {
				right_rotate(x);
			} else {
				left_rotate(x);
			}
		} else {
			if (p->l == f) {
				if (f->l == x) {
					right_rotate(f);
					right_rotate(x);
				} else {
					left_rotate(x);
					right_rotate(x);
				}
			} else {
				if (f->l == x) {
					right_rotate(x);
					left_rotate(x);
				} else {
					left_rotate(f);
					left_rotate(x);
				}
			}
		}
	}
}
inline void access(splay_t *x) {
	for (splay_t *t = NULL; x; x = x->f) {
		splay(x);
		x->r = t;
		t = x;
		pushUp(x);
	}
}
inline void setRoot(splay_t *x) {
	access(x);
	splay(x);
	x->rev = 1;
}
inline splay_t *getRoot(splay_t *x) {
	access(x);
	splay(x);
	while (x->l) x = x->l;
	return x;
}
inline void link(splay_t *x, splay_t *y) {
	setRoot(x);
	x->f = y;
	pushUp(x);
	pushUp(y);
}
inline void cut(splay_t *x, splay_t *y) {
	setRoot(x);
	access(y);
	splay(y);
	y->l = x->f = NULL;
	pushUp(x);
	pushUp(y);
}
int n, m, k, t, u[MAXN], v[MAXN], pre[MAXN];
int root[MAXN], L[MAXM], R[MAXM], sum[MAXM], all;
void add(int &n, int m, int l, int r, int p) {
	n = ++all;
	L[n] = L[m], R[n] = R[m], sum[n] = sum[m] + 1;
	if (l == r) return;
	int mid = (l + r) >> 1;
	p <= mid ? add(L[n], L[m], l, mid, p) : add(R[n], R[m], mid + 1, r, p);
}
int qry(int n, int m, int l, int r, int _l, int _r) {
	if (l == _l && r == _r) return sum[n] - sum[m];
	int mid = (l + r) >> 1;
	if (_r <= mid) return qry(L[n], L[m], l, mid, _l, _r);
	if (_l > mid) return qry(R[n], R[m], mid + 1, r, _l, _r);
	return qry(L[n], L[m], l, mid, _l, mid) + qry(R[n], R[m], mid + 1, r, mid + 1, _r);
}
int main() {
	n = $(), m = $(), k = $(), t = $();
	for (int i = 1; i <= n + m; i++) pool[i].val = pool[i].min = INF;
	for (int i = 1; i <= m; i++) {
		u[i] = $(), v[i] = $();
		if (u[i] == v[i]) {
			pre[i] = i;
			add(root[i], root[i - 1], 0, m, pre[i]);
			continue;
		}
		splay_t *U = &pool[u[i]];
		splay_t *V = &pool[v[i]];
		splay_t *E = &pool[n + i];
		if (getRoot(U) == getRoot(V)) {
			setRoot(U);
			access(V);
			splay(V);
			int val = V->l->min;
			pre[i] = val;
			cut(&pool[u[val]], &pool[n + val]);
			cut(&pool[n + val], &pool[v[val]]);
		}
		pool[n + i].min = pool[n + i].val = i;
		link(U, E);
		link(E, V);
		add(root[i], root[i - 1], 0, m, pre[i]);
	}
	for (int l, r, lans = 0; k; k--) {
		l = $(), r = $();
		l ^= t * lans;
		r ^= t * lans;
		printf("%d\n", lans = (n - qry(root[r], root[l - 1], 0, m, 0, l - 1)));
	}
	return 0;
}