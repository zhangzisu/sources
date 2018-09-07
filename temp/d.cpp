#include <algorithm>
#include <cstdio>

const long long MAXL = 60;

struct LinearBasis {
	long long a[MAXL + 1];
	LinearBasis() {
		std::fill(a, a + MAXL + 1, 0);
	}
	void insert(long long t) {
		for (long long j = MAXL; j >= 0; j--) {
			if (!(t & (1ll << j))) continue;
			if (a[j])
				t ^= a[j];
			else {
				for (long long k = 0; k < j; k++)
					if (t & (1ll << k)) t ^= a[k];
				for (long long k = j + 1; k <= MAXL; k++)
					if (a[k] & (1ll << j)) a[k] ^= t;
				a[j] = t;
				return;
			}
		}
	}
} lb;
long long n;
int main() {
	scanf("%lld", &n);
	for (long long i = 1, x; i <= n; i++) {
		scanf("%lld", &x);
		lb.insert(x);
	}
	for (long long x, y = scanf("%lld", &n); n; n--) {
		scanf("%lld%lld", &x, &y);
		x ^= y;
		for (long long i = MAXL; ~i; i--) {
			if ((x >> i) & 1) {
				x ^= lb.a[i];
			}
		}
		puts(x ? "NO" : "YES");
	}
	return 0;
}