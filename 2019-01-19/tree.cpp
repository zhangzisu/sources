#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
const int MOD = 1000000007;
inline int fp(int x, int y) {
	int z = 1;
	for (; y; y >>= 1) {
		if (y & 1) z = 1LL * z * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return z;
}
inline void trim(int &x) { x -= MOD, x += (x >> 31) & MOD; }
inline void up(int &x, int y) { trim(x += y); }
const int MAXN = 1010;
const int MAXM = 12;
int n, m, all, valid[1 << MAXM], top[1 << MAXM], pa[1 << MAXM], g[MAXM][MAXM];
int dfs(int x, int fa) {
	int state = 1 << x;
	for (int i = 0; i < m; ++i) {
		if (i == fa || !g[x][i]) continue;
		state |= dfs(i, x);
	}
	valid[state] = 1, top[state] = x, pa[state] = fa;
	return state;
}
std::vector<int> next[MAXN];
int f[MAXN][1 << MAXM], db[1 << MAXM], tmp[1 << MAXM], ans;
void dp(int x, int fa) {
	int *now = f[x];
	for (int y : next[x]) {
		if (y == fa) continue;
		dp(y, x);
	}
	memset(db, -1, sizeof(db));
	for (int y : next[x]) {
		if (y == fa) continue;
		int *son = f[y];
		for (int i = 1; i < all; ++i) {
			if (!valid[i] || !son[i]) continue;
			db[i] = pa[i];
			up(tmp[i], son[i]);
		}
		for (int i = 3; i < all; ++i) {
			for (int j = (i - 1) & i; j; j = (j - 1) & i) {
				if (!~db[i ^ j] || !valid[j] || !g[db[i ^ j]][top[j]]) continue;
				db[i] = db[i ^ j];
				up(tmp[i], 1LL * now[i ^ j] * son[j] % MOD);
			}
		}
		for (int i = 0; i < all; ++i) up(now[i], tmp[i]), tmp[i] = 0;
	}
	for (int i = 0; i < m; ++i) up(ans, now[all ^ (1 << i)]);
	for (int i = 0; i < all; ++i) {
		if (~db[i] && now[i]) {
			tmp[i | (1 << db[i])] = now[i];
		}
	}
	for (int i = 0; i < m; ++i) {
		if (valid[1 << i]) {
			up(tmp[1 << i], 1);
		}
	}
	for (int i = 0; i <= all; ++i) {
		now[i] = valid[i] ? tmp[i] : 0;
		tmp[i] = 0;
	}
}
inline int lowbit(int x) { return x & -x; }
int u1[MAXN], v1[MAXN], u2[MAXN], v2[MAXN];
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) scanf("%d%d", u1 + i, v1 + i), --u1[i], --v1[i];
	scanf("%d", &m);
	if (m == 1) return printf("%d\n", n), 0;
	all = (1 << m) - 1;
	for (int i = 1; i < m; ++i) scanf("%d%d", u2 + i, v2 + i), --u2[i], --v2[i];
	for (int i = 1; i < m; ++i) g[u2[i]][v2[i]] = g[v2[i]][u2[i]] = 1;
	for (int i = 0; i < m; ++i) dfs(i, -1);
	valid[all] = top[all] = pa[all] = 0;
	for (int i = 1; i < m; ++i) {
		next[u2[i]].push_back(v2[i]);
		next[v2[i]].push_back(u2[i]);
	}
	dp(0, -1);
	int fuck = ans;
	ans = 0;
	memset(f, 0, sizeof(f));
	for (int i = 0; i < n; ++i) next[i].clear();
	for (int i = 1; i < n; ++i) {
		next[u1[i]].push_back(v1[i]);
		next[v1[i]].push_back(u1[i]);
	}
	dp(0, -1);
	printf("%lld\n", 1LL * ans * fp(fuck, MOD - 2) % MOD);
	return 0;
}
