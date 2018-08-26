#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, m, a[MAXN], b[MAXN], c[MAXN];
long long tmp;
int lc0[MAXN], lc1[MAXN], rc0[MAXN], rc1[MAXN], ls[MAXN], rs[MAXN];
void solve(int l, int r) {
	if (l == r) return tmp += c[l], void();
	int mid = (l + r) >> 1;
	solve(l, mid);
	solve(mid + 1, r);
	int cl0 = 0, cl1 = 0, cr0 = 0, cr1 = 0;
	for (int i = mid; i >= l; i--) {
		ls[mid - i + 1] = ls[mid - i] + c[i];
		if ((mid - i + 1) & 1) {
			lc1[++cl1] = ls[mid - i + 1] - (mid - i + 1) / 2;
		} else {
			lc0[++cl0] = ls[mid - i + 1] - (mid - i + 1) / 2;
		}
	}
	for (int i = mid + 1; i <= r; i++) {
		rs[i - mid] = rs[i - mid - 1] + c[i];
		if ((i - mid) & 1) {
			rc1[++cr1] = rs[i - mid] - (i - mid) / 2;
		} else {
			rc0[++cr0] = rs[i - mid] - (i - mid) / 2;
		}
	}
	std::sort(lc0 + 1, lc0 + cl0 + 1);
	std::sort(rc0 + 1, rc0 + cr0 + 1);
	std::sort(lc1 + 1, lc1 + cl1 + 1);
	std::sort(rc1 + 1, rc1 + cr1 + 1);
	int cur = cr0;
	for (int i = 1; i <= cl0; i++) {
		while (cur && lc0[i] + rc0[cur] >= 1) cur--;
		tmp += cr0 - cur;
	}
	cur = cr0;
	for (int i = 1; i <= cl1; i++) {
		while (cur && lc1[i] + rc0[cur] >= 1) cur--;
		tmp += cr0 - cur;
	}
	cur = cr1;
	for (int i = 1; i <= cl0; i++) {
		while (cur && lc0[i] + rc1[cur] >= 1) cur--;
		tmp += cr1 - cur;
	}
	cur = cr1;
	for (int i = 1; i <= cl1; i++) {
		while (cur && lc1[i] + rc1[cur] >= 2) cur--;
		tmp += cr1 - cur;
	}
}
inline bool judge(int v) {
	for (int i = 1; i <= n; i++) c[i] = a[i] <= v;
	// fprintf(stderr, "JUDGE %d\n", v);
	// for (int i = 1; i <= n; i++) fprintf(stderr, "%d ", c[i]);
	// fprintf(stderr, "\n");
	tmp = 0;
	solve(1, n);
	// fprintf(stderr, "RETURN %lld\n", tmp);
	return tmp >= 1LL * n * (n + 1) / 4 + 1;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	memcpy(b, a, sizeof(b));
	std::sort(b + 1, b + n + 1);
	int l = 1, r = n, ans = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (judge(b[mid]))
			ans = mid, r = mid - 1;
		else
			l = mid + 1;
	}
	printf("%d\n", b[ans]);
	return 0;
}