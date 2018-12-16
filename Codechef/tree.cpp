#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 210
#define MOD 1000000007
inline int trim(int x) {
	return x >= MOD ? x - MOD : x;
}
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int size[MAXN], bin[MAXN * MAXN], f[MAXN][MAXN][MAXN], g[MAXN][MAXN];
inline int fuck(int x, int p) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
void dp(int x, int fa) {
	f[x][0][1] = size[x] = 1;
	size[x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		dp(to[i], x);
		for (int j = 0; j <= size[x] + size[to[i]]; j++) memset(g[j], 0, sizeof(int) * (size[x] + size[to[i]] + 1));
		for (int j = 0; j <= size[to[i]]; j++) {
			for (int k = 0; k <= size[x]; k++) {
				for (int p = 1; p <= size[to[i]]; p++) {
					for (int q = 1; q <= size[x]; q++) {
						up(g[j + k + 1][q], 1LL * f[x][k][q] * f[to[i]][j][p] % MOD);
						up(g[j + k][p + q], 1LL * f[x][k][q] * f[to[i]][j][p] % MOD * bin[p * q - 1] % MOD);
					}
				}
			}
		}
		size[x] += size[to[i]];
		for (int j = 0; j <= size[x]; j++) memcpy(f[x][j], g[j], sizeof(int) * (size[x] + 1));
	}
}
int n, ans[MAXN], frc[MAXN], inv[MAXN];
inline int C(int n, int m) { return m <= n ? 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD : 0; }
int main() {
	memset(head, -1, sizeof(head));
	bin[0] = 1;
	for (int i = 1; i < MAXN * MAXN; i++) bin[i] = trim(bin[i - 1] << 1);
	frc[0] = 1;
	for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
	inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
	for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;

	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
	dp(1, 0);
	for (int i = 0; i <= n; i++)
		for (int j = 1; j <= n; j++) up(ans[i], f[1][i][j]);
	for (int i = n - 1; ~i; i--)
		for (int j = i + 1; j < n; j++)
			up(ans[i], MOD - 1LL * C(j, i) * ans[j] % MOD);
	for (int i = 1; i <= n; i++) printf("%d ", ans[i - 1]);
	return 0;
}