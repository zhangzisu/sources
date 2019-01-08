#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define SQRT 320
int n, m, a[MAXN], c[MAXN], ans[MAXN];
struct query_t {
	int l, r, x, opt, id;
	inline int friend operator<(const query_t &a, const query_t &b) {
		return a.l / SQRT == b.l / SQRT ? a.r < b.r : a.l < b.l;
	}
} q[MAXN];
std::bitset<MAXN> A, B;
inline void add(int x) {
	if (!c[x]++) {
		A[x] = B[MAXN - x] = 1;
	}
}
inline void del(int x) {
	if (!--c[x]) {
		A[x] = B[MAXN - x] = 0;
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= m; i++) scanf("%d%d%d%d", &q[i].opt, &q[i].l, &q[i].r, &q[i].x), q[i].id = i;
	std::sort(q + 1, q + m + 1);
	int l = 1, r = 0;
	for (int _ = 1; _ <= m; _++) {
		const query_t &Q = q[_];
		int &Ans = ans[Q.id];
		while (l > Q.l) add(a[--l]);
		while (r < Q.r) add(a[++r]);
		while (l < Q.l) del(a[l++]);
		while (r > Q.r) del(a[r--]);
		if (Q.opt == 1) {
			Ans = (A & (A << Q.x)).any();
		} else if (Q.opt == 2) {
			Ans = (A & (B >> (MAXN - Q.x))).any();
		} else {
			for (int x = 1; x * x <= Q.x; x++) {
				if (Q.x % x) continue;
				if ((Ans = (A[x] && A[Q.x / x]))) break;
			}
		}
	}
	for (int i = 1; i <= n; i++) puts(ans[i] ? "yuno" : "yumi");
	return 0;
}