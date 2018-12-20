#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
typedef long long lnt;
int n, s;
char buf[MAXN];
lnt ans = 0;
int main() {
	scanf("%s", buf + 1);
	n = strlen(buf + 1);
	for (int i = 1; i <= n; i++) {
		if (buf[i] == 'W') {
			ans += s;
		} else {
			s++;
		}
	}
	printf("%lld\n", ans);
	return 0;
}