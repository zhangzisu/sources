#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 100010
int n, m;
struct edge {
	int u, v, w, id;
	inline edge(int u = 0, int v = 0, int w = 0, int id = 0) : u(u), v(v), w(w), id(id) {}
	inline friend bool operator<(const edge &a, const edge &b) {
		return a.w < b.w;
	}
} e[MAXN], t[MAXN];
int head[MAXN], to[MAXN << 1], id[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v, int i) {
	next[tot] = head[u], to[tot] = v, id[tot] = i, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, id[tot] = i, head[v] = tot++;
}
int p[MAXN], type[MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int vis[MAXN], stk[MAXN], dfn[MAXN], ins[MAXN], low[MAXN], dfsclk = 0, top = 0;
void dfs(int x, int fa) {
	dfn[x] = low[x] = ++dfsclk;
	ins[stk[++top] = x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (i == (fa ^ 1)) continue;
		if (dfn[to[i]]) {
			if (ins[to[i]]) low[x] = std::min(low[x], dfn[to[i]]);
		} else {
			dfs(to[i], i);
			low[x] = std::min(low[x], low[to[i]]);
			if (low[to[i]] > dfn[x])
				type[id[x]] = 2;
		}
	}
	if (low[x] == dfn[x]) {
		do {
			ins[stk[top]] = 0;
		} while (stk[top--] != x);
	}
}
std::vector<int> tmp;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w), e[i].id = i;
	for (int i = 1; i <= n; i++) p[i] = i;
	std::sort(e + 1, e + m + 1);
	memset(head, -1, sizeof(head));
	for (int i = 1, j = 0; i <= m; i++) {
		t[++j] = e[i];
		if (i == m || e[i].w != e[i + 1].w) {
			for (int k = 1; k <= j; k++) {
				int u = find(t[k].u), v = find(t[k].v);
				if (u == v) {
					type[t[k].id] = 1;
				} else {
					$(u, v, e[k].id);
					tmp.push_back(u);
					tmp.push_back(v);
				}
			}
			std::sort(tmp.begin(), tmp.end());
			tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
			for (auto x : tmp)
				if (!vis[x]) dfs(x, -1);
			for (int k = 1; k <= j; k++) {
				if (!type[t[k].id]) type[t[k].id] = 3;
				int u = find(t[k].u), v = find(t[k].v);
				if (u == v) continue;
				p[u] = v;
			}
			for (auto x : tmp) {
				head[x] = -1;
				dfn[x] = low[x] = ins[x] = 0;
			}
			tot = j = top = dfsclk = 0;
		}
	}
	for (int i = 1; i <= n; i++) puts(type[i] == 1 ? "none" : type[i] == 2 ? "any" : "at least one");
	return 0;
}