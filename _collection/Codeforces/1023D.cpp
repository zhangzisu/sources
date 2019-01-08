#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 200010
int n, m, q, a[MAXN], max[MAXN << 2];
std::vector<int> pos[MAXN];
inline void pushDown(int n) {
	max[n << 1] = std::max(max[n << 1], max[n]);
	max[n << 1 | 1] = std::max(max[n << 1 | 1], max[n]);
}
inline void setMax(int n, int l, int r, int L, int R, int v) {
	if (l == L && r == R) return max[n] = std::max(max[n], v), void();
	int mid = (l + r) >> 1;
	pushDown(n);
	if (R <= mid) return setMax(n << 1, l, mid, L, R, v);
	if (L > mid) return setMax(n << 1 | 1, mid + 1, r, L, R, v);
	setMax(n << 1, l, mid, L, mid, v);
	setMax(n << 1 | 1, mid + 1, r, mid + 1, R, v);
}
inline int getVal(int n, int l, int r, int p) {
	if (l == r) return max[n];
	int mid = (l + r) >> 1;
	pushDown(n);
	return p <= mid ? getVal(n << 1, l, mid, p) : getVal(n << 1 | 1, mid + 1, r, p);
}
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		m = std::max(m, a[i]);
		pos[a[i]].push_back(i);
	}
	if (m > q) return puts("NO"), 0;
	if (m != q && !pos[0].size()) return puts("NO"), 0;
	for (int i = 1, size; i <= m; i++) {
		if ((size = (int)pos[i].size()) >= 2)
			setMax(1, 1, n, pos[i][0], pos[i][size - 1], i);
	}
	for (int i = 1; i <= n; i++) {
		int val = std::max(getVal(1, 1, n, i), 1);
		if (a[i]) {
			if (a[i] < val) return puts("NO"), 0;
		} else {
			a[i] = val;
		}
	}
	if (m != q) a[pos[0][0]] = q;
	puts("YES");
	for (int i = 1; i <= n; i++) printf("%d ", a[i]);
	puts("");
	return 0;
}