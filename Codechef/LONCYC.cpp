#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline void pc(char c) {
	if (_4 == _2 + BUF) fwrite(_2, 1, BUF, stdout), _4 = _2;
	*_4++ = c;
}
inline void rt() { fwrite(_2, 1, _4 - _2, stdout), exit(0); }
inline void $(int x) {
	static int _5[32];
	if (!x) {
		pc('0');
		return;
	}
	if (x < 0) {
		pc(45);
		x = -x;
	}
	register int _6;
	for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
	while (_6) pc(_5[_6--] ^ 48);
}
inline void $(long long x) {
	static int _5[64];
	if (!x) {
		pc('0');
		return;
	}
	if (x < 0) {
		pc(45);
		x = -x;
	}
	register int _6;
	for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
	while (_6) pc(_5[_6--] ^ 48);
}
inline int $() {
	register int x = 0;
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 200010
#define MAXM 5000010
int head[MAXN], to[MAXM << 1], next[MAXM << 1], tot;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int t, n, m, deep[MAXN], fa[MAXN], f[MAXN], g[MAXN], F[MAXN], G[MAXN];
int bad[MAXM], u[MAXM], v[MAXM], s[MAXN];
void dfs0(int x) {
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x]) continue;
		if (!deep[to[i]]) {
			deep[to[i]] = deep[x] + 1;
			fa[to[i]] = x;
			dfs0(to[i]);
		} else {
			if (deep[to[i]] < deep[x]) {
				s[to[i]]--;
				s[x]++;
				bad[i >> 1] = 1;
			}
		}
	}
}
void dfs1(int x) {
	f[x] = 1;
	g[x] = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x]) continue;
		if (deep[to[i]] > deep[x]) {
			if (deep[to[i]] == deep[x] + 1) {
				dfs1(to[i]);
				if (s[to[i]]) bad[i >> 1] = 1;
				s[x] += s[to[i]];
			}
			if (bad[i >> 1]) {
				g[x] += f[to[i]];
			} else {
				f[x] += f[to[i]];
				g[x] += g[to[i]];
			}
		}
	}
}
void dfs2(int x) {
	F[x] = 1;
	G[x] = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (deep[to[i]] < deep[x]) {
			if (bad[i >> 1]) {
				G[x] += F[to[i]] + f[to[i]] - 1;
			} else {
				G[x] += G[to[i]] + g[to[i]] - g[x];
				F[x] += F[to[i]] + f[to[i]] - f[x] - 1;
			}
		}
	}
	for (int i = head[x]; ~i; i = next[i]) {
		if (deep[to[i]] == deep[x] + 1) dfs2(to[i]);
	}
}
int main() {
	memset(head, -1, sizeof(head));
	for (t = $(); t; t--) {
		n = $(), m = $();
		for (int i = 1; i <= m; i++) $(u[i] = $(), v[i] = $());
		for (int i = 1; i <= n; i++) {
			if (!deep[i]) {
				deep[i] = 1;
				dfs0(i), dfs1(i), dfs2(i);
			}
		}
		// for (int i = 1; i <= n; i++) printf("%d %d %d %d\n", f[i], g[i], F[i], G[i]);
		for (int i = 1; i <= m; i++) {
			if (deep[u[i]] > deep[v[i]]) std::swap(u[i], v[i]);
			if (bad[i - 1]) {
				$(1LL * (F[u[i]] + f[u[i]] - 1) * f[v[i]]);
				pc(10);
			} else {
				$(1LL * (F[u[i]] + f[u[i]] - f[v[i]] - 1) * g[v[i]] + 1LL * (G[u[i]] + g[u[i]] - g[v[i]]) * f[v[i]] + 1LL * (F[u[i]] + f[u[i]] - f[v[i]] - 1) * f[v[i]]);
				pc(10);
			}
		}
		for (int i = 1; i <= n; i++) {
			head[i] = -1;
			deep[i] = s[i] = 0;
		}
		for (int i = 0; i < tot; i += 2) bad[i >> 1] = 0;
		tot = 0;
	}
	rt();
}