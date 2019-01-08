#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int t, n, m, x, y;
int main() {
	for (scanf("%d", &t); t; t--) {
		scanf("%d%d%d%d", &n, &m, &x, &y);
		n--, m--;
		if ((n % x == 0) && (m % y == 0))
			puts("Chefirnemo");
		else if (n - 1 >= 0 && m - 1 >= 0 && ((n - 1) % x == 0) && ((m - 1) % y == 0))
			puts("Chefirnemo");
		else
			puts("Pofik");
	}
	return 0;
}