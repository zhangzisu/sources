#include <cassert>
#include <cstdio>
int n, m, a[1000];
inline int fuck(int x, int y) {
	int z = 1;
	for (; y; y >>= 1) {
		if (y & 1) z = 1LL * z * x % m;
		x = 1LL * x * x % m;
	}
	return z;
}
int main() {
	scanf("%d%d", &m, &n);
	for (int i = n; i >= 0; i--) scanf("%d", &a[i]);
	for (int d = 0; d < m; d++) {
		int tmp = 0;
		for (int i = 0, x = 1; i <= n; i++, x = 1LL * x * d % m) {
			tmp = (tmp + 1LL * x * a[i] % m) % m;
		}
		assert(tmp == 0);
	}
	return 0;
}