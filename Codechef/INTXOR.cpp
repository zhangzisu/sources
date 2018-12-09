#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 50010
int T, n, a[MAXN];
inline int query(int i, int j, int k) {
	printf("1 %d %d %d\n", i, j, k);
	fflush(stdout);
	int res;
	scanf("%d", &res);
	return res;
}
int tmp[MAXN], pre[MAXN][3], nxt[MAXN][3];
inline void solve31(int n, int offset) {
	int all = 0;
	memset(pre, 0, sizeof(pre));
	memset(nxt, 0, sizeof(nxt));
	for (int i = 1; i <= n; i++) all ^= (tmp[i] = query(i + offset - 1, i % n + offset, (i + 1) % n + offset));
	for (int i = 1; i <= n; i++) {
		memcpy(pre[i], pre[i - 1], sizeof(int) * 3);
		pre[i][i % 3] ^= tmp[i];
	}
	for (int i = n; i >= 1; i--) {
		memcpy(nxt[i], nxt[i + 1], sizeof(int) * 3);
		nxt[i][i % 3] ^= tmp[i];
	}
	for (int i = 1; i <= n; i++) {
		a[i + offset - 1] = all ^ pre[i][i % 3] ^ nxt[i][(i + 1) % 3] ^ tmp[i];
	}
}
inline void solve5(int offset) {
	int x123 = query(offset, offset + 1, offset + 2);
	int x245 = query(offset + 1, offset + 3, offset + 4);
	int x345 = query(offset + 2, offset + 3, offset + 4);
	a[offset] = x123 ^ x245 ^ x345;
	int x134 = query(offset, offset + 2, offset + 3);
	int x125 = query(offset, offset + 1, offset + 4);
	int x23 = x123 ^ a[offset];
	int x34 = x134 ^ a[offset];
	int x25 = x125 ^ a[offset];
	a[offset + 3] = x245 ^ x25;
	a[offset + 2] = x34 ^ a[offset + 3];
	a[offset + 1] = x23 ^ a[offset + 2];
	a[offset + 4] = x25 ^ a[offset + 1];
}
int main() {
	scanf("%d", &T);
	for (; T; T--) {
		scanf("%d", &n);
		if (n % 3 == 1) {
			solve31(n, 1);
		} else if (n % 3 == 2) {
			solve31(n / 2, 1);
			solve31(n / 2, n / 2 + 1);
		} else {
			solve5(1);
			solve31(n - 5, 6);
		}
		printf("%d", 2);
		for (int i = 1; i <= n; i++) printf(" %d", a[i]);
		puts("");
		fflush(stdout);
		scanf("%*d");
	}
}