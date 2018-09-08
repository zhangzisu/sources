#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 100010
typedef long long lnt;
int t, n, q, a[MAXN], cnt, L[MAXN], R[MAXN];
lnt sum[MAXN << 2], tag[MAXN << 2];
int add(int n, int l, int r, int _l, int _r, int v) {
	int cur = ++cnt;
	L[cur] = L[n], R[cur] = R[n], tag[cur] = tag[n], sum[cur] = sum[n];
	if (l == _l && r == _r) {
		tag[cur] += v;
		sum[cur] += 1LL * (r - l + 1) * v;
		return;
	}
	int mid = (l + r) >> 1;
	if (R <= mid) {
		L[cur] = add(L[n], l, mid, _l, _r, v);
	} else if (L > mid) {
		R[cur] = add(R[n], mid + 1, r, _l, _r, v);
	} else {
		L[cur] = add(L[n], l, mid, _l, mid, v);
		R[cur] = add(R[n], mid + 1, r, mid + 1, r, v);
	}
	sum[cur] = sum[L[cur]] + sum[R[cur]];
	return cur;
}
lnt query(int n, int m, int l, int r, int _l, int _r) {
	if (l == _l && r == _r) return sum[n] - sum[m];
	int mid = (l + r) >> 1;
	lnt tmp = tag[n] * (_r - _l + 1);
	if (R <= mid) return query(L[n], L[m], l, mid, _l, _r) + tmp;
	if (L > mid) return query(R[n], R[m], mid + 1, r, _l, _r) + tmp;
	return query(L[n], L[m], l, mid, _l, mid) + query(R[n], R[m], mid + 1, r, mid + 1, _r) + tmp;
}
int root[MAXN];
std::vector<int> places;
int isQAQ(int x) {
	return ((int)sqrt(x)) * ((int)sqrt(x)) == x;
}
int main() {
	for (scanf("%d", &t); t; t--) {
		scanf("%d%d", &n, &q);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++) {
			int val = a[i];
			for (int j = (int)places.size() - 1; ~j; j--) {
				if ((a[places[j]] & val) == val)
					places.pop_back();
				else
					val &= a[places[j]];
			}
			val = a[i];
			places.push_back(i);
			root[i] = root[i - 1];
			for (int j = (int)places.size() - 1; ~j; j--) {
				val &= a[places[j]];
				if (isQAQ(val)) root[i] = add(root[i], 1, n, places[j - 1] + 1, places[j]);
			}
			for (int l, r; q; q--) {
				scanf("%d%d", &l, &r);
				printf("%lld\n", query(root[r], root[l - 1], 1, n, l, r));
			}
		}
	}
	return 0;
}