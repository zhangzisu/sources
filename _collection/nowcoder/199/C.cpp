#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int N = 2048;
const int N2 = 4096;
#define MOD 998244353
#define G 3
inline int fuck(int x, int p, int m) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % m;
		x = 1LL * x * x % m;
	}
	return y;
}
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int pre[N2], wn[N2];
inline void calc(int N) {
	for (int i = 1, j = 0; i < N - 1; i++) {
		for (int t = N; ~j & t; j ^= t) t >>= 1;
		pre[i] = j;
	}
	for (int k = 1; k < N; k <<= 1) {
		int t = k << 1;
		wn[k] = fuck(G, (MOD - 1) / t, MOD);
	}
}
inline void NTT(int *a, int N) {
	for (int i = 1; i < N - 1; i++) {
		if (i < pre[i]) std::swap(a[i], a[pre[i]]);
	}
	for (int k = 1; k < N; k <<= 1) {
		int t = k << 1, fucker = wn[k];
		for (int i = 0; i < N; i += t) {
			int fucked = 1;
			for (int j = 0; j < k; j++, fucked = 1LL * fucked * fucker % MOD) {
				int x = a[i + j];
				int y = 1LL * fucked * a[i + j + k] % MOD;
				a[i + j] = (x + y) % MOD;
				a[i + j + k] = (x - y + MOD) % MOD;
			}
		}
	}
}
int frc[N2 + 1], ifrc[N2 + 1], inv[N2 + 1], m, k, n, ans;
int f[N][N], s[N2][N];
int F[N2], T[N2];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	frc[0] = frc[1] = ifrc[0] = ifrc[1] = inv[1] = 1;
	for (int i = 2; i <= N2; i++) {
		inv[i] = 1LL * (MOD - MOD / i) * inv[MOD % i] % MOD;
		frc[i] = 1LL * frc[i - 1] * i % MOD;
		ifrc[i] = 1LL * ifrc[i - 1] * inv[i] % MOD;
	}
	for (int i = 1; i < N; i++) f[0][i] = ifrc[i];
	for (int i = 1; i < N; i++) T[i] = ifrc[i];
	calc(N2);
	NTT(T, N2);
	for (int i = 0; i <= m; i++) {
		up(ans, 1LL * f[i][n] * frc[n] % MOD);
		// fprintf(stderr, "ANS %d\n", ans);
		memcpy(F, f[i], sizeof(int) * N);
		memset(F + N, 0, sizeof(int) * N);
		NTT(F, N2);
		for (int j = 0; j < N2; j++) F[j] = 1LL * F[j] * T[j] % MOD;
		NTT(F, N2);
		std::reverse(F + 1, F + N2);
		for (int j = 0; j < N2; j++) F[j] = 1LL * F[j] * inv[N2] % MOD;

		for (int j = 0; j < N; j++) up(s[i + 1][j], F[j]);
		for (int j = 0; j < N; j++) up(s[i + k + 1][j], MOD - F[j]);
		for (int j = 0; j < N; j++) up(s[i + 1][j], s[i][j]);
		for (int j = 0; j < N; j++) f[i + 1][j] = s[i + 1][j];
		// fprintf(stderr, "PASS %d\n", i);
	}
	printf("%d\n", ans);
	return 0;
}