#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#define MAXN 150010
std::map<std::pair<int, int>, int> M;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], val[MAXN << 1], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
std::vector<int> values[MAXN], origins[MAXN];
int vis[MAXN], size[MAXN], f[MAXN], all, froot[MAXN], fdist[MAXN];
int getSize(int x, int p) {
	size[x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (vis[to[i]] || to[i] == p) continue;
		size[x] += getSize(to[i], x);
	}
	return size[x];
}
int getF(int x, int p) {
	f[x] = 0;
	int best = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (vis[to[i]] || to[i] == p) continue;
		int y = getF(to[i], x);
		f[x] = std::max(f[x], size[to[i]]);
		if (f[y] < f[best]) best = y;
	}
	f[x] = std::max(f[x], all - size[x]);
	if (f[x] < f[best]) best = x;
	return best;
}
void add(int root, int x, int p, int dist) {
	values[root].push_back(dist);
	M[std::make_pair(root, x)] = dist;
	for (int i = head[x]; ~i; i = next[i]) {
		if (vis[to[i]] || to[i] == p) continue;
		add(root, to[i], x, dist + val[i]);
	}
}
void ddd(int root, int x, int p, int dist) {
	origins[root].push_back(dist);
	if (x == root) fdist[root] = dist;
	for (int i = head[x]; ~i; i = next[i]) {
		if ((vis[to[i]] && to[i] != root) || to[i] == p) continue;
		ddd(root, to[i], x, dist + val[i]);
	}
}
void solve(int root, int pre, int real, int len) {
	vis[root] = 1;
	all = getSize(root, 0);
	froot[root] = pre;
	// printf("ROOT: %d, FROOT: %d\n", root, pre);
	values[root].push_back(0);
	for (int i = head[root]; ~i; i = next[i]) {
		if (!vis[to[i]]) add(root, to[i], root, val[i]);
	}
	if (pre && real) {
		ddd(root, real, pre, len);
	}
	for (int i = head[root]; ~i; i = next[i]) {
		if (!vis[to[i]]) {
			int next = getF(to[i], root);
			solve(next, root, to[i], val[i]);
		}
	}
}
int n, k;
inline int count(std::vector<int> &x, int y) {
	return std::upper_bound(x.begin(), x.end(), y) - x.begin();
}
inline int count(int x, int y) {
	int ret = count(values[x], y);
	int a = x, b = froot[x];
	while (b) {
		int delta = M[std::make_pair(b, x)];
		ret += count(values[b], y - delta) - count(origins[a], y - delta);
		b = froot[a = b];
	}
	return ret;
}
int main() {
	scanf("%d%d", &n, &k);
	memset(head, -1, sizeof(head));
	for (int i = 1, x, y, w; i < n; i++) {
		scanf("%d%d%d", &x, &y, &w);
		$(x, y, w);
	}
	f[0] = 0x3F3F3F3F;
	all = n;
	getSize(1, 0);
	solve(getF(1, 0), 0, 0, 0);
	for (int i = 1; i <= n; i++) {
		std::sort(values[i].begin(), values[i].end());
		std::sort(origins[i].begin(), origins[i].end());
		// printf("NODE %d, FROOT: %d, DROOT: %d\n", i, froot[i], fdist[i]);
	}
	for (int i = 1; i <= n; i++) {
		int l = 0, r = n * 10, ans = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (count(i, mid) > k)
				ans = mid, r = mid - 1;
			else
				l = mid + 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}