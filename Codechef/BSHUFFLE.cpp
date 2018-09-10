#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#define MAXN 100
int n, t[MAXN], m;
int main() {
	scanf("%d", &n);
	if (n & 1) {
		for (int i = 2; i <= n / 2; i++) printf("%d ", i);
		printf("%d ", 1);
		printf("%d ", (n + 3) / 2);
		for (int i = n / 2 + 1; i <= n; i++)
			if (i != (n + 3) / 2) t[++m] = i;
		for (int i = 2; i <= m; i++) printf("%d ", t[i]);
		printf("%d ", t[1]);
		puts("");
	} else {
		for (int i = 2; i <= n / 2; i++) printf("%d ", i);
		printf("%d ", 1);
		for (int i = n / 2 + 2; i <= n; i++) printf("%d ", i);
		printf("%d ", n / 2 + 1);
		puts("");
	}
	printf("%d ", n);
	for (int i = 1; i < n; i++) printf("%d%c", i, " \n"[i == n - 1]);
	return 0;
}