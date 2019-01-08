#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#define MAXN 300010
#define MAXM 5000100
int n, m, a[MAXN], ans[MAXN];
int min[MAXN << 2], tag[MAXN << 2];
inline void up(int &x, int y) {
	if (y < x) x = y;
}
inline void pushDown(int n) {
	up(min[n << 1], tag[n]);
	up(min[n << 1 | 1], tag[n]);
	up(tag[n << 1], tag[n]);
	up(tag[n << 1 | 1], tag[n]);
}
void modify(int n, int l, int r, int L, int R, int v) {
	if (l == L && r == R) return up(min[n], v), up(tag[n], v), void();
	int mid = (l + r) >> 1;
	pushDown(n);
	if (R <= mid)
		modify(n << 1, l, mid, L, R, v);
	else if (L > mid)
		modify(n << 1 | 1, mid + 1, r, L, R, v);
	else
		modify(n << 1, l, mid, L, mid, v), modify(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	min[n] = std::min(min[n << 1], min[n << 1 | 1]);
}
int query(int n, int l, int r, int p) {
	if (l == r) return min[n];
	assert(l <= r);
	int mid = (l + r) >> 1;
	pushDown(n);
	return p <= mid ? query(n << 1, l, mid, p) : query(n << 1 | 1, mid + 1, r, p);
}
int root[MAXN], L[MAXM], R[MAXM], max[MAXM], all;
void insert(int &n, int m, int l, int r, int p, int v) {
	n = ++all;
	L[n] = L[m];
	R[n] = R[m];
	max[n] = max[m];
	if (l == r) return max[n] = std::max(max[n], v), void();
	int mid = (l + r) >> 1;
	p <= mid ? insert(L[n], L[m], l, mid, p, v) : insert(R[n], R[m], mid + 1, r, p, v);
	max[n] = std::max(max[L[n]], max[R[n]]);
}
int query(int n, int l, int r, int _l, int _r) {
	if (!n) return 0;
	if (l == _l && r == _r) return max[n];
	int mid = (l + r) >> 1;
	if (_r <= mid) return query(L[n], l, mid, _l, _r);
	if (_l > mid) return query(R[n], mid + 1, r, _l, _r);
	return std::max(query(L[n], l, mid, _l, mid), query(R[n], mid + 1, r, mid + 1, _r));
}
std::vector<std::pair<int, int>> left[MAXN];
std::vector<int> V;
int main() {
	V.push_back(-1);
	for (int i = scanf("%d", &n); i <= n; i++) scanf("%d", &a[i]), V.push_back(a[i]);
	std::sort(V.begin(), V.end());
	V.erase(std::unique(V.begin(), V.end()), V.end());
	for (int i = 1; i <= n; i++) {
		a[i] = (std::lower_bound(V.begin(), V.end(), a[i]) - V.begin());
		insert(root[i], root[i - 1], 1, n, a[i], i);
	}
	for (int l, r, i = scanf("%d", &m); i <= m; i++) scanf("%d%d", &l, &r), left[r].emplace_back(l, i);
	memset(min, 0x3F, sizeof(min));
	memset(tag, 0x3F, sizeof(tag));
	for (int i = 1; i <= n; i++) {
		int vl = a[i], vr = (int)V.size() - 1, cur = i - 1;
		for (int next; cur >= 1; cur = next - 1) {
			next = query(root[cur], 1, n, vl, vr);
			if (!next) break;
			modify(1, 1, n, 1, next, V[a[next]] - V[vl]);
			if (V[a[next]] == V[vl]) break;
			// printf("modify %d-%d %d\n", 1, next, V[a[next]] - V[vl]);
			vr = (std::lower_bound(V.begin(), V.end(), (V[vl] + V[a[next]]) / 2) - V.begin());
		}
		vl = 1, vr = a[i], cur = i - 1;
		for (int next; cur >= 1; cur = next - 1) {
			next = query(root[cur], 1, n, vl, vr);
			if (!next) break;
			modify(1, 1, n, 1, next, V[vr] - V[a[next]]);
			if (V[vr] == V[a[next]]) break;
			// printf("modify %d-%d %d\n", 1, next, V[vr] - V[a[next]]);
			vl = (std::lower_bound(V.begin(), V.end(), (V[vr] + V[a[next]] + 1) / 2) - V.begin());
		}
		// printf("done %d\n", i);
		for (auto x : left[i]) ans[x.second] = query(1, 1, n, x.first);
		// printf("%d\n", i);
	}
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
	return 0;
}