#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline int $() {
	register int x = 0;
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 2010
int n, m, ans;
int a[MAXN][MAXN], b[MAXN][MAXN], c[MAXN][MAXN], min = 0x3F3F3F3F, max = 0;
inline bool judge(int n, int m) {
	// puts("----------");
	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 1; j <= m; j++) {
	// 		printf("%d ", c[i][j]);
	// 	}
	// 	puts("");
	// }
	for (register int i = 1, maxlen = m; i <= n; i++) {
		for (register int j = 1; j <= maxlen; j++) {
			if (c[i][j] == 2) {
				maxlen = j - 1;
				break;
			}
		}
		for (int j = maxlen + 1; j <= m; j++) {
			if (c[i][j] == 1) {
				return 0;
			}
		}
	}
	return 1;
}
inline bool judge(int mid) {
	for (register int i = 1; i <= n; i++) {
		for (register int j = 1; j <= m; j++) {
			b[i][j] = (a[i][j] <= min + mid) << 1 | (a[i][j] >= max - mid);
			if (!b[i][j]) return 0;
		}
	}
	// printf("=== mid: %d\n", mid);
	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 1; j <= m; j++) {
	// 		printf("%d ", b[i][j]);
	// 	}
	// 	puts("");
	// }
	for (register int i = 1; i <= n; i++) {
		for (register int j = 1; j <= m; j++) {
			c[i][j] = b[i][j];
		}
	}
	if (judge(n, m)) return 1;
	for (register int i = 1; i <= n; i++) {
		for (register int j = 1; j <= m; j++) {
			c[i][j] = b[n - i + 1][j];
		}
	}
	if (judge(n, m)) return 1;
	for (register int i = 1; i <= n; i++) {
		for (register int j = 1; j <= m; j++) {
			c[i][j] = b[i][m - j + 1];
		}
	}
	if (judge(n, m)) return 1;
	for (register int i = 1; i <= n; i++) {
		for (register int j = 1; j <= m; j++) {
			c[i][j] = b[n - i + 1][m - j + 1];
		}
	}
	if (judge(n, m)) return 1;

	for (register int i = 1; i <= n; i++) {
		for (register int j = 1; j <= m; j++) {
			c[j][i] = b[i][j];
		}
	}
	if (judge(m, n)) return 1;
	for (register int i = 1; i <= n; i++) {
		for (register int j = 1; j <= m; j++) {
			c[j][i] = b[n - i + 1][j];
		}
	}
	if (judge(m, n)) return 1;
	for (register int i = 1; i <= n; i++) {
		for (register int j = 1; j <= m; j++) {
			c[j][i] = b[i][m - j + 1];
		}
	}
	if (judge(m, n)) return 1;
	for (register int i = 1; i <= n; i++) {
		for (register int j = 1; j <= m; j++) {
			c[j][i] = b[n - i + 1][m - j + 1];
		}
	}
	if (judge(m, n)) return 1;
	return 0;
}
int main() {
	n = $(), m = $();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			a[i][j] = $();
			min = std::min(min, a[i][j]);
			max = std::max(max, a[i][j]);
		}
	}
	int l = 0, r = ans = max - min;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (judge(mid)) {
			ans = mid, r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}