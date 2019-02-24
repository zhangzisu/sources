#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int MOD = 998244353;
const int INV = (MOD + 1) / 2;
inline void trim(int &x) { x -= MOD, x += (x >> 31) & MOD; }
int n, a[100], b[100], c[100], d = 1, e, f[5000];
char buf[100];
int main() {
	scanf("%d", &n);
	f[0] = 1;
	for (int i = 1; i < 5000; i++) f[i] = 1LL * f[i - 1] * INV % MOD;
	for (int i = 0; i < n; i++) {
		scanf("%s", buf);
		for (int j = 0; buf[j]; j++) (buf[j] == '?' ? trim(d += d), c : buf[j] == '0' ? a : b)[j] |= 1 << i;
	}
	for (int d = (1 << n) - 1; d; d--) {
		int ans = 1, all = __builtin_popcount(d), cur = 1, p = 0;
		for (int i = 0; ((a[i] | b[i] | c[i]) & d) == d; i++) {
			if ((a[i] & d) && (b[i] & d)) break;
			int cnt = __builtin_popcount(c[i] & d);
			if (cnt == all) trim(cur += cur);
			trim(ans += 1LL * cur * f[p += cnt] % MOD);
		}
		(all & 1) ? trim(e += ans) : trim(e += MOD - ans);
	}
	printf("%lld\n", 1LL * e * d % MOD);
	return 0;
}
