#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define MAXN 100010
int n, a[MAXN];
int min[MAXN << 2];
std::set<int> S[MAXN << 2];
inline void pushDown(int n) {
	min[n << 1] = std::min(min[n << 1], min[n]);
	min[n << 1 | 1] = std::min(min[n << 1 | 1], min[n]);
}
void modify(int n, int l, int r, int L, int R, int v) {
	if (l == L && r == R) return min[n] = v, void();
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
void add(int n, int l, int r, int p, int v) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	pushDown(mid);
	p <= mid ? add(n << 1, l, mid, p, v) : add(n << 1 | 1, mid + 1, r, p, v);
}
int main() {
	//
	return 0;
}