#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define lowbit(x) (x & -x)
#define N 2000000
int n, a[N], b[N], c[N];
inline void add(int x, int v) {
	for (; x <= n; x += lowbit(x)) b[x] += v;
}
inline int qry(int x) {
	int v = 0;
	for (; x; x -= lowbit(x)) v += b[x];
	return v;
}
__int128 ans = 0;
void print(__int128 d) {
	if (d == 0) return;
	print(d / 10);
	putchar(d % 10 + 48);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), c[i] = i;
	std::sort(c + 1, c + n + 1, [](int x, int y) { return (a[x] <= 0 && a[y] <= 0) ? (x > y) : (a[x] >= 0 && a[y] >= 0) ? (x < y) : (a[x] < a[y]); });
	for (int i = 1; i <= n; i++) add(i, 1);
	for (int i = 1; i <= n; i++) ans += (__int128)qry(c[i]) * a[c[i]], add(c[i], -1);
	if (ans < 0)
		putchar('-'), ans = -ans;
	else if (ans == 0)
		putchar('0');
	print(ans);
	puts("");
	return 0;
}