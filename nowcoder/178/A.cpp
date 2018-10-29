#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
#define MAXN 1000010
#define MOD 998244353
#define INF 0x3F3F3F3F
#define BASE 29
#define LOG 21
inline int getint() {
	int r = 0, s = 0;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) s |= c == '-';
	for (; isdigit(c); c = getchar()) r = (((r << 2) + r) << 1) + (c ^ '0');
	return s ? -r : r;
}
const int base = 37, mod = 1000000007;
int head[MAXN], next[MAXN], to[MAXN], val[MAXN], tot = 0;
inline void $(int u, int v, int w) {
	next[++tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot;
}
int dfn[MAXN], low[MAXN], dfsclk = 0, ins[MAXN], bel[MAXN], bc = 0, bs[MAXN];
std::stack<int> S;
inline void tarjan(int u) {
	dfn[u] = low[u] = ++dfsclk;
	ins[u] = 1;
	S.push(u);
	for (int i = head[u], v = to[i]; ~i; v = to[i = next[i]]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = std::min(low[u], low[v]);
		} else if (ins[v])
			low[u] = std::min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u] && ++bc) {
		int x = S.top();
		while (1) {
			bel[x] = bc;
			ins[x] = 0;
			bs[bc]++;
			S.pop();
			if (u == x) break;
			x = S.top();
		}
	}
}
int HEAD[MAXN], NEXT[MAXN], TO[MAXN], VAL[MAXN], TOT = 0, ind[MAXN];
inline void ADDEDGE(int u, int v, int w) {
	NEXT[++TOT] = HEAD[u], TO[TOT] = v, VAL[TOT] = w, HEAD[u] = TOT, ind[v]++;
}
std::queue<int> Q;
int topo[MAXN], tc = 0, f[MAXN], g[MAXN], hash[MAXN], trans[MAXN][LOG], suf[MAXN];
inline void link(int u, int v, int e) {
	trans[u][0] = v;
	f[u] = f[v] + 1;
	g[u] = (1LL * g[v] * BASE + VAL[e]) % MOD;
	suf[u] = VAL[e];
	hash[u] = (1LL * hash[v] * base + VAL[e]) % MOD;
}
inline int gao(int u, int d) {
	if (!d) return u;
	for (int i = 0; i < LOG; i++)
		if ((d >> i) & 1) u = trans[u][i];
	return u;
}
int pw[MAXN];
inline int gethash(int l, int r) {
	return (1LL * hash[l] + mod - (1LL * hash[trans[r][0]] * pw[r - l + 1] % mod)) % mod;
}
int n, m;
int main() {
	pw[0] = 1;
	for (int i = 1; i < MAXN; i++) pw[i] = 1LL * pw[i - 1] * base % MOD;
	memset(head, -1, sizeof(head));
	memset(HEAD, -1, sizeof(HEAD));
	n = getint(), m = getint();
	for (int i = 1, x, y, z; i <= m; i++) {
		x = getint(), y = getint(), z = getint();
		$(x, y, z);
	}
	for (int i = 1; i <= n; i++) {
		if (!dfn[i]) tarjan(i);
	}
	for (int u = 1; u <= n; u++) {
		for (int i = head[u], v = to[i]; ~i; v = to[i = next[i]]) {
			if (bel[u] != bel[v]) {
				ADDEDGE(bel[u], bel[v], val[i]);
			}
		}
	}
	for (int i = 1; i <= bc; i++)
		if (!ind[i]) Q.push(i);
	while (Q.size()) {
		int u = Q.front();
		Q.pop();
		topo[++tc] = u;
		for (int i = HEAD[u], v = TO[i]; ~i; v = TO[i = NEXT[i]]) {
			if (!ind[v]) continue;
			if (!--ind[v]) Q.push(v);
		}
	}
	memset(f, -1, sizeof(f));
	memset(g, -1, sizeof(g));
	for (int I = bc; I; I--) {
		int u = topo[I];
		if (!~f[u]) {
			f[u] = bs[u] > 1 ? INF : 0;
			g[u] = bs[u] > 1 ? INF : 0;
		}
		for (int i = HEAD[u], v = TO[i]; ~i; v = TO[i = NEXT[i]]) {
			if (f[v] + 1 > f[u]) {
				link(u, v, i);
			} else if (f[v] + 1 == f[u]) {
				if (VAL[v] < suf[u]) {
					link(u, v, i);
					continue;
				}
				if (VAL[v] > suf[u]) continue;
				int ano = trans[u][0];
				int l = 0, r = f[v], ans = 0;
				while (l <= r) {
					int mid = (l + r) >> 1;
					int A = gao(v, mid);
					int B = gao(ano, mid);
					if (gethash(v, A) == gethash(ano, B))
						ans = mid, l = mid + 1;
					else
						r = mid - 1;
				}
				if (suf[gao(v, ans)] < suf[gao(ano, ans)]) link(u, v, i);
			}
		}
		for (int i = 1; i < LOG; i++) trans[u][i] = trans[trans[u][i - 1]][i - 1];
	}
	for (int i = 1; i <= n; i++) {
		if (bs[bel[i]] > 1)
			puts("Infinity");
		else
			printf("%lld\n", 1LL * g[bel[i]] * BASE % MOD);
	}
	return 0;
}