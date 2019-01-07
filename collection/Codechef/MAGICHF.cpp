#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int t, n, x, s;
int main() {
	for (scanf("%d", &t); t; t--) {
		scanf("%d%d%d", &n, &x, &s);
		for (int a, b; s; s--) {
			scanf("%d%d", &a, &b);
			if (a == x) {
				x = b;
			} else if (b == x) {
				x = a;
			}
		}
        printf("%d\n", x);
	}
	return 0;
}