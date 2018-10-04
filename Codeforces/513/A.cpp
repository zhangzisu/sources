#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, a, b;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%1d", &x);
		if (x == 8) a++;
	}
	int ret = 0;
	for (int i = 1; i <= a; i++) {
		ret = std::max(ret, std::min(i, (n - i) / 10));
	}
	printf("%d\n", ret);
	return 0;
}