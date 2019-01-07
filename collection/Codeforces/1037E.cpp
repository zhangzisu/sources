#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#define MAXN 200010
int n, m, k, u[MAXN], v[MAXN], t[MAXN];
std::set<int> next[MAXN], p;
inline void remove(int x) {
	if ((int)next[x].size() < k && p.erase(x)) {
		for (auto y : next[x]) {
			next[y].erase(x);
			remove(y);
		}
		next[x].clear();
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", u + i, v + i);
		next[u[i]].insert(v[i]);
		next[v[i]].insert(u[i]);
	}
	for (int i = 1; i <= n; i++) p.insert(i);
	for (int i = 1; i <= n; i++) remove(i);
	for (int i = m; i; i--) {
		t[i] = p.size();
		if (p.count(v[i]) && p.count(u[i])) {
			next[v[i]].erase(u[i]);
			next[u[i]].erase(v[i]);
			remove(u[i]);
			remove(v[i]);
		}
	}
	for (int i = 1; i <= m; i++) printf("%d\n", t[i]);
	return 0;
}
