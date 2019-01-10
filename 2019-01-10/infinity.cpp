#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2010
int n, ans = 0;
char buf[MAXN];
int main() {
	freopen("infinity.in", "r", stdin);
	freopen("infinity.out", "w", stdout);
	scanf("%s", buf + 1);
	n = strlen(buf + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			int len = j - i + 1;
			for (int k = j + 1; k <= j + len; k++) {
				if (k <= n && buf[k] != buf[j - (k - j) + 1]) goto fail;
				buf[k] = buf[j - (k - j) + 1];
			}
			len *= 2;
			for (int k = i + len, cur = 0; k <= n; k++) {
				if (buf[k] != buf[i + cur]) goto fail;
				if (++cur >= len) cur = 0;
			}
			for (int k = i - 1, cur = 0; k >= 1; k--) {
				if (buf[k] != buf[i + len - 1 - cur]) goto fail;
				if (++cur >= len) cur = 0;
			}
			ans++;
		fail:;
		}
	}
	printf("%d\n", ans - 1);
}
