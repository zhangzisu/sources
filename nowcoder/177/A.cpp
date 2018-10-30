#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
typedef long long lnt;
inline lnt calc(lnt limit1, lnt limit2, lnt m) {
	lnt ret = (limit1 ^ limit2) % m == 0;
	for (int i = 0; i <= 60; i++) {
		if ((limit1 >> i) & 1) {
			lnt L = (limit1 >> (i + 1) << (i + 1)) ^ (limit2 >> i << i);
			lnt R = L + (1LL << i) - 1;
			lnt cnt = (R + m) / m - (L + m - 1) / m;
            cnt %= MOD;
			ret = (ret + cnt) % MOD;
		}
	}
	for (int i = 0; i <= 60; i++) {
		if ((limit2 >> i) & 1) {
			lnt L = (limit2 >> (i + 1) << (i + 1)) ^ (limit1 >> i << i);
			lnt R = L + (1LL << i) - 1;
			lnt cnt = (R + m) / m - (L + m - 1) / m;
            cnt %= MOD;
			ret = (ret + cnt) % MOD;
		}
	}
	for (int i = 0; i <= 60; i++) {
		if ((limit1 >> i) & 1) {
			for (int j = 0; j <= 60; j++) {
				if ((limit2 >> j) & 1) {
					int h = std::max(i, j);
					int l = std::min(i, j);
					lnt L = (limit1 >> (h + (i == h)) << (h + (i == h))) ^ (limit2 >> (h + (j == h)) << (h + (j == h)));
					lnt R = L + (1LL << h) - 1;
					lnt cnt = (R + m) / m - (L + m - 1) / m;
                    cnt %= MOD;
					ret = (ret + (1LL << l) % MOD * cnt % MOD) % MOD;
				}
			}
		}
	}
	return ret;
}
lnt l1, r1, l2, r2, m;
int main() {
	scanf("%lld%lld%lld%lld%lld", &l1, &r1, &l2, &r2, &m);
	lnt ans = calc(r1, r2, m) - calc(l1 - 1, r2, m) - calc(r1, l2 - 1, m) + calc(l1 - 1, l2 - 1, m);
	((ans %= MOD) += MOD) %= MOD;
	printf("%lld\n", ans);
	return 0;
}