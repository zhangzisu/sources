#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,abm,mmx,tune=native")
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 500010
using lnt = long long;
const lnt MOD = 75161927681LL;
const lnt G = 3;
inline lnt mul(lnt x, lnt y) { return (x * y - (lnt)((long double)x / MOD * y) * MOD + MOD) % MOD; }
inline void trim(lnt &x) { x -= MOD, x += (x >> 63) & MOD; }
inline lnt fuck(lnt x, lnt y) {
	lnt z = 1;
	for (; y; y >>= 1) {
		if (y & 1) z = mul(z, x);
		x = mul(x, x);
	}
	return z;
}
lnt wns[20][MAXN], invs[20];
int revs[20][MAXN];
inline void pre() {
	for (int n = 1, kk = 0; n < MAXN; n <<= 1, kk++) {
		lnt wn = fuck(G, (MOD - 1) / n);
		wns[kk][0] = 1;
		for (int i = 1; i < (n >> 1); i++) wns[kk][i] = mul(wns[kk][i - 1], wn);
		invs[kk] = fuck(n, MOD - 2);
		for (int i = 1, j = 0; i < n - 1; i++) {
			for (int t = n; ~j & t; j ^= t) t >>= 1;
			revs[kk][i] = j;
		}
	}
}
inline void NTT(int *rev, lnt *a, int n) {
	for (int i = 1; i < n - 1; i++) {
		if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	}
	for (int k = 1, kk = 1; k < n; k <<= 1, kk++) {
		int t = k << 1;
		for (int i = 0; i < n; i += t) {
			for (int j = 0; j < k; j++) {
				lnt x = a[i + j], y = mul(wns[kk][j], a[i + j + k]);
				trim(a[i + j] = x + y);
				trim(a[i + j + k] = x - y + MOD);
			}
		}
	}
}
int m, cnt = 0;
lnt f[MAXN], g[MAXN], h[MAXN];
inline std::pair<int, int> solve(int l, int r) {
	if (l == r) {
		f[cnt++] = (m - l) % m;
		f[cnt++] = 1;
		return {cnt - 2, 2};
	}
	int mid = (l + r) >> 1;
	auto L = solve(l, mid), R = solve(mid + 1, r);
	int n = 1, nn = 0, len = L.second + R.second - 1;
	while (n < len) n <<= 1, nn++;
	memcpy(g, f + L.first, sizeof(lnt) * L.second);
	memset(g + L.second, 0, sizeof(lnt) * (n - L.second));
	memcpy(h, f + R.first, sizeof(lnt) * R.second);
	memset(h + R.second, 0, sizeof(lnt) * (n - R.second));
	NTT(revs[nn], g, n), NTT(revs[nn], h, n);
	for (int i = 0; i < n; i++) g[i] = mul(g[i], h[i]);
	NTT(revs[nn], g, n);
	std::reverse(g + 1, g + n);
	lnt inv = invs[nn];
	for (int i = 0; i < n; i++) g[i] = mul(g[i], inv) % m;
	std::memcpy(f + L.first, g, sizeof(lnt) * len);
	return {L.first, len};
}
int main() {
	freopen("polynomial.in", "r", stdin);
	freopen("polynomial.out", "w", stdout);
	pre();
	scanf("%d", &m);
	auto ans = solve(0, m - 1);
	printf("%d\n", ans.second - 1);
	for (int i = ans.first + ans.second - 1; i >= ans.first; i--) printf("%lld ", f[i]);
	return 0;
}