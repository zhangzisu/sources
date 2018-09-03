#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 100010
int n, ans, f[MAXN];
std::vector<int> next[MAXN];
void gao(int x, int fa) {
	int tmp = 0, all = 0;
	for (int y : next[x])
		if (y != fa) gao(y, x), tmp |= all & f[y], all |= f[y];
	if (!all) {
		f[x] = 1;
		ans = std::max(ans, 1);
	} else {
		int count = 0;
		while (((1 << count) < tmp) || ((all >> count) & 1)) count++;
		f[x] = (all >> count << count) | (1 << count);
		ans = std::max(ans, count);
	}
}
int main() {
	scanf("%d", &n);
	for (int u, v, i = 1; i < n; i++) scanf("%d%d", &u, &v), next[u].push_back(v), next[v].push_back(u);
	gao(1, 0);
	printf("%d\n", ans);
	return 0;
}