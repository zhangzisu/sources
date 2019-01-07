#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 65536
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2;
int _0;
inline char gc() {
	if (_3 == _1 + BUF) _0 = fread(_1, 1, BUF, stdin), _3 = _1;
	return _3 == _1 + _0 ? 0 : *_3++;
}
inline void pc(char c) {
	if (_4 == _2 + BUF) fwrite(_2, 1, BUF, stdout), _4 = _2;
	*_4++ = c;
}
inline void rt() {
	fwrite(_2, 1, _4 - _2, stdout);
	exit(0);
}
inline int $() {
	register int x = 0;
	register char ch = gc();
	while (!isdigit(ch) && (ch ^ 45)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
inline void pi(int x) {
	static int _5[32];
	if (!x) return pc('0');
	if (x < 0) pc(45), x = -x;
	register int _6;
	for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
	while (_6) pc(_5[_6--] ^ 48);
}
#include <queue>
#include <vector>
#define MAXN 300010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int n, f[MAXN], g[MAXN], F[MAXN], G[MAXN];
void dfs1(int x, int fa) {
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		dfs1(to[i], x);
		f[x] = std::max(f[x], f[to[i]]);
		f[x] = std::max(f[x], g[x] + g[to[i]] + 1);
		g[x] = std::max(g[x], g[to[i]] + 1);
	}
}
inline void ensure(int &x, int y) {
	if (y > x) x = y;
}
inline void ensure(int &x1, int &x2, int y) {
	if (y >= x1)
		x2 = x1, x1 = y;
	else
		ensure(x2, y);
}
inline void ensure(int &x1, int &x2, int &x3, int y) {
	if (y >= x1)
		x3 = x2, x2 = x1, x1 = y;
	else
		ensure(x2, x3, y);
}
int ans = 0x3F3F3F3F, ansp = -1;
void dfs2(int x, int fa) {
	int max1 = 0, max2 = 0, max3 = 0;
	int MAX1 = 0, MAX2 = 0;
	ensure(max1, max2, max3, G[x] + 1);
	ensure(MAX1, MAX2, F[x]);
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		ensure(max1, max2, max3, g[to[i]] + 1);
		ensure(MAX1, MAX2, f[to[i]]);
	}
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		int &nextF = F[to[i]];
		int &nextG = G[to[i]];
		if (f[to[i]] == MAX1) {
			nextF = MAX2;
		} else {
			nextF = MAX1;
		}
		if (g[to[i]] + 1 == max1) {
			nextF = std::max(nextF, max2 + max3);
			nextG = max2;
		} else if (g[to[i]] + 1 == max2) {
			nextF = std::max(nextF, max1 + max3);
			nextG = max1;
		} else {
			nextF = std::max(nextF, max1 + max2);
			nextG = max1;
		}
		int val = (F[to[i]] + 1) / 2 + (f[to[i]] + 1) / 2 + 1;
		val = std::max(val, std::max(F[to[i]], f[to[i]]));
		if (val < ans) ans = val, ansp = i >> 1;
		dfs2(to[i], x);
	}
}
std::vector<int> path;
std::queue<int> Q;
int fa[MAXN], deep[MAXN];
inline int bfs(int x, int ban) {
	Q.push(x);
	memset(fa, 0, sizeof(fa));
	memset(deep, 0, sizeof(deep));
	while (Q.size()) {
		x = Q.front();
		Q.pop();
		for (int i = head[x]; ~i; i = next[i]) {
			if (to[i] == ban || to[i] == fa[x]) continue;
			fa[to[i]] = x;
			deep[to[i]] = deep[x] + 1;
			Q.push(to[i]);
		}
	}
	return x;
}
inline int gao(int x, int ban) {
	int d = bfs(bfs(x, ban), ban);
	for (path.clear(); d; d = fa[d]) path.push_back(d);
	return path[path.size() >> 1];
}
int main() {
	memset(head, -1, sizeof(head));
	n = $();
	for (int i = 1; i < n; i++) $($(), $());
	dfs1(1, 0);
	G[1] = -1;
	dfs2(1, 0);
	printf("%d\n", ans);
	printf("%d %d\n", to[ansp << 1], to[ansp << 1 | 1]);
	printf("%d %d\n", gao(to[ansp << 1], to[ansp << 1 | 1]), gao(to[ansp << 1 | 1], to[ansp << 1]));
	rt();
}