#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using u = unsigned;
const u MOD = 0x7FFFFFFF;
inline u add(u x, u y) {
	return x + y >= MOD ? x + y - MOD : x + y;
}
inline u fuck(u x, u y) {
	u z = 1;
	for (; y; y >>= 1) {
		if (y & 1) z = 1ULL * z * x % MOD;
		x = 1ULL * x * x % MOD;
	}
	return z;
}
int N, M;
u s, t, x0, ans, base[8192], cur[8192], inv[1048576];
int main() {
	freopen("sqr.in", "r", stdin);
	freopen("sqr.out", "w", stdout);
	scanf("%d%u%u%u", &N, &s, &t, &x0);
	M = (int)sqrt(N);
	N = M * M;
	inv[1] = 1;
	for (int i = 2; i <= N + N + 1; i++) inv[i] = (1ULL * (MOD - MOD / i) * inv[MOD % i]) % MOD;
	if (s == t) {
		for (int i = 1; i * i <= N; i++) {
			for (int j = 1; j * j <= N; j++) {
				int n = i * i + j * j;
				u ans = add(fuck((x0 + s) % MOD, n + 1), MOD - fuck(s, n + 1));
				ans = 1ULL * ans * inv[n + 1] % MOD;
				printf("%u ", ans);
			}
			puts("");
		}
		return 0;
	}
	base[0] = 1;
	for (int n = 1; n <= M; n++) {
		int nn = n * n;
		for (int p = (n - 1) * (n - 1) + 1; p <= nn; p++) {
			for (register int i = p; i >= 1; i--) base[i] = add(1ULL * base[i] * s % MOD, base[i - 1]);
			base[0] = 1ULL * base[0] * s % MOD;
		}
		memcpy(cur, base, sizeof(cur));
		for (int m = 1; m <= M; m++) {
			int mm = m * m;
			for (int p = (m - 1) * (m - 1) + 1; p <= mm; p++) {
				for (register int i = nn + p; i >= 1; i--) cur[i] = add(1ULL * cur[i] * t % MOD, cur[i - 1]);
				cur[0] = 1ULL * cur[0] * t % MOD;
			}
			u ans = 0;
			for (register int i = 0, x = x0; i <= nn + mm; i++, x = 1ULL * x * x0 % MOD) ans = add(ans, 1ULL * x * cur[i] % MOD * inv[i + 1] % MOD);
			printf("%u ", ans);
		}
		puts("");
	}
	return 0;
}
