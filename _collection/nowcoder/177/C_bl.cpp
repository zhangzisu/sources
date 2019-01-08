#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 51
#define MOD 1000000007
int f[MAXN][MAXN][MAXN][MAXN], a, b, c, d;
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int main() {
	scanf("%d%d%d%d", &a, &b, &c, &d);
	f[0][0][0][0] = 1;
	f[0][1][0][0] = 1;
	f[0][1][0][1] = 1;
	f[1][0][0][0] = 1;
	f[1][0][1][0] = 1;
	f[1][1][0][0] = 2;
	f[1][1][0][1] = 2;
	f[1][1][1][0] = 2;
	for (int i = 1; i <= a; i++) {
		for (int j = 1; j <= b; j++) {
			for (int k = 1; k <= c; k++) {
				for (int l = 1; l <= d; l++) {
					up(f[i][j][k][l], f[i - 1][j][k][l]);
					up(f[i][j][k][l], f[i - 1][j][k - 1][l]);
					up(f[i][j][k][l], f[i][j - 1][k][l]);
					up(f[i][j][k][l], f[i][j - 1][k][l - 1]);
				}
			}
		}
	}
	printf("%d\n", f[a][b][c][d]);
	return 0;
}