#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int t, n1, m1, n2, m2, n3, m3, a[MAXN][MAXN], b[MAXN][MAXN], c[MAXN][MAXN], d[MAXN][MAXN];
int main() {
	for (scanf("%d", &t); t; t--) {
		scanf("%d%d", &n1, &m1);
		for (int i = 1; i <= n1; i++) {
			for (int j = 1; j <= m1; j++) {
				scanf("%1d", &a[i][j]);
			}
		}
		scanf("%d%d", &n2, &m2);
		for (int i = 1; i <= n2; i++) {
			for (int j = 1; j <= m2; j++) {
				scanf("%1d", &b[i][j]);
			}
		}
		n3 = n2 / gcd(n2, n1) * n1;
		m3 = m2 / gcd(m2, m1) * m1;
		int dn1 = n3 / n1;
		int dn2 = n3 / n2;
		int dm1 = m3 / m1;
		int dm2 = m3 / m2;
		for (int i = 1; i <= n3; i++) {
			for (int j = 1; j <= m3; j++) {
				c[i][j] = a[(i + dn1 - 1) / dn1][(j + dm1 - 1) / dm1];
				d[i][j] = b[(i + dn2 - 1) / dn2][(j + dm2 - 1) / dm2];
			}
		}
		// puts("err:");
		// for (int i = 1; i <= n3; i++) {
		// 	for (int j = 1; j <= m3; j++) printf("%1d", c[i][j]);
		// 	puts("");
		// }
		// puts("err:");
		// for (int i = 1; i <= n3; i++) {
		// 	for (int j = 1; j <= m3; j++) printf("%1d", d[i][j]);
		// 	puts("");
		// }
		int ans = 0;
		for (int i = 1; i <= n3; i++) {
			for (int j = 1; j <= m3; j++) ans += c[i][j] == d[i][j];
		}
        printf("%d\n", ans);
	}
	return 0;
}