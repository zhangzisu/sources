#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 710
bool can[MAXN][MAXN][2];
int n, a[MAXN], b[MAXN][MAXN];
inline int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		b[i][0] = b[i][n + 1] = b[0][i] = b[n + 1][i] = 1;
		for (int j = 1; j <= n; j++) {
			b[i][j] = gcd(a[i], a[j]) > 1;
		}
	}
	for (int l = n; l >= 1; l--) {
		for (int r = l; r <= n; r++) {
			if (l == r) {
				can[l][r][0] = b[l][l - 1];
				can[l][r][1] = b[l][l + 1];
			} else {
				if (b[l][l - 1]) can[l][r][0] |= can[l + 1][r][0];
				if (b[l][r + 1]) can[l][r][1] |= can[l + 1][r][0];
				if (b[r][l - 1]) can[l][r][0] |= can[l][r - 1][1];
				if (b[r][r + 1]) can[l][r][1] |= can[l][r - 1][1];
				for (int k = l + 1; k < r; k++) {
					bool g = can[l][k - 1][1] && can[k + 1][r][0];
					if (b[k][l - 1]) can[l][r][0] |= g;
					if (b[k][r + 1]) can[l][r][1] |= g;
				}
			}
		}
	}
	if (can[1][n][0] || can[1][n][1]) return puts("Yes"), 0;
	puts("No");
	return 0;
}