#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 500010
#define MAXM 10000010
int n, m, ty, root[MAXN];
int sum[MAXN << 2], tag[MAXN << 2];
inline int pushDown(int n, int l, int r) {
	int mid = (l + r) >> 1;
	if (tag[n] != -1) {
		tag[n << 1] = tag[n];
		sum[n << 1] = (mid - l + 1) * tag[n];
		tag[n << 1 | 1] = tag[n];
		sum[n << 1 | 1] = (r - mid) * tag[n];
		tag[n] = -1;
	}
	return mid;
}
void set(int n, int l, int r, int L, int R, int v) {
	if (l == L && r == R) {
		tag[n] = v;
		sum[n] = (r - l + 1) * v;
		return;
	}
	int mid = pushDown(n, l, r);
	if (R <= mid) {
		set(n << 1, l, mid, L, R, v);
	} else if (L > mid) {
		set(n << 1 | 1, mid + 1, r, L, R, v);
	} else {
		set(n << 1, l, mid, L, mid, v);
		set(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	}
	sum[n] = sum[n << 1] + sum[n << 1 | 1];
}
int get(int n, int l, int r, int L, int R) {
	if (l == L && r == R) return sum[n];
	int mid = pushDown(n, l, r);
	if (R <= mid) {
		return get(n << 1, l, mid, L, R);
	} else if (L > mid) {
		return get(n << 1 | 1, mid + 1, r, L, R);
	} else {
		return get(n << 1, l, mid, L, mid) + get(n << 1 | 1, mid + 1, r, mid + 1, R);
	}
}
int val[MAXM], L[MAXM], R[MAXM], cnt = 0;
inline void fuckUp(int n){
	if(val[n] != -1){
		val[L[n] = ++cnt] = val[n];
		val[R[n] = ++cnt] = val[n];
		val[n] = -1;
	}
}
int update(int n, int l, int r, int _l, int _r, int v) {
	int cur = ++cnt;
	val[cur] = val[n], L[cur] = L[n], R[cur] = R[n];
	if (l == _l && r == _r) {
		val[cur] = v;
		return cur;
	}
	fuckUp(n);
	int mid = (l + r) >> 1;
	if (_r <= mid) {
		L[cur] = update(L[n], l, mid, _l, mid, v);
	} else if (_l > mid) {
		R[cur] = update(R[n], mid + 1, r, _l, _r, v);
	} else {
		L[cur] = update(L[n], l, mid, _l, mid, v);
		R[cur] = update(R[n], mid + 1, r, mid + 1, _r, v);
	}
	return cur;
}
int query(int n, int l, int r, int p) {
	if (val[n] != -1) return val[n];
	int mid = (l + r) >> 1;
	return p <= mid ? query(L[n], l, mid, p) : query(R[n], mid + 1, r, p);
}
int dat[MAXN], q;
int main() {
	freopen("ex_C3.in", "r", stdin);
	scanf("%d%d%d", &n, &m, &ty);
	memset(tag, -1, sizeof(tag));
	memset(val, -1, sizeof(val));
	root[0] = update(root[0], 1, n, 1, n, 0);
	for (int i = 1, op, l, r, x, lans = 0; i <= m; i++) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d%d", &l, &r);
			l = (l + 1LL * lans * ty) % n + 1;
			r = (r + 1LL * lans * ty) % n + 1;
			if (l > r) std::swap(l, r);
			printf("%d\n", lans = get(1, 1, n, l, r));
		} else if (op == 2) {
			scanf("%d", &l);
			l = (l + 1LL * lans * ty) % n + 1;
			int p = query(root[q], 1, n, l);
			if (!p) continue;
			int v = dat[p - 1];
			set(1, 1, n, l, l, v);
			root[q] = update(root[q], 1, n, l, l, p - 1);
		} else {
			scanf("%d%d%d", &l, &r, &x);
			dat[++q] = x;
			l = (l + 1LL * lans * ty) % n + 1;
			r = (r + 1LL * lans * ty) % n + 1;
			if (l > r) std::swap(l, r);
			set(1, 1, n, l, r, x);
			root[q] = update(root[q - 1], 1, n, l, r, q);
		}
	}
	return 0;
}