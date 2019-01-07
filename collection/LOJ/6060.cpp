#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
typedef long long lnt;
int n;
lnt a[MAXN], base[61], ans, sum;
inline void insert(lnt x) {
	for (int i = 60; ~i; i--) {
		if (!((sum >> i) & 1) && ((x >> i) & 1)) {
			if (base[i]) {
				x ^= base[i];
			} else {
				base[i] = x;
                return;
			}
		}
	}
	for (int i = 60; ~i; i--) {
		if (((sum >> i) & 1) && ((x >> i) & 1)) {
			if (base[i]) {
				x ^= base[i];
			} else {
				base[i] = x;
                return;
			}
		}
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), sum ^= a[i];
	for (int i = 1; i <= n; i++) insert(a[i]);
	lnt mask = ((1LL << 61) - 1) ^ sum;
	for (int i = 60; ~i; i--)
		if (!((sum >> i) & 1) && ((ans ^ base[i]) & mask) > (ans & mask))
			ans ^= base[i];
	for (int i = 60; ~i; i--)
		if (((sum >> i) & 1) && (ans ^ base[i]) < ans)
			ans ^= base[i];
	printf("%lld\n", ans);
	return 0;
}