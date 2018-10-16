#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
typedef long long lnt;
int t;
lnt l, r, k, c;
int main() {
	for (scanf("%d", &t); t; t--) {
		scanf("%lld%lld%lld", &l, &r, &k);
		c = 0;
		if (k == 0) {
			for (int i = 0; i <= 1; i++)
				if (l <= i && i <= r) printf("%d ", i), c++;
			puts(c ? "" : "None.");
		} else if (k == 1) {
			puts(l <= 1 && 1 <= r ? "1" : "None.");
		} else {
			for (lnt t = 1; t <= r;) {
				if (l <= t && t <= r) printf("%lld ", t), c++;
				if (t <= (r + k - 1) / k) {
					t *= k;
				} else {
					break;
				}
			}
			puts(c ? "" : "None.");
		}
	}
	return 0;
}