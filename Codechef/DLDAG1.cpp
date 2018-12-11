#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <string>
#include <vector>
#define MAXN 1000010
int head[MAXN], to[MAXN], next[MAXN], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
int n, m, d[MAXN];
std::stack<int> Q;
inline void remove(int x) {
	for (int i = head[x]; ~i; i = next[i]) {
		if (!--d[to[i]]) {
			Q.push(to[i]);
		}
	}
}
std::vector<std::pair<int, int>> ans;
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		$(v, u);
		d[u]++;
	}
	for (int i = 1; i <= n; i++) {
		if (!d[i]) Q.push(i);
	}
	for (int x, y; Q.size();) {
		x = Q.top();
		Q.pop();
		if ((int)Q.size() > 1) {
			y = Q.top();
			Q.pop();
			ans.emplace_back(x, y);
			remove(x);
			remove(y);
		} else {
			ans.emplace_back(x, 0);
			remove(x);
		}
	}
	printf("%llu\n", ans.size());
	for (auto s : ans) {
		if (s.second) {
			printf("2 %d %d\n", s.first, s.second);
		} else {
			printf("1 %d\n", s.first);
		}
	}
	return 0;
}