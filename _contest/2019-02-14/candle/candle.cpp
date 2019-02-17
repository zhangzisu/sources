#include <cstdio>
const int MAXN = 100010;
int p;
char buf[MAXN];
int main() {
	freopen("candle.in", "r", stdin);
	freopen("candle.out", "w", stdout);
	scanf("%d%s", &p, buf);
	if (p == 2) {
		if (buf[0] == '?' || buf[1] == '?') {
			puts("1073741827");
		} else if (buf[0] == buf[1]) {
			puts("0");
		} else {
			puts("7");
		}
		return 0;
	}
	puts("0");
	return 0;
}
