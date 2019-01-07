#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline int $() {
	register int x = 0;
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
inline int $$() {
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	return ch ^ 48;
}
#define MAXN 1000010
typedef long long lnt;
inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int t, n1, m1, n2, m2, sx, sy, lx, ly, a[MAXN], b[MAXN], c[MAXN];
lnt ans;
inline int get(int x, int y, int n, int m) {
	if (x < 1 || y < 1 || x > n || y > m) return 0;
	return (x - 1) * m + y;
}
inline lnt sumb(lnt xl, lnt xr, lnt yl, lnt yr) {
	return c[get(xr, yr, n2, m2)] - c[get(xr, yl - 1, n2, m2)] - c[get(xl - 1, yr, n2, m2)] + c[get(xl - 1, yl - 1, n2, m2)];
}
inline lnt sumy(lnt xl, lnt xr, lnt yl, lnt yr) {
	if (yl > yr) return 0;
	lnt YL = (yl + ly - 1) / ly;
	lnt YR = (yr + ly - 1) / ly;
	if (YL == YR) return sumb(xl, xr, YL, YR) * (yr - yl + 1);
	return sumb(xl, xr, YL, YL) * ((YL * ly) - yl + 1) +
	       sumb(xl, xr, YR, YR) * (yr - (YR - 1) * ly) +
	       ly * sumb(xl, xr, YL + 1, YR - 1);
}
inline lnt sum(lnt xl, lnt xr, lnt yl, lnt yr) {
	if (xl > xr || yl > yr) return 0;
	lnt XL = (xl + lx - 1) / lx;
	lnt XR = (xr + lx - 1) / lx;
	if (XL == XR) return sumy(XL, XR, yl, yr) * (xr - xl + 1);
	return sumy(XL, XL, yl, yr) * ((XL * lx) - xl + 1) +
	       sumy(XR, XR, yl, yr) * (xr - (XR - 1) * lx) +
	       lx * sumy(XL + 1, XR - 1, yl, yr);
}
int main() {
	for (t = $(); t; t--) {
		ans = 0;
		n1 = $(), m1 = $();
		for (int i = 1; i <= n1 * m1; i++) a[i] = $$();
		n2 = $(), m2 = $();
		for (int i = 1; i <= n2 * m2; i++) b[i] = $$();
		for (int i = 1; i <= n2; i++) {
			for (int j = 1; j <= m2; j++) {
				c[get(i, j, n2, m2)] = b[get(i, j, n2, m2)] + c[get(i - 1, j, n2, m2)] + c[get(i, j - 1, n2, m2)] - c[get(i - 1, j - 1, n2, m2)];
			}
		}
		sx = n2 / gcd(n1, n2);
		sy = m2 / gcd(m1, m2);
		lx = n1 / gcd(n1, n2);
		ly = m1 / gcd(m1, m2);
		for (int i = 1; i <= n1; i++) {
			for (int j = 1; j <= m1; j++) {
				lnt px = 1LL * sx * (i - 1) + 1;
				lnt py = 1LL * sy * (j - 1) + 1;
				lnt tx = px + sx - 1;
				lnt ty = py + sy - 1;
				lnt c1 = sum(px, tx, py, ty);
				lnt c0 = 1LL * sx * sy - c1;
				ans += a[get(i, j, n1, m1)] ? c1 : c0;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}