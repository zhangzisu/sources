#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
#define MAXN 300010
#define MAXM 10000010
const int INF = 0x3f3f3f3f;
std::multiset<int> pos[MAXN];
int n, k, q, m, root, all, tot, cnt;
int ans[MAXN], id[MAXM], L[MAXM], R[MAXM], min[MAXM];
struct operation {
	int op, x, t, k;
	inline bool friend operator<(const operation &a, const operation &b) {
		return a.t == b.t ? a.op > b.op : a.t < b.t;
	}
} w[MAXM];
struct exqueue {
	std::priority_queue<int> Q1, Q2;
	inline int size() { return Q1.size() - Q2.size(); }
	inline void push(int x) { Q1.push(-x); }
	inline void erase(int x) { Q2.push(-x); }
	inline int top() {
		while (Q2.size() && Q1.top() == Q2.top()) Q1.pop(), Q2.pop();
		return -Q1.top();
	}
} Q[MAXN];
void modify(int &n, int l, int r, int p, int u, int v) {
	if (!n) n = ++tot;
	if (l == r) {
		if (!id[n]) id[n] = ++cnt;
		exqueue &q = Q[id[n]];
		if (~u) q.push(u);
		if (~v) q.erase(v);
		min[n] = q.size() ? q.top() : INF;
		return;
	}
	int mid = (l + r) >> 1;
	p <= mid ? modify(L[n], l, mid, p, u, v) : modify(R[n], mid + 1, r, p, u, v);
	min[n] = std::min(min[L[n]], min[R[n]]);
}
int query(int p) {
	int l = 0, r = INF, x = root, ans = INF;
	while (l != r) {
		int mid = (l + r) >> 1;
		int tmp = std::min(ans, min[R[x]]);
		if (p <= mid && tmp + mid >= 2 * p)
			ans = tmp, r = mid, x = L[x];
		else
			l = mid + 1, x = R[x];
	}
	return l - p;
}
int main() {
	scanf("%d%d%d", &n, &k, &q);
	min[0] = INF;
	for (int i = 1; i <= k; i++) {
		pos[i].insert(-INF);
		pos[i].insert(INF);
		modify(root, 0, INF, INF, -INF, -1);
	}
	for (int i = 1, x, t, a, b; i <= n; i++) {
		scanf("%d%d%d%d", &x, &t, &a, &b);
		w[++m] = (operation){1, x, a, t};
		w[++m] = (operation){-1, x, b, t};
	}
	for (int i = 1, l, y; i <= q; i++) {
		scanf("%d%d", &l, &y);
		w[++m] = (operation){0, l, y, i};
	}
	std::sort(w + 1, w + m + 1);
	for (int i = 1; i <= m; i++) {
		operation &p = w[i];
		if (p.op) {
			if (p.op > 0) {
				std::multiset<int> &s = pos[p.k];
				std::multiset<int>::iterator r = s.upper_bound(p.x), l = r--;
				modify(root, 0, INF, *l, p.x, *r);
				modify(root, 0, INF, p.x, *r, -1);
				if (s.size() == 2) all++;
				s.insert(p.x);
			} else {
				std::multiset<int> &s = pos[p.k];
				s.erase(s.find(p.x));
				if (s.size() == 2) all--;
				std::multiset<int>::iterator r = s.upper_bound(p.x), l = r--;
				modify(root, 0, INF, *l, *r, p.x);
				modify(root, 0, INF, p.x, -1, *r);
			}
		} else {
			ans[p.k] = (all == k) ? query(p.x) : -1;
		}
	}
	for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
	return 0;
}