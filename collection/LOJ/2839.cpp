#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 310
#define MOD 1000000007
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int n, f[MAXN][MAXN][3];
char buf[MAXN];
int main() {
	scanf("%d%s", &n, buf + 1);
	f[0][0][0] = 1;
	for (int i = 1; i <= n; i++) {
		if (buf[i] != ')') {
			for (int j = 0; j <= n; j++) {
				if (f[i - 1][j][0]) {
					if (j < n) up(f[i][j + 1][0], f[i - 1][j][0]);
					if (j > 0) up(f[i][j - 1][1], f[i - 1][j][0]);
				}
				if (f[i - 1][j][1]) {
					if (j > 0) up(f[i][j - 1][1], f[i - 1][j][1]);
					if (j < n) up(f[i][j + 1][2], f[i - 1][j][1]);
				}
				if (f[i - 1][j][2]) {
					if (j < n) up(f[i][j + 1][2], f[i - 1][j][2]);
				}
			}
		}
		if (buf[i] != '(') {
			for (int j = 0; j <= n; j++) {
				if (f[i - 1][j][0]) {
					if (j > 0) up(f[i][j - 1][0], f[i - 1][j][0]);
					if (j < n) up(f[i][j + 1][1], f[i - 1][j][0]);
				}
				if (f[i - 1][j][1]) {
					if (j < n) up(f[i][j + 1][1], f[i - 1][j][1]);
					if (j > 0) up(f[i][j - 1][2], f[i - 1][j][1]);
				}
				if (f[i - 1][j][2]) {
					if (j > 0) up(f[i][j - 1][2], f[i - 1][j][2]);
				}
			}
		}
	}
	int ans = 0;
	up(ans, f[n][0][0]);
	up(ans, f[n][0][1]);
	up(ans, f[n][0][2]);
	printf("%d\n", ans);
	return 0;
}