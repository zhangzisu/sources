#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
#define MOD 1000000007
inline int fuck(int x, int p) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
const int inv2 = fuck(2, MOD - 2);
int n, a[MAXN], b[MAXN], c[MAXN], d[MAXN], BIT[MAXN], all, ans;
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int y) {
	for (; x <= n; x += lowbit(x)) up(BIT[x], y);
}
inline int qry(int x) {
	register int y = 0;
	for (; x; x -= lowbit(x)) up(y, BIT[x]);
	return y;
}
int count[MAXN];
inline void add(int x) {
	for (; x <= n; x += lowbit(x)) count[x]++;
}
inline int get(int x) {
	register int y = 0;
	for (; x; x -= lowbit(x)) y += count[x];
	return y;
}
int l[MAXN], r[MAXN];
int main() {
	for (int i = scanf("%d", &n); i <= n; i++) scanf("%d", &a[i]), b[a[i]]++;
	for (int i = n; i >= 1; i--) b[i] += b[i + 1];
	all = 1;
	for (int i = 1; i <= n; i++) {
		if ((b[i] -= n - i) <= 0) return puts("0"), 0;
		all = 1LL * all * b[i] % MOD;
	}
	for (int i = 1; i <= n; i++) c[i] = 1LL * (b[i] - 1) * fuck(b[i], MOD - 2) % MOD;
	l[0] = 0;
	for (int i = 1; i <= n; i++) l[i] = c[i] ? l[i - 1] : i;
	r[n + 1] = n + 1;
	for (int i = n; i >= 1; i--) r[i] = c[i] ? r[i + 1] : i;
	d[0] = 1;
	for (int i = 1; i <= n; i++) d[i] = d[i - 1] ? 1LL * d[i - 1] * c[i] % MOD : c[i];
	for (int i = n; i >= 1; i--) {
		int tmp = (qry(r[a[i]] - 1) - qry(a[i] - 1) + MOD) % MOD;
		tmp = 1LL * tmp * all % MOD;
		tmp = 1LL * tmp * inv2 % MOD;
		tmp = 1LL * tmp * fuck(d[a[i]], MOD - 2) % MOD;
		up(ans, tmp);
		add(a[i], d[a[i]]);
	}
	memset(BIT, 0, sizeof(BIT));
	for (int i = 1; i <= n; i++) {
		int tmp = (qry(r[a[i]] - 1) - qry(a[i]) + MOD) % MOD;
		tmp = 1LL * tmp * all % MOD;
		tmp = 1LL * tmp * inv2 % MOD;
		tmp = 1LL * tmp * fuck(d[a[i]], MOD - 2) % MOD;
		tmp = (1LL * (get(n) - get(a[i])) * all % MOD - tmp + MOD) % MOD;
		up(ans, tmp);
		add(a[i], d[a[i]]);
		add(a[i]);
	}
	printf("%d\n", ans);
	return 0;
}