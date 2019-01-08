#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define MAXN 300000
int n, m, k, x[MAXN], id[MAXN], ans[MAXN], sum[MAXN];
int main() {
	scanf("%d", &n);
	m = n * n;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x[i]);
		id[i] = ans[x[i]] = i;
	}
	std::sort(id + 1, id + n + 1, [](int a, int b) { return x[a] < x[b]; });
	for (int i = 1, cur = 1; i <= n; i++) {
		for (int j = 1; j < id[i]; j++) {
			while (ans[cur]) cur++;
			ans[cur] = id[i];
		}
		if (cur > x[id[i]]) return puts("No"), 0;
	}
	for (int i = n, cur = m; i >= 1; i--) {
		for (int j = id[i] + 1; j <= n; j++) {
			while (ans[cur]) cur--;
			ans[cur] = id[i];
		}
		if (cur < x[id[i]]) return puts("No"), 0;
	}
	puts("Yes");
	for (int i = 1; i <= m; i++) printf("%d%c", ans[i], " \n"[i == m]);
	return 0;
}
