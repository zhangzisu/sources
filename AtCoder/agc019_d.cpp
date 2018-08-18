#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2010
char buf[MAXN];
int n, a[MAXN], b[MAXN], c[MAXN], A, B, ans = 0x3F3F3F3F;
inline int _sum(int l, int r) {
	return c[r] - (l ? c[l - 1] : 0);
}
inline int sum(int l, int r) {
	return l <= r ? _sum(l, r) : _sum(l, n - 1) + _sum(0, r);
}
inline void solve0() {
	c[0] = b[0];
	for (int i = 1; i < n; i++) c[i] = c[i - 1] + b[i];

	for (int d = 0; d < n; d++) {
		int tmp = 0;
		for (int i = 0; i < n; i++)
			if (a[i] != b[(i + d) % n]) tmp++;
		ans = std::min(ans, tmp + d + n);
		register int l = 0, r = std::min(n / 2, n - d);
		while (l <= r) {
			int mid = (l + r) >> 1;
			for (int i = 0; i < n; i++) {
				if (a[i] != b[(i + d) % n]) {
					if (!sum(i, (i + d + mid) % n)) goto fail;
				}
			}
			ans = std::min(ans, tmp + d + mid * 2);
			r = mid - 1;
			continue;
		fail:
			l = mid + 1;
		}
	}
}
inline void solve1() {
	c[0] = b[0];
	for (int i = 1; i < n; i++) c[i] = c[i - 1] + b[i];

	for (int d = 0; d < n; d++) {
		int tmp = 0;
		for (int i = 0; i < n; i++)
			if (a[i] != b[(i + d) % n]) tmp++;
		ans = std::min(ans, tmp + d + n);
		register int l = 0, r = std::min(n / 2, n - d);
		while (l <= r) {
			int mid = (l + r) >> 1;
			for (int i = 0; i < n; i++) {
				if (a[i] != b[(i + d) % n]) {
					if (!sum((i - mid + n) % n, (i + d) % n)) goto fail;
				}
			}
			ans = std::min(ans, tmp + d + mid * 2);
			r = mid - 1;
			continue;
		fail:
			l = mid + 1;
		}
	}
}
int main() {
	scanf("%s", buf);
	n = strlen(buf);
	for (int i = 0; i < n; i++) A |= (a[i] = buf[i] == '1');
	scanf("%s", buf);
	for (int i = 0; i < n; i++) B |= (b[i] = buf[i] == '1');
	if (!B) return puts(A ? "-1" : "0"), 0;
	solve0();
	solve1();
	printf("%d\n", ans);
	std::reverse(a, a + n);
	std::reverse(b, b + n);
	solve0();
	solve1();
	printf("%d\n", ans);
	return 0;
}