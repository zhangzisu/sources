#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
#define MOD 1000000007
const int INF = (~0U) >> 1;
typedef long long lnt;
lnt n, k, t, ans, a[MAXN], l[MAXN], r[MAXN], s[MAXN];
inline void up(lnt &x, lnt y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline void down(lnt &x, lnt y) {
	if ((x -= y) < 0) x += MOD;
}
int main() {
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	a[0] = a[n + 1] = INF;
	s[t = 0] = 0;
	for (int i = 1; i <= n; i++) {
		while (t && a[s[t]] < a[i]) t--;
		l[i] = s[t] + 1;
		s[++t] = i;
	}
	s[t = 0] = n + 1;
	for (int i = n; i >= 1; i--) {
		while (t && a[s[t]] < a[i]) t--;
		r[i] = s[t] - 1;
		s[++t] = i;
	}
	for (int i = 1; i <= n; i++) {
		lnt count = 0;
		lnt len = r[i] - l[i] + 1;
		lnt limit = len / k;
		lnt split = (r[i] - i + 1) / k;
		up(count, split * i % MOD);
		up(count, (r[i] - k * (split + 1) + 1 + r[i] - k * limit + 1) * (limit - split) / 2 % MOD);
		split = (i - l[i] + 1) / k;
		down(count, (i - k + 1 + i - split * k + 1) * (split) / 2 % MOD);
		down(count, (limit - split) * l[i] % MOD);
        up(count, limit);
		up(ans, count * a[i] % MOD);
	}
	printf("%lld\n", ans);
	return 0;
}