#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
#define MOD 1000000007
const int MAXD = 1 << 15;
typedef long long lnt;
lnt s1, s2, a[MAXN];
int n, all, v[MAXN], f[MAXN][MAXD];
const int primes[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int g[MAXD], h[MAXD], ans;
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline void FWT(int *a, int len) {
	for (int i = 1; i < len; i <<= 1) {
		int t = i << 1;
		for (int j = 0; j < len; j += t) {
			for (int k = 0; k < i; k++) {
				up(a[j + k + i], a[j + k]);
			}
		}
	}
}
inline void IFWT(int *a, int len) {
	for (int i = 1; i < len; i <<= 1) {
		int t = i << 1;
		for (int j = 0; j < len; j += t) {
			for (int k = 0; k < i; k++) {
				up(a[j + k + i], MOD - a[j + k]);
			}
		}
	}
}
void dp(int x, int fa) {
	f[x][0] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		dp(to[i], x);
		int delta = v[x] ^ v[to[i]];
		memset(g, 0, sizeof(g));
		for (int j = 0; j < (MAXD); j++) up(g[j | delta], f[x][j]);
		memcpy(h, f[to[i]], sizeof(h));
		FWT(g, MAXD);
		FWT(h, MAXD);
		for (int j = 0; j < MAXD; j++) g[j] = 1LL * g[j] * h[j] % MOD;
		IFWT(g, MAXD);
		for (int j = 0; j < MAXD; j++) up(f[x][j], g[j]);
	}
	up(ans, f[x][all]);
}
int main() {
	scanf("%d%lld%lld", &n, &s1, &s2);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++) {
		a[i] /= s1;
		for (int j = 0; j < 15; j++)
			if (a[i] % primes[j] == 0) v[i] |= 1 << j;
	}
	s2 /= s1;
	for (int j = 0; j < 15; j++)
		if (s2 % primes[j] == 0) all |= 1 << j;
	memset(head, -1, sizeof(head));
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
	dp(1, 0);
	printf("%d\n", ans);
	return 0;
}