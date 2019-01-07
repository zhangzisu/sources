#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 250010
#define BLOCK 500
#define MOD 1000000007
#define INV 500000004
int t, ans[MAXN], nsa[MAXN], frc[MAXN], inv[MAXN];
inline int fuck(register int x, register int p) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
inline int C(int n, int m) {
	return n >= m ? 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD : 0;
}
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
struct query_t {
	int k, w, id;
	inline int friend operator<(const query_t &a, const query_t &b) {
		return a.k / BLOCK == b.k / BLOCK ? a.w < b.w : a.k < b.k;
	}
} q[MAXN];
inline void increaseK(int &k, int &w, int &now) {
	up(now, C(w, k + 1));
	k++;
}
inline void decreaseK(int &k, int &w, int &now) {
	up(now, MOD - C(w, k));
	k--;
}
inline void increaseW(int &k, int &w, int &now) {
	now = 2LL * now % MOD;
	up(now, MOD - C(w, k));
	w++;
}
inline void decreaseW(int &k, int &w, int &now) {
	up(now, C(w - 1, k));
	now = 1LL * now * INV % MOD;
	w--;
}
int main() {
	frc[0] = 1;
	for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
	inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
	for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;

	scanf("%d%*d", &t);
	for (int i = 1; i <= t; i++) {
		int n, m;
		scanf("%d%d", &n, &m);
		nsa[i] = fuck(C(n + m, n), MOD - 2);
		if (n >= m) {
			ans[i] = 1LL * (n - m) * C(n + m, m) % MOD;
			q[i].k = m - 1;
		} else {
			q[i].k = n - 1;
		}
		q[i].w = n + m;
		q[i].id = i;
	}
	std::sort(q + 1, q + t + 1);
	for (int i = 1, k = 0, w = 1, now = 1; i <= t; i++) {
		query_t &t = q[i];
		while (w < t.w) increaseW(k, w, now);
		while (k > t.k) decreaseK(k, w, now);
		while (k < t.k) increaseK(k, w, now);
		while (w > t.w) decreaseW(k, w, now);
		up(ans[t.id], now);
	}
	for (int i = 1; i <= t; i++) printf("%lld\n", 1LL * ans[i] * nsa[i] % MOD);
	return 0;
}