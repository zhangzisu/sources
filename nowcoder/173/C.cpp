#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, m, k, as = 1, at = 0, val;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	int all = (1 << n) - 1;
	if (__builtin_popcount(k + 1) != 1 && __builtin_popcount(all - k + 1) != 1) {
		return puts("-1"), 0;
	}
	val = k;
	if (__builtin_popcount(k + 1) != 1) std::swap(as, at), val = all - k;
	for (int i = 1; i < (1 << n); i++) {
		if (i & (~val)) {
			printf("%d", at);
		} else {
			printf("%d", as);
		}
	}
	puts("");
	return 0;
}