#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 110
typedef long long lnt;
int n, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
std::queue<int> Q;
int vis[MAXN];
inline int farthest(int s) {
	memset(vis, 0, sizeof(vis));
	vis[s] = 1;
	Q.push(s);
	int t = s;
	while (Q.size()) {
		int x = Q.front();
		Q.pop();
		t = x;
		for (int i = head[x]; ~i; i = next[i]) {
			if (!vis[to[i]]) {
				vis[to[i]] = 1;
				Q.push(to[i]);
			}
		}
	}
	return t;
}
int path[MAXN], plen = 0;
bool dfs(int s, int t, int fa) {
	if (s == t) return path[++plen] = s, 1;
	for (int i = head[s]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		if (dfs(to[i], t, s)) return path[++plen] = s, 1;
	}
	return 0;
}
int count[MAXN], maxdeep;
void fill(int x, int deep, int fa) {
	int sc = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		sc++;
		fill(to[i], deep + 1, x);
	}
	if (sc) {
		count[deep] = std::max(count[deep], sc);
		maxdeep = std::max(maxdeep, deep);
	}
}
int bfn[MAXN], fa[MAXN], bl[MAXN], br[MAXN], dl[MAXN], dr[MAXN], deep[MAXN], bfsclk = 0;
inline void bfs(int x) {
	memset(vis, 0, sizeof(vis));
	vis[x] = deep[x] = 1;
	Q.push(x);
	while (Q.size()) {
		int x = Q.front();
		Q.pop();
		bfn[x] = ++bfsclk;
		for (int i = head[x]; ~i; i = next[i]) {
			if (!vis[to[i]]) {
				vis[to[i]] = 1;
				fa[to[i]] = x;
				deep[to[i]] = deep[x] + 1;
				Q.push(to[i]);
			}
		}
	}
	std::fill(bl + 1, bl + n + 1, n + 1);
	std::fill(dl + 1, dl + n + 1, n + 1);
	std::fill(br + 1, br + n + 1, 0);
	std::fill(dr + 1, dr + n + 1, 0);
	for (int i = 1; i <= n; i++) {
		bl[fa[i]] = std::min(bl[fa[i]], bfn[i]);
		br[fa[i]] = std::max(br[fa[i]], bfn[i]);
		dl[deep[i]] = std::min(dl[deep[i]], bfn[i]);
		dr[deep[i]] = std::max(dr[deep[i]], bfn[i]);
	}
}
int max[MAXN << 2];
void set(int n, int l, int r, int p, int v) {
	if (l == r) return max[n] = v, void();
	int mid = (l + r) >> 1;
	p <= mid ? set(n << 1, l, mid, p, v), set(n << 1 | 1, mid + 1, r, p, v);
	max[n] = std::max(max[n << 1], max[n << 1 | 1]);
}
int query(int n, int l, int r, int L, int R) {
	if (l == L && r == R) return max[n];
	int mid = (l + r) >> 1;
	if (R <= mid) return query(n << 1, l, mid, L, R);
	if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R);
	return std::max(query(n << 1, l, mid, L, mid), query(n << 1 | 1, mid + 1, r, mid + 1, R));
}
void build(int x, int fa) {
	int sc = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		build(to[i], x);
		sc++;
	}
	set(1, 1, n, bfn[x], sc);
}
lnt cao(int x, int fa) {
	int d = deep[x];
    
}
int main() {
	memset(head, -1, sizeof(head));
	for (int i = scanf("%d", &n), u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
	int x = farthest(1);
	int y = farthest(x);
	dfs(x, y, 0);
	printf("%d ", (plen + 1) / 2);
	if (plen & 1) {
		int x = path[plen / 2 + 1];
		fill(x, 1, 0);
		lnt ans = 1;
		for (int i = 1; i <= maxdeep; i++) ans *= count[i];
		build(x, 0);
		for (int j = head[x]; ~j; j = next[j]) {
			memset(count, 0, sizeof(count));
			maxdeep = 0;
			fill(x, 1, to[j]);
			fill(to[j], 1, x);
			lnt tmp = 2;
			for (int i = 1; i <= maxdeep; i++) tmp *= count[i];
			ans = std::min(ans, tmp);
		}
		printf("%lld\n", ans);
	} else {
		int u = path[plen / 2];
		int v = path[plen / 2 + 1];
		fill(u, 1, v);
		fill(v, 1, u);
		lnt ans = 2;
		for (int i = 1; i <= maxdeep; i++) ans *= count[i];
		printf("%lld\n", ans);
	}
	return 0;
}