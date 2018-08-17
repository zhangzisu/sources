#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
inline int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
int n, m, k;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, x; i <= n; i++) {
		scanf("%d", &x);
		if (x % m) {
			x %= m;
			if (!k)
				k = x;
			else
				k = gcd(x, k);
		}
	}
	printf("%d\n", k ? (m - 1) / k + 1 : 1);
	return 0;
}