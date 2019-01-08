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
inline void pi(int x) {
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
inline int $() {
	register int x = 0;
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
inline char ga() {
	register char ch = gc();
	while (!isalpha(ch)) ch = gc();
	return ch;
}
#define MAXN 50010
#define SQRT 230
#define LOGN 16
int n, a[MAXN], b[MAXN], md = LOGN;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int deep[MAXN], fa[MAXN][LOGN], p[MAXN][LOGN], s[MAXN][LOGN];
void dfs(int x) {
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x][0]) continue;
		fa[to[i]][0] = x;
		deep[to[i]] = deep[x] + 1;
		dfs(to[i]);
	}
}
inline int getFa(int x, int d) {
	for (int i = 0; i < 16 && d; i++)
		if ((d >> i) & 1) x = fa[x][i], d -= 1 << i;
	return x;
}
inline int lca(int x, int y) {
	if (deep[x] < deep[y]) std::swap(x, y);
	x = getFa(x, deep[x] - deep[y]);
	for (int i = 15; ~i; i--)
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return x == y ? x : fa[x][0];
}
struct query_t {
	int u, v, c, id;
} query[MAXN];
inline int cmp(const query_t& a, const query_t& b) { return a.c < b.c; }
int ans[MAXN];
int main() {
	n = $();
	for (int i = 1; i <= n; i++) a[i] = $();
	memset(head, -1, sizeof(head));
	for (int i = 1; i < n; i++) $($(), $());
	dfs(1);
	for (int d = 1; d < 16; d++)
		for (int i = 1; i <= n; i++)
			fa[i][d] = fa[fa[i][d - 1]][d - 1];
	for (int i = 1; i <= n; i++) b[i] = $();
	for (int i = 1; i < n; i++) query[i].u = b[i], query[i].v = b[i + 1], query[i].c = $(), query[i].id = i;
	std::sort(query + 1, query + n, cmp);
	for (int i = 1, pre = 0; i < n; i++) {
		query_t& q = query[i];
		int u = q.u, v = q.v;
		int l = lca(u, v);
		int rest = (deep[u] - deep[l] + deep[v] - deep[l]) % q.c;
		if (q.c < SQRT) {
			if (pre < q.c) {
				for (int i = 1; i <= n; i++) p[i][0] = getFa(i, q.c), s[i][0] = a[i];
				for (int d = 1; d < md; d++) {
					for (int i = 1; i <= n; i++) {
						p[i][d] = p[p[i][d - 1]][d - 1];
						s[i][d] = s[p[i][d - 1]][d - 1] + s[i][d - 1];
					}
				}
				while (md > 1) {
					for (int i = 1; i <= n; i++)
						if (p[i][md - 1]) goto fin;
					md--;
				}
			fin:
				pre = q.c;
			}
			if (v == l) {
				ans[q.id] = a[v];
				for (int i = md - 1; ~i; i--)
					if (deep[p[u][i]] > deep[l]) ans[q.id] += s[u][i], u = p[u][i];
				if (deep[u] > deep[v]) ans[q.id] += a[u];
			} else if (u == l) {
				ans[q.id] = a[u] + a[v];
				v = getFa(v, rest);
				if (v == q.v) v = getFa(v, q.c);
				for (int i = md - 1; ~i; i--)
					if (deep[p[v][i]] > deep[l]) ans[q.id] += s[v][i], v = p[v][i];
				if (deep[v] > deep[u]) ans[q.id] += a[v];
			} else {
				ans[q.id] = a[v];
				v = getFa(v, rest);
				if (v == q.v) v = getFa(v, q.c);
				for (int i = md - 1; ~i; i--)
					if (deep[p[u][i]] > deep[l]) ans[q.id] += s[u][i], u = p[u][i];
				for (int i = md - 1; ~i; i--)
					if (deep[p[v][i]] > deep[l]) ans[q.id] += s[v][i], v = p[v][i];
				if (deep[u] > deep[l]) ans[q.id] += a[u];
				if (deep[v] > deep[l]) ans[q.id] += a[v];
				if (p[u][0] == l || p[v][0] == l) ans[q.id] += a[l];
			}
		} else {
			if (v == l) {
				ans[q.id] = a[u] + a[v];
				for (u = getFa(u, q.c); deep[u] > deep[l]; u = getFa(u, q.c)) ans[q.id] += a[u];
			} else if (u == l) {
				ans[q.id] = a[u] + a[v];
				v = getFa(v, rest);
				if (deep[v] < deep[l] && v != q.v) ans[q.id] += a[v];
				for (v = getFa(v, q.c); deep[v] > deep[l]; v = getFa(v, q.c)) ans[q.id] += a[v];
			} else {
				ans[q.id] = a[u] + a[v];
				v = getFa(v, rest);
				if (deep[v] < deep[l] && v != q.v) ans[q.id] += a[v];
				for (u = getFa(u, q.c); deep[u] > deep[l]; u = getFa(u, q.c)) ans[q.id] += a[u];
				for (v = getFa(v, q.c); deep[v] > deep[l]; v = getFa(v, q.c)) ans[q.id] += a[v];
				if (u == l || v == l) ans[q.id] += a[l];
			}
		}
	}
	for (int i = 1; i < n; i++) pi(ans[i]), pc(10);
	rt();
}