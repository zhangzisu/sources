#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
#define MOD 2333
typedef long long lnt;
lnt n, m;
lnt vis[MAXN], d[MAXN], p[MAXN], pri[MAXN], pnt, ans;
inline void up(lnt &x, lnt y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline void shai() {
	d[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		if (!vis[i]) {
			pri[++pnt] = i;
			d[i] = 2;
			p[i] = 1;
		}
		for (int j = 1, next; j <= pnt; j++) {
			if ((next = i * pri[j]) >= MAXN) break;
			vis[next] = 1;
			if (i % pri[j]) {
				d[next] = d[i] * 2;
				p[next] = d[i];
			} else {
				d[next] = d[i] + p[i];
				p[next] = p[i];
				break;
			}
		}
		up(d[i], d[i - 1]);
	}
}
lnt calc(lnt n) {
	if (n < MAXN) return d[n];
	lnt m = sqrt(n), ret = 0;
	for (lnt i = 1; i <= m; i++) up(ret, (n / i) % MOD);
	return (2LL * ret - 1LL * m * m + MOD) % MOD;
}
lnt calc2(lnt n) {
	lnt ret = calc(n);
	for (lnt i = 1; i <= m; i++) up(ret, MOD - (n / i) % MOD);
	return ret;
}
int main() {
	shai();
	scanf("%lld", &n);
	m = cbrt(n);
	ans = m * m * m % MOD;
	for (lnt i = m, j; i; i = j) {
		j = n / (n / i + 1);
		up(ans, 3LL * calc2(n / i) * (i - j) % MOD);
	}
	printf("%lld\n", ans);
}