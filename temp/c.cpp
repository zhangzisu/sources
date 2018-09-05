#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
#define MAXN 100010
inline int fuck(int x, int p) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
int n, m, in, a[MAXN], sum;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		(sum += a[i]) %= MOD;
	}
	in = fuck(n, MOD - 2);
	while (m--) {
		int x, t;
		scanf("%d%d", &x, &t);
		int ans = 1LL * sum * in % MOD * fuck(n - 1, t) % MOD;
		(ans += 1LL * (t & 1 ? 1 : -1) * sum * in % MOD) %= MOD;
		(ans += MOD) %= MOD;
		(ans += 1LL * (t & 1 ? -1 : 1) * a[x]) %= MOD;
		(ans += MOD) %= MOD;
		printf("%d\n", ans);
	}
	return 0;
}