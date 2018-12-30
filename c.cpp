#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000
int k, n, a[MAXN][MAXN];
int main() {
	scanf("%d", &k);
	if (k == 1) {
		puts("1");
		puts("1");
		return 0;
	}
	if (k == 2) {
		puts("2");
		puts("1 1");
		puts("2 2");
		return 0;
	}
	n = ((k - 1) / 4 + 1) * 2;
	printf("%d\n", n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int x = (i & 1 ? n : 0) + (i + j) % n;
			if (x >= k) x -= n;
			printf("%d ", x + 1);
		}
        puts("");
	}
	return 0;
}