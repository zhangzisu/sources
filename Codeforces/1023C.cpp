#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
int n, k, l, r;
char buf[MAXN];
int main() {
	scanf("%d%d%s", &n, &k, buf + 1);
	l = r = k / 2;
	for (int i = 1; i <= n; i++) {
		if (l && buf[i] == '(') putchar('('), l--;
		if (r && buf[i] == ')') putchar(')'), r--;
	}
	putchar(10);
	return 0;
}