#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
#define MAXN 300010
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int n, f[MAXN][3], tmp[MAXN], pre[MAXN], suf[MAXN];
void dp(int x, int fa) {
	int c = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] != fa) dp(to[i], x);
	}
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] != fa) tmp[++c] = to[i];
	}
	if (!c) return void(f[x][0] = f[x][1] = 1);
	f[x][0] = f[x][1] = 1;
	for (int i = 1; i <= c; i++) {
		pre[i] = suf[i] = (f[tmp[i]][0] + f[tmp[i]][2]) % MOD;
		f[x][0] = 1LL * f[x][0] * f[tmp[i]][0] % MOD;
		f[x][1] = 1LL * f[x][1] * (f[tmp[i]][0] + f[tmp[i]][2]) % MOD;
	}
	pre[0] = suf[c + 1] = 1;
	for (int i = 1; i <= c; i++) pre[i] = 1LL * pre[i - 1] * pre[i] % MOD;
	for (int i = c; i >= 1; i--) suf[i] = 1LL * suf[i + 1] * suf[i] % MOD;
	for (int i = 1; i <= c; i++) up(f[x][2], 1LL * f[tmp[i]][1] * pre[i - 1] % MOD * suf[i + 1] % MOD);
	up(f[x][0], f[x][2]);
}
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
	dp(1, 0);
	printf("%d\n", f[1][0]);
	return 0;
}