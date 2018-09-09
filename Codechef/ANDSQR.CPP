#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <list>
#define MAXN 100010
#define MAXM 5000010
typedef long long lnt;
int t, n, q, a[MAXN], cnt, L[MAXM], R[MAXM];
lnt sum[MAXM], tag[MAXM];
int add(int n, int l, int r, int _l, int _r) {
	int cur = ++cnt;
	L[cur] = L[n], R[cur] = R[n], tag[cur] = tag[n], sum[cur] = sum[n];
	if (l == _l && r == _r) {
		tag[cur]++;
		sum[cur] += r - l + 1;
		return cur;
	}
	int mid = (l + r) >> 1;
	if (_r <= mid) {
		L[cur] = add(L[n], l, mid, _l, _r);
	} else if (_l > mid) {
		R[cur] = add(R[n], mid + 1, r, _l, _r);
	} else {
		L[cur] = add(L[n], l, mid, _l, mid);
		R[cur] = add(R[n], mid + 1, r, mid + 1, _r);
	}
	sum[cur] = sum[L[cur]] + sum[R[cur]];
	return cur;
}
lnt query(int n, int m, int l, int r, int _l, int _r) {
	if (l == _l && r == _r) return sum[n] - sum[m];
	int mid = (l + r) >> 1;
	lnt tmp = tag[n] * (_r - _l + 1);
	if (_r <= mid) return query(L[n], L[m], l, mid, _l, _r) + tmp;
	if (_l > mid) return query(R[n], R[m], mid + 1, r, _l, _r) + tmp;
	return query(L[n], L[m], l, mid, _l, mid) + query(R[n], R[m], mid + 1, r, mid + 1, _r) + tmp;
}
int root[MAXN];
std::list<int> places;
int isQAQ(int x) { return ((int)sqrt(x)) * ((int)sqrt(x)) == x; }
int main() {
	for (scanf("%d", &t); t; t--) {
		memset(sum, 0, sizeof(sum));
		memset(tag, 0, sizeof(tag));
		places.clear();
		cnt = 0;
		scanf("%d%d", &n, &q);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++) {
			int val = a[i];
			for (std::list<int>::iterator it = places.begin(); it != places.end();) {
				if ((a[*it] & val) == val) {
					it = places.erase(it);
				} else {
					val &= a[*it++];
				}
			}
			val = a[i];
			places.push_front(i);
			root[i] = root[i - 1];
			for (std::list<int>::iterator it = places.begin(); it != places.end();) {
				int r = *it;
				val &= a[r];
				int l = (++it == places.end()) ? 1 : *it + 1;
				if (isQAQ(val)) {
					root[i] = add(root[i], 1, n, l, r);
					// printf("ADDED 1 to RANGE %d-%d\n", l, r);
				}
			}
		}
		for (int l, r; q; q--) {
			scanf("%d%d", &l, &r);
			printf("%lld\n", query(root[r], root[0], 1, n, l, r));
		}
	}
	return 0;
}