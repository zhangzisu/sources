#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2000010
inline int convert(char ch) {
	return ch == 'A' ? 0 : ch == 'G' ? 1 : ch == 'U' ? 2 : 3;
}
int ch[2][MAXN][4], in[MAXN], out[MAXN], dfsclk = 0, cnt[2] = {1, 1};
int tmp[MAXN][2], map[MAXN], tim[MAXN];
inline void insert(const char *s) {
	int n = strlen(s);
	for (int i = 0; i < n; i++) tmp[i][0] = tmp[n - i - 1][1] = convert(s[i]);
	int p[2] = {1, 1};
	for (int d = 0; d < 2; d++) {
		for (int i = 0; i < n; i++) {
			int &nxt = ch[d][p[d]][tmp[i][d]];
			if (!nxt) nxt = ++cnt[d];
			p[d] = nxt;
		}
	}
	map[p[1]] = p[0];
	tim[p[1]]++;
}
inline int eval(int d, const char *s) {
	int p = 1, n = strlen(s);
	for (int i = 0;i < n; i++) {
		if (!(p = ch[d][p][convert(s[d ? n - i - 1 : i])])) return 0;
	}
	return p;
}
void dfs(int x) {
	in[x] = ++dfsclk;
	for (int i = 0; i < 4; i++) {
		if (!ch[0][x][i]) continue;
		dfs(ch[0][x][i]);
	}
	out[x] = dfsclk;
}
int head[MAXN], to[MAXN], id[MAXN], next[MAXN], tot = 0;
inline void $(int x, int y, int i) {
	next[tot] = head[x], to[tot] = y, id[tot] = i, head[x] = tot++;
}
int n, m, ans[MAXN], size[MAXN], prf[MAXN];
char buf[MAXN];
void pre(int x) {
	size[x] = 1;
	for (int i = 0, y; i < 4; i++) {
		if (!(y = ch[1][x][i])) continue;
		pre(y);
		size[x] += size[y];
		if (size[y] > size[prf[x]]) prf[x] = y;
	}
}
int bit[MAXN];
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int y) {
	for (; x <= cnt[0]; x += lowbit(x)) bit[x] += y;
}
inline int qry(int x) {
	int y = 0;
	for (; x; x -= lowbit(x)) y += bit[x];
	return y;
}
void merge(int x) {
	if (map[x]) add(in[map[x]], tim[x]);
	for (int i = 0, y; i < 4; i++) {
		if (!(y = ch[1][x][i])) continue;
		merge(y);
	}
}
void clear(int x) {
	if (map[x]) add(in[map[x]], -tim[x]);
	for (int i = 0, y; i < 4; i++) {
		if (!(y = ch[1][x][i])) continue;
		clear(y);
	}
}
void solve(int x) {
	// printf("S %d\n", x);
	for (int i = 0, y; i < 4; i++) {
		if (!(y = ch[1][x][i]) || y == prf[x]) continue;
		solve(y);
		clear(y);
	}
	if (prf[x]) solve(prf[x]);
	for (int i = 0, y; i < 4; i++) {
		if (!(y = ch[1][x][i]) || y == prf[x]) continue;
		merge(y);
	}
	if (map[x]) add(in[map[x]], tim[x]);
	for (int i = head[x]; ~i; i = next[i]) {
		ans[id[i]] = qry(out[to[i]]) - qry(in[to[i]] - 1);
	}
}
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", buf);
		insert(buf);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%s", buf);
		int l = eval(0, buf);
		scanf("%s", buf);
		int r = eval(1, buf);
		if (l && r) $(r, l, i);
		// printf("l %d r %d\n", l, r);
	}
	dfs(1);
	// for (int i = 1; i <= cnt[0]; i++) printf("%d: %d - %d\n", i, in[i], out[i]);
	pre(1);
	solve(1);
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
}