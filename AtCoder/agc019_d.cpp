#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2010
char buf[MAXN];
int n, a[MAXN], b[MAXN];
int main() {
	scanf("%s", buf + 1);
	n = strlen(buf + 1);
	for (int i = 1; i <= n; i++) a[0] |= (a[i] = buf[i] == '1');
	scanf("%s", buf + 1);
	for (int i = 1; i <= n; i++) b[0] |= (b[i] = buf[i] == '1');
	if (!b[0]) return puts(a[0] ? "-1" : "0"), 0;
	for (int d = 0; d < n; d++) {
		//
	}
	return 0;
}