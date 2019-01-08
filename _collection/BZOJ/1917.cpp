#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 50010
int n, h[MAXN], ans, res[MAXN];
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int rest[MAXN];
void dfs(int x, int fa) {
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		dfs(to[i], x);
		int t = std::min(h[x], h[to[i]]);
		ans += t << 1;
		h[x] -= t;
		h[to[i]] -= t;
		if (h[to[i]]) rest[x] = to[i];
	}
}
void solve(int x, int fa) {
	res[x] = ans;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		if (h[x]) {
			ans++;
			solve(to[i], x);
			ans--;
		} else if (rest[to[i]]) {
			h[rest[to[i]]]--;
			ans++;
			solve(to[i], x);
			h[rest[to[i]]]++;
			ans--;
		} else {
			ans--;
			h[to[i]]++;
			solve(to[i], x);
			ans++;
			h[to[i]]--;
		}
	}
}
int main() {
	for (int i = scanf("%d", &n); i <= n; i++) scanf("%d", &h[i - 1]);
	memset(head, -1, sizeof(head));
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v), $(u, v);
		ans += 2;
		h[u]--;
		h[v]--;
	}
	dfs(0, -1);
	solve(0, -1);
	for (int i = 0; i < n; i++) printf("%d\n", res[i]);
	return 0;
}