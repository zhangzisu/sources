#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define MAXN 25010
#define MAXK 410
#define MOD 1000000007
inline int fuck(int x, int p) {
	int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline void down(int &x, int y) {
	if ((x -= y) < 0) x += MOD;
}
int n, k, m, a[MAXN], f[MAXN][MAXK], g[MAXN][MAXK], frc[MAXN], inv[MAXN], count = 0;
std::map<int, int> M;

int main() {
	scanf("%d%d%d", &n, &k, &m);
	int all = 1LL * (n - m + 1) * fuck(k, n - m) % MOD;
	frc[0] = 1;
	for (int i = 1; i <= n; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
	inv[n] = fuck(frc[n], MOD - 2);
	for (int i = n; i >= 1; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
	for (int i = 1; i <= m; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= k && i <= m; i++)
		if (!M[a[i]]++) count++;
	for (int i = k + 1; i <= m; i++) {
		if (count == k) return printf("%lld\n", 1LL * (n - m + 1) * fuck(k, n - m)), 0;
		if (!--M[a[i - k]]) count--;
		if (!M[a[i]]++) count++;
	}
	if (count == k) return printf("%d\n", all), 0;
	if (count == m) {
		f[1][1] = k;
		for (int i = 1; i < n; i++) {
			for (int j = 1; j < k; j++) {
				up(f[i + 1][1], f[i][j]);
				down(f[i + 1][j + 1], f[i][j]);
				// printf("UP %d => [%d-%d]\n", f[i][j], 1, j);
				up(f[i + 1][j + 1], 1LL * f[i][j] * (k - j) % MOD);
				down(f[i + 1][j + 2], 1LL * f[i][j] * (k - j) % MOD);
				// printf("UP %d => %d\n", f[i][j] * (k - j), j + 1);
			}
			for (int j = 1; j <= k; j++) up(f[i][j], f[i][j - 1]);
			for (int j = 1; j <= k; j++) up(f[i + 1][j], f[i + 1][j - 1]);
		}
		return printf("%lld\n", (MOD + all - 1LL * f[n][k - 1] * frc[k - m] % MOD * inv[k] % MOD) % MOD), 0;
	}
	M.clear();
	count = 0;
	int l = 1, r = m;
	for (int i = 1; i <= m; i++) {
		if (!M[a[i]]++) count++;
		if (count == i)
			l = i;
		else
			break;
	}
	M.clear();
	count = 0;
	for (int i = m; i >= 1; i--) {
		if (!M[a[i]]++) count++;
		if (count == (m - i + 1))
			r = i;
		else
			break;
	}
	f[0][l] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < k; j++) {
			up(f[i + 1][1], f[i][j]);
			down(f[i + 1][j + 1], f[i][j]);
			// printf("UP %d => [%d-%d]\n", f[i][j], 1, j);
			up(f[i + 1][j + 1], 1LL * f[i][j] * (k - j) % MOD);
			down(f[i + 1][j + 2], 1LL * f[i][j] * (k - j) % MOD);
			// printf("UP %d => %d\n", f[i][j] * (k - j), j + 1);
		}
		for (int j = 1; j <= k; j++) up(f[i][j], f[i][j - 1]);
		for (int j = 1; j <= k; j++) up(f[i + 1][j], f[i + 1][j - 1]);
	}
	g[0][m - r + 1] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < k; j++) {
			up(g[i + 1][1], g[i][j]);
			down(g[i + 1][j + 1], g[i][j]);
			// printf("UP %d => [%d-%d]\n", g[i][j], 1, j);
			up(g[i + 1][j + 1], 1LL * g[i][j] * (k - j) % MOD);
			down(g[i + 1][j + 2], 1LL * g[i][j] * (k - j) % MOD);
			// printf("UP %d => %d\n", g[i][j] * (k - j), j + 1);
		}
		for (int j = 1; j <= k; j++) up(g[i][j], g[i][j - 1]);
		for (int j = 1; j <= k; j++) up(g[i + 1][j], g[i + 1][j - 1]);
	}
	int ans = 0;
	for (int i = 0; i <= (n - m); i++) {
		int left = i;
		int right = (n - m - i);
		up(ans, 1LL * f[left][k - 1] * g[right][k - 1] % MOD);
	}
	printf("%d\n", (MOD + all - ans) % MOD);
	return 0;
}