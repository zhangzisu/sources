#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 5000010
#define MOD 998244353
typedef long long lnt;
lnt n, k, q, vis[MAXN], pri[MAXN], mu[MAXN], val[MAXN], low[MAXN], tim[MAXN], pnt = 0;
inline lnt fuck(lnt x, lnt p) {
	register lnt y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = y * x % MOD;
		x = x * x % MOD;
	}
	return y;
}
inline void shai() {
	mu[1] = 1;
	val[1] = 1;
	for (lnt i = 2; i < MAXN; i++) {
		if (!vis[i]) {
			mu[i] = -1;
			pri[++pnt] = i;
			low[i] = i;
			tim[i] = 1;
			val[i] = (fuck(i, k) - 1 + MOD) % MOD;
		}
		for (lnt j = 1; j <= pnt; j++) {
			if (i * pri[j] >= MAXN) break;
			lnt next = i * pri[j];
			vis[next] = 1;
			if (i % pri[j]) {
				mu[next] = -mu[i];
				val[next] = val[i] * val[pri[j]] % MOD;
				low[next] = pri[j];
				tim[next] = 1;
			} else {
				mu[next] = 0;
				low[next] = low[i] * pri[j];
				tim[next] = tim[i] + 1;
				val[next] = val[i / low[i]] * (fuck(pri[j], tim[next] * k) - fuck(pri[j], (tim[next] * k - k)) + MOD) % MOD;
				break;
			}
		}
	}
}
int main() {
	scanf("%lld%lld", &q, &k);
	shai();
	while (q--) scanf("%lld", &n), printf("%lld\n", val[n]);
	return 0;
}