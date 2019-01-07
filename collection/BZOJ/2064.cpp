#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
inline int lowbit(int x) { return x & -x; }
int n1, n2, n, sum[1 << 20], f[1 << 20];
int main() {
	scanf("%d", &n1);
	for (int i = 0, x; i < n1; i++) scanf("%d", &x), sum[1 << i] = x;
	scanf("%d", &n2);
	for (int i = 0, x; i < n2; i++) scanf("%d", &x), sum[1 << (i + n1)] = -x;
	n = n1 + n2;
	for (int d = 1; d < (1 << n); d++) {
		sum[d] = sum[lowbit(d)] + sum[d - lowbit(d)];
		for (int i = 0; i < n; i++)
			if ((d >> i) & 1) f[d] = std::max(f[d], f[d - (1 << i)]);
		if (!sum[d]) f[d]++;
	}
	printf("%d\n", n - 2 * f[(1 << n) - 1]);
	return 0;
}