#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#define MAXN 200010
int n, ans, a[MAXN], vis[MAXN];
std::map<int, std::vector<int>> M;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		M[a[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		if (vis[i]) continue;
		M.erase(a[i]);
		for (int j = 1; j - a[i] <= 1000000000; j <<= 1) {
			if (M.count(j - a[i])) {
				ans++;
				auto &v = M[j - a[i]];
				vis[v.back()] = 1;
				v.pop_back();
				if (v.empty()) M.erase(j - a[i]);
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}