#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
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
inline int $() {
	register int x = 0;
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 100010
int n, k, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int id[MAXN], fa[MAXN], f[MAXN], g[MAXN], dfsclk;
void dfs(int x) {
	id[++dfsclk] = x;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x]) continue;
		fa[to[i]] = x;
		dfs(to[i]);
	}
}
inline void dp() {
	for (int i = n, x; i >= 1; i--) {
		x = id[i];
		int max1 = 0, max2 = 0;
		f[x] = g[x] = 0;
		for (int i = head[x]; ~i; i = next[i]) {
			if (to[i] == fa[x]) continue;
			f[x] += f[to[i]];
			if (g[to[i]] >= max1) {
				max2 = max1, max1 = g[to[i]];
			} else if (g[to[i]] > max2) {
				max2 = g[to[i]];
			}
		}
		if (max1 + max2 + 1 >= k) {
			f[x] = f[x] + 1;
			g[x] = 0;
		} else {
			g[x] = max1 + 1;
		}
	}
}
int max[MAXN], m;
int main() {
	clock_t start = clock();
	n = $();
	memset(head, -1, sizeof(head));
	for (int i = 1; i < n; i++) $($(), $());
	for (m = 1; m * m < n;) m++;
	dfs(1);
	fprintf(stderr, "init: %ld\n", clock() - start);
	start = clock();
	for (int i = 1; i <= m; i++) k = i, dp(), $(f[1]), pc(10);
	fprintf(stderr, "dp1: %ld\n", clock() - start);
	start = clock();
	max[0] = n;
	for (int i = 1; i <= m; i++) {
		register int l = 1, r = max[i - 1];
		while (l <= r) {
			k = (l + r) >> 1;
			dp();
			if (f[1] >= i) {
				max[i] = k;
				l = k + 1;
			} else {
				r = k - 1;
			}
		}
	}
	fprintf(stderr, "dp2: %ld\n", clock() - start);
	start = clock();
	for (int i = m + 1; i <= n; i++) {
		int l = 1, r = m, ans = 0;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (max[mid] >= i) {
				ans = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		$(ans);
		pc(10);
	}
	fprintf(stderr, "calc ans: %ld\n", clock() - start);
	start = clock();
	rt();
}