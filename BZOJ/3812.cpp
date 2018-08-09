#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define popcount(x) __builtin_popcount(x)
#define MOD 1000000007

int n, m, in[1 << 15], out[1 << 15], bin[300];
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline int lowbit(int x) { return x & -x; }
int sum[1 << 15], into[1 << 15], f[1 << 15], g[1 << 15];
inline void calc(int i, int j) {
	if (!j) return;
	calc(i, (j - 1) & i);
	into[j] = into[j - lowbit(j)] + popcount(in[lowbit(j)] & i);
}
int main(int argc, char const *argv[]) {
	bin[0] = 1;
	for (int i = 1; i < 300; i++) bin[i] = 1LL * bin[i - 1] * 2 % MOD;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		u--, v--;
		in[1 << v] |= 1 << u;
		out[1 << u] |= 1 << v;
	}
	for (int i = 1; i < (1 << n); i++) {
		int p = i - lowbit(i);
		sum[i] = sum[p] + popcount(in[lowbit(i)] & i) + popcount(out[lowbit(i)] & i);
		f[i] = bin[sum[i]];
		calc(i, i);
		for (int j = p; j; j = (j - 1) & p) up(g[i], MOD - 1LL * f[i - j] * g[j] % MOD);
		for (int j = i; j; j = (j - 1) & i) up(f[i], MOD - 1LL * bin[sum[i] - into[j]] * g[j] % MOD);
		up(g[i], f[i]);
	}
	printf("%d\n", f[(1 << n) - 1]);
	return 0;
}
