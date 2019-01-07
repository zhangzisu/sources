#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 110
int n, m, x[MAXN], f[2][MAXN * MAXN * 2], ans;
const int prefix = MAXN * MAXN;
int main(int argc, char const *argv[]) {
	scanf("%d%d", &n, &m);
	memset(f, 0x80, sizeof(f));
	f[0][prefix] = 0;
	for (int i = 1, x; i <= n; i++) {
		int now = i & 1, pre = now ^ 1;
		memset(f[now], 0, sizeof(f[now]));
		scanf("%d", &x);
		for (int _j = -10000; _j <= 10000; _j++) {
			int j = _j + prefix;
			f[now][j] = f[pre][j];
			if (_j + x <= 10000) f[now][j] = std::max(f[now][j], f[pre][j + x] + x);
			if (_j - x >= -10000) f[now][j] = std::max(f[now][j], f[pre][j - x] + x);
		}
	}
	for (int i = -m; i <= m; i++) ans = std::max(ans, f[n & 1][i + prefix]);
	printf("%d\n", ans);
	return 0;
}
