#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define MAXN 100010
typedef long long lnt;
inline lnt $() {
	register lnt x = 0;
	register char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
lnt t, n, m, a[MAXN], p[MAXN], c[MAXN], g[MAXN], skip[MAXN];
std::map<lnt, lnt> M;
lnt pre = 0, ans = 0, MOD, VAL, x, y, d;
inline lnt gcd(lnt a, lnt b) { return b ? gcd(b, a % b) : a; }
inline lnt lcm(lnt a, lnt b) {
	return a / gcd(a, b) * b;
}
inline lnt exgcd(lnt a, lnt b, lnt &x, lnt &y) {
	if (b) {
		lnt r = exgcd(b, a % b, y, x);
		y -= a / b * x;
		return r;
	} else {
		x = 1, y = 0;
		return a;
	}
}
inline lnt inv(lnt x, lnt p) {
	lnt l, r;
	exgcd(x, p, l, r);
	return ((l % p) + p) % p;
}
inline lnt fmul(lnt a, lnt b, lnt p) {
	lnt y = 0;
	for (; b; b >>= 1) {
		if (b & 1) y = (y + a) % p;
		a = (a + a) % p;
	}
	return y;
}

int main() {
	freopen("C:\\Users\\admin\\Desktop\\day2.tar\\day2\\dragon\\dragon1.in", "r", stdin);
	t = $();
	while (t--) {
		n = $(), m = $();
		for (int i = 1; i <= n; i++) a[i] = $();
		for (int i = 1; i <= n; i++) p[i] = $();
		for (int i = 1; i <= n; i++) c[i] = $();
		for (int i = 1; i <= n; i++) skip[i] = 0;
		M.clear();
		for (lnt x; m--; M[x]++) x = $();
		for (int i = 1; i <= n; i++) {
			auto it = M.upper_bound(a[i]);
			if (it != M.begin()) it--;
			g[i] = it->first;
			if (!--M[it->first]) M.erase(it);
			M[c[i]]++;
			lnt t = (a[i] + g[i] - 1) / g[i];
			pre = std::max(pre, t);
			if (p[i] == 1) skip[i] = 1;
		}

		for (int i = 1; i <= n; i++) {
			if (skip[i]) continue;
			a[i] = (((a[i] - fmul(pre, g[i], p[i])) % p[i]) + p[i]) % p[i];
		}
		for (int i = 1; i <= n; i++) {
			if (skip[i]) continue;
			lnt l = gcd(g[i], p[i]);
			if (a[i] % l) goto fail;
			g[i] /= l;
			a[i] /= l;
			p[i] /= l;
			lnt v = inv(g[i], p[i]);
			if (!v) goto fail;
			if (g[i] * v % p[i] != 1) {
				goto fail;
			}
			a[i] = fmul(a[i], v, p[i]);
		}
		MOD = p[1], VAL = a[1];
		// if (t == 0) printf("%lld %lld\n", p[1], a[1]);
		for (int i = 2; i <= n; i++) {
			if (skip[i]) continue;
			// if (t == 0) printf("%lld %lld\n", p[i], a[i]);
			d = exgcd(MOD, p[i], x, y);
			if ((VAL - a[i]) % d) {
				// fprintf(stderr, "FAILED at line %d\n", __LINE__);
				goto fail;
			}
			x = (VAL - a[i]) / d * x % (p[i] / d);
			VAL -= MOD * x;
			MOD = MOD / d * p[i];
			VAL %= MOD;
		}
		printf("%lld\n", (VAL % MOD + MOD) % MOD + pre);
		continue;
	fail:
		puts("-1");
	}
	return 0;
}