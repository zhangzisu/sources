#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
#define MOD 998244353
inline void trim(int &x) { x -= MOD, x += (x >> 31) & MOD; }
int n, w[MAXN], head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
inline void FWT(int *a, register int n) {
	for (register int i = 1; i < n; i <<= 1) {
		for (register int j = 0; j < n; j += i << 1) {
			for (register int k = 0; k < i; k++) {
				register int x = a[j + k], y = a[j + k + i];
				trim(a[j + k] = x + y);
				trim(a[j + k + i] = MOD + x - y);
			}
		}
	}
}
inline void IFWT(int *a, register int n) {
	for (register int i = 1; i < n; i <<= 1) {
		for (register int j = 0; j < n; j += i << 1) {
			for (register int k = 0; k < i; k++) {
				register int x = a[j + k], y = a[j + k + i];
				a[j + k] = 499122177LL * (x + y) % MOD;
				a[j + k + i] = 499122177LL * (MOD + x - y) % MOD;
			}
		}
	}
}
int f[MAXN][1 << 15], g[1 << 15];
void dp(int x, int fa) {
	f[x][w[x]] = 1;
	FWT(f[x], 1 << 15);
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		dp(to[i], x);
		for (int j = 0; j < (1 << 15); j++) trim(f[x][j] += 1LL * f[x][j] * f[to[i]][j] % MOD);
	}
	for (int i = 0; i < (1 << 15); i++) trim(g[i] += f[x][i]);
}
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", w + i);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
	dp(1, 0);
	IFWT(g, 1 << 15);
	for (int i = 0; i < (1 << 15); i++) printf("%d ", g[i]);
	puts("");
	return 0;
}