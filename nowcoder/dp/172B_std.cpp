#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int l, r, L, R;
inline int gao(int x) {
	int ret = 1;
	while (x) ret *= x % 10, x /= 10;
	return ret;
}
inline int in(int x, int l, int r) {
	return x >= l && x <= r;
}
int main() {
	scanf("%d%d%d%d", &l, &r, &L, &R);
	int ans = 0;
	for (int i = l; i <= r; i++) ans += in(gao(i), L, R);
	printf("%d\n", ans);
	return 0;
}