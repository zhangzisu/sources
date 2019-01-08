#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
int n, m, q, p[MAXN << 1], ans;
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n + m; i++) p[i] = i;
	ans = n + m - 1;
	for (int x, y; q; q--) {
		scanf("%d%d", &x, &y);
		int X = find(x), Y = find(n + y);
		if (X == Y) continue;
		p[X] = Y;
		ans--;
	}
	printf("%d\n", ans);
	return 0;
}