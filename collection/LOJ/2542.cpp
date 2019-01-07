#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 18
#define MOD 998244353
int n, q, root, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline int fpow(int x, int p) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
int f[1 << MAXN], A[MAXN], B[MAXN];
void dfs(int x, int fa, int mask) {
	if ((mask >> x) & 1) {
		A[x] = B[x] = 0;
	} else {
		int sa = 0, sb = 0, d = 0;
		for (int i = head[x]; ~i; i = next[i]) {
			d++;
			if (to[i] == fa) continue;
			dfs(to[i], x, mask);
			up(sa, A[to[i]]);
			up(sb, B[to[i]]);
		}
		d = fpow(d, MOD - 2);
		int k = MOD - 1LL * sa * d % MOD + 1;
		k = fpow(k, MOD - 2);
		A[x] = 1LL * d * k % MOD;
		B[x] = (1LL * d * sb % MOD + 1) * k % MOD;
	}
}
int main() {
	scanf("%d%d%d", &n, &q, &root), root--;
	memset(head, -1, sizeof(head));
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u - 1, v - 1);
	for (int i = 1; i < (1 << n); i++) {
		dfs(root, -1, i);
		f[i] = B[root];
	}
	for (int k; q; q--) {
		int mask = 0, ans = 0;
		scanf("%d", &k);
		for (int x; k; k--) scanf("%d", &x), mask |= 1 << (x - 1);
		for (int i = mask; i; i = (i - 1) & mask)
			up(ans, 1LL * ((__builtin_popcount(i) & 1) ? 1 : MOD - 1) * f[i] % MOD);
		printf("%d\n", ans);
	}
	return 0;
}