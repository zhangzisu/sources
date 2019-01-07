#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 10010
int n, a[MAXN], c1, c2, sg;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		if (a[i] <= 1) {
			i--, n--;
			continue;
		}
		if (a[i] & 1) {
			c1++;
			sg ^= (a[i] - 1) / 2;
		} else {
			c2++;
		}
	}
	puts(sg ? (c2 & 1 ? "Bob" : "Alice") : (c2 & 1 ? "Alice" : "Bob"));
	return 0;
}