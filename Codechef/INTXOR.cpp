#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 50010
int T, n, a[MAXN];
inline int query(int i, int j, int k, int offset) {
	printf("1 %d %d %d\n", i + offset - 1, j + offset - 1, k + offset - 1);
	fflush(stdout);
	int res;
	scanf("%d", &res);
	return res;
}
int tmp[MAXN];
inline void solve31(int n, int offset) {
	int *a = ::a + offset - 1;
	for (int i = 1; i <= n - 2; i++) tmp[i] = query(i, i + 1, i + 2, offset);
	tmp[n - 1] = query(1, n - 1, n, offset);
	tmp[n] = query(1, 2, n, offset);
	int sum = 0;
	for (int i = 1; i <= n; i++) sum ^= tmp[i];
	a[1] = a[2] = sum;
	for (int i = 2; i <= n; i += 3) a[1] ^= tmp[i];
	for (int i = 3; i <= n; i += 3) a[2] ^= tmp[i];
	for (int i = 1; i <= n - 2; i++) a[i + 2] = tmp[i] ^ a[i] ^ a[i + 1];
}
inline void solve5(int offset) {
	int *a = ::a + offset - 1;
	int x123 = query(1, 2, 3, offset);
	int x245 = query(2, 4, 5, offset);
	int x345 = query(3, 4, 5, offset);
	a[1] = x123 ^ x245 ^ x345;
	int x134 = query(1, 3, 4, offset);
	int x125 = query(1, 2, 5, offset);
	int x23 = x123 ^ a[1];
	int x34 = x134 ^ a[1];
	int x25 = x125 ^ a[1];
	a[4] = x245 ^ x25;
	a[3] = x34 ^ a[4];
	a[2] = x23 ^ a[3];
	a[5] = x25 ^ a[2];
}
int main() {
	scanf("%d", &T);
	for (; T; T--) {
		scanf("%d", &n);
		if (n % 3 == 1) {
			solve31(n, 1);
		} else if (n % 3 == 2) {
			solve31(4, 1);
			solve31(n - 4, 5);
		} else {
			solve5(1);
			solve31(n - 5, 6);
		}
		printf("2");
		for (int i = 1; i <= n; i++) printf(" %d", a[i]);
		puts("");
		fflush(stdout);
		scanf("%*d");
	}
}