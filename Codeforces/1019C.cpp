#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 1000010
int n, m, vis[MAXN];
std::vector<int> next[MAXN], a, b;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; i++) scanf("%d%d", &u, &v), next[u].push_back(v);
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			a.push_back(i);
			for (auto x : next[i]) vis[x] = 1;
		}
	}
	std::reverse(a.begin(), a.end());
	memset(vis, 0, sizeof(vis));
	for (auto x : a) {
		if (!vis[x]) {
			b.push_back(x);
			for (auto y : next[x]) vis[y] = 1;
		}
	}
	printf("%lu\n", b.size());
	for (auto x : b) printf("%d ", x);
	return puts(""), 0;
}