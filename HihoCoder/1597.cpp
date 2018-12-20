#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MOD 1000000007
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
char buf[MAXN];
int n, f[2][2][2][1 << 4][1 << 4];
inline void gao(int &c1, int &ci, int d) { c1 ^= d, ci ^= c1 & !d; }
inline void cao(int s, int &t, int d) {
	for (int e = 0; e < 4; e++) {
		if ((~s >> e) & 1) continue;
		int i1 = e & 1, ii = e >> 1;
		gao(i1, ii, d);
		t |= 1 << (ii << 1 | i1);
	}
}
inline int valid(int s) { return ((s >> 2) | (s >> 3)) & 1; }
int main() {
	scanf("%s", buf + 1);
	n = strlen(buf + 1);
	f[0][0][0][0][0] = 1;
	for (int p = 1; p <= n; p++) {
		int d = buf[p] - '0';
		int now = p & 1, pre = now ^ 1;
		memset(f[now], 0, sizeof(f[now]));
		for (int c1 = 0; c1 < 2; c1++) {
			for (int ci = 0; ci < 2; ci++) {
				for (int s2 = 0; s2 < (1 << 4); s2++) {
					for (int s3 = 0; s3 < (1 << 4); s3++) {
						int &v = f[pre][c1][ci][s2][s3];
						if (!v) continue;
						up(f[now][c1][ci][s2][s3], v);
						int n1 = c1, ni = ci;
						gao(n1, ni, d);
						int t2 = 0, t3 = 0;
						if (ni) t2 |= 1 << d;
						cao(s2, t2, d);
						if (valid(s2)) t3 |= 1 << d;
						cao(s3, t3, d);
						up(f[now][n1][ni][t2][t3], v);
					}
				}
			}
		}
	}
	int ans = 0;
	for (int c1 = 0; c1 < 2; c1++) {
		for (int ci = 0; ci < 2; ci++) {
			for (int s2 = 0; s2 < (1 << 4); s2++) {
				for (int s3 = 0; s3 < (1 << 4); s3++) {
					int &v = f[n & 1][c1][ci][s2][s3];
					if (!v) continue;
					if (ci & 1) {
						up(ans, v);
					} else if (valid(s2)) {
						up(ans, 2LL * v % MOD);
					} else if (valid(s3)) {
						up(ans, 3LL * v % MOD);
					}
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}