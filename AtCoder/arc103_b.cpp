#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
typedef long long lnt;
int n, x[MAXN], y[MAXN], flag;
lnt pw2[MAXN];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]);
	flag = (x[1] + y[1]) & 1;
	for (int i = 2; i <= n; i++) {
		if (((x[i] + y[i]) ^ flag) & 1) {
			puts("-1");
			return 0;
		}
	}
	if (flag) {
		puts("39");
	} else {
		puts("40");
		printf("1 ");
	}
	pw2[0] = 1;
	for (int i = 1; i < 39; i++) pw2[i] = pw2[i - 1] << 1;
	for (int i = 38; ~i; i--) printf("%lld%c", pw2[i], " \n"[!i]);
	for (int i = 1; i <= n; i++) {
		lnt x = ::x[i], y = ::y[i];
		if (!flag) {
			putchar('U');
			y--;
		}
		for (int j = 38; ~j; j--) {
			if (y <= x) {
				if (y <= -x) {
					putchar('D');
					y += pw2[j];
				} else {
					putchar('R');
					x -= pw2[j];
				}
			} else {
				if (y <= -x) {
					putchar('L');
					x += pw2[j];
				} else {
					putchar('U');
					y -= pw2[j];
				}
			}
		}
		putchar(10);
        fprintf(stderr, "(%lld, %lld)\n", x, y);
	}
	return 0;
}
