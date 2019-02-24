#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#define ppc __builtin_popcount
typedef long long LL;
const int N = 55, M = N * N, MOD = 998244353;
const LL iv2 = (MOD + 1) / 2;
int a[N], b[N], c[N], n, ans, re = 1;
char buf[N];
int pw[N] = {1}, inv[M] = {1};
inline int e2(int x) { return x > 0 ? pw[x] : inv[-x]; }
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline void down(int &x, int y) {
	if ((x -= y) < 0) x += MOD;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i < N; i++) pw[i] = 2LL * pw[i - 1] % MOD;
	for (int i = 1; i < M; i++) inv[i] = iv2 * inv[i - 1] % MOD;
	for (int i = 0; i < n; i++) {
		scanf("%s", buf);
		for (int j = 0, m = strlen(buf), I = 1 << i; j < m; j++) (buf[j] == '?' ? (re = 2LL * re % MOD, c) : (buf[j] == '0' ? a : b))[j] |= I;
	}
	for (int i = 1, sz = 1 << n; i < sz; i++) {
		int ret = 1, ex = 0;
		for (int j = 0; ((a[j] | b[j] | c[j]) & i) == i; j++) {
			if ((a[j] & i) && (b[j] & i)) break;
			ex += ((c[j] & i) == i) - ppc(c[j] & i);
			up(ret, e2(ex));
		}
		ppc(i) & 1 ? up(ans, ret) : down(ans, ret);
		printf("%d => %d\n", i, ret);
	}
	printf("%lld\n", 1LL * ans * re % MOD);
	return 0;
}
