#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int t, k;
long long p, b;
int main() {
	for (scanf("%d", &t); t; t--) {
		scanf("%d%lld", &k, &p);
		if (p % 2 == 0) {
			puts("0");
			continue;
		}
		b = p;
		for (long long x; p; p -= x + 1) {
			x = 0;
			for (;;) {
				if (x * 2 + 1 < p) {
					x = x * 2 + 1;
				} else if (x * 2 + 1 == p) {
					goto succ;
				} else {
					break;
				}
			}
		}
	succ:;
		printf("%lld\n", p == b ? (p - 1) / 2 : p);
	}
	return 0;
}