#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100
int n, a[MAXN][MAXN];
int d[4][4][MAXN], p[2][MAXN];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 1; k <= 4; k++) {
				scanf("%d", &a[j][k]);
			}
		}
		for (int j = 1; j <= 4; j++) {
			int x = 4;
			for (int k = 1; k <= 4; k++) {
				if (a[j][k] == 0) {
					x = k - 1;
					break;
				}
			}
			if (x == 4) {
				p[0][j] += x;
			} else {
				if (x > d[0][0][j]) {
					d[1][0][j] = d[0][0][j];
					d[3][0][j] = d[2][0][j];
					d[0][0][j] = x;
					d[2][0][j] = i;
				} else if (x > d[1][0][j]) {
					d[1][0][j] = x, d[3][0][j] = i;
				}
			}
			x = 1;
			for (int k = 4; k; k--) {
				if (a[j][k] == 0) {
					x = k + 1;
					break;
				}
			}
			if (x == 1) continue;
			x = 4 - x + 1;
			if (x > d[0][1][j]) {
				d[1][1][j] = d[0][1][j];
				d[3][1][j] = d[2][1][j];
				d[0][1][j] = x;
				d[2][1][j] = i;
			} else if (x > d[1][1][j]) {
				d[1][1][j] = x, d[3][1][j] = i;
			}
		}
		for (int k = 1; k <= 4; k++) {
			int x = 4;
			for (int j = 1; j <= 4; j++) {
				if (a[j][k] == 0) {
					x = j - 1;
					break;
				}
			}
			if (x == 4) {
				p[1][k] += x;
				continue;
			} else {
				if (x > d[0][2][k]) {
					d[1][2][k] = d[0][2][k];
					d[3][2][k] = d[2][2][k];
					d[0][2][k] = x;
					d[2][2][k] = i;
				} else if (x > d[1][2][k]) {
					d[1][2][k] = x, d[3][2][k] = i;
				}
			}
			x = 1;
			for (int j = 4; j; j--) {
				if (a[j][k] == 0) {
					x = j + 1;
					break;
				}
			}
			if (x == 1) continue;
			x = 4 - x + 1;
			if (x > d[0][3][k]) {
				d[1][3][k] = d[0][3][k];
				d[3][3][k] = d[2][3][k];
				d[0][3][k] = x;
				d[2][3][k] = i;
			} else if (x > d[1][3][k]) {
				d[1][3][k] = x, d[3][3][k] = i;
			}
		}
	}
	int ans = 0;
	for (int j = 1; j <= 4; j++) {
		int tmp = p[0][j];
		if (d[2][0][j] == d[2][1][j]) {
			tmp += std::max(d[0][0][j] + d[1][1][j], d[1][0][j] + d[0][1][j]);
		} else {
			tmp += d[0][0][j] + d[0][1][j];
		}
		ans = std::max(ans, tmp);
	}
	for (int j = 1; j <= 4; j++) {
		int tmp = p[1][j];
		if (d[2][2][j] == d[2][3][j]) {
			tmp += std::max(d[0][2][j] + d[1][3][j], d[1][2][j] + d[0][3][j]);
		} else {
			tmp += d[0][2][j] + d[0][3][j];
		}
		ans = std::max(ans, tmp);
	}
	printf("%d\n", ans);
	return 0;
}
