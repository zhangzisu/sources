#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, c;
inline int fuck(int x) {
	printf("1 %d\n", x);
	fflush(stdout);
	int y;
	scanf("%d", &y);
	return y;
}
inline void quit(int ans) {
	printf("3 %d\n", ans);
	fflush(stdout);
	exit(0);
}
int main() {
	scanf("%d%d", &n, &c);
	int now;
	for (now = 1; now + 500 <= n; now += 500) {
		if (fuck(now + 500)) {
			puts("2");
			fflush(stdout);
			break;
		}
	}
	for (; now <= n; now++)
		if (fuck(now)) quit(now);
	quit(n);
	return 0;
}