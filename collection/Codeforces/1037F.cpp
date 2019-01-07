#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
#define MOD 1000000007
const int INF = (~0U) >> 1;
typedef long long lnt;
lnt n, k, t, ans, a[MAXN], l[MAXN], r[MAXN], s[MAXN];
const lnt inv2 = 500000004;
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
		while (t && a[s[t]] <= a[i]) t--;
		r[i] = s[t] - 1;
		s[++t] = i;
	}
	--k;
	for (int i = 1; i <= n; i++) {
		lnt count = 0;
		lnt len = r[i] - l[i] + 1;
		lnt limit = (len - 1) / k;

		lnt split = (r[i] - i + k - 1) / k;
		(count += (split - 1) * i % MOD) %= MOD;
		(count += MOD) %= MOD;
		(count += (r[i] - k * split % MOD + r[i] - limit * k % MOD) * (limit - split + 1) % MOD * inv2 % MOD) %= MOD;
		(count += MOD) %= MOD;

		split = (i - l[i]) / k;
		(count -= (i - k + i - split * k % MOD) * split % MOD * inv2 % MOD) %= MOD;
		(count += MOD) %= MOD;
		(count -= (limit - split) * l[i] % MOD) %= MOD;
		(count += MOD) %= MOD;
		(count += limit) %= MOD;
		(ans += count * a[i] % MOD) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
}