#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 10010
#define MOD 2333
int f[MAXN][MAXN], s[MAXN], n;
char buf[MAXN];
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int main() {
	scanf("%d%s", &n, buf + 1);
	for (int i = 1; i <= n; i++) s[i] = buf[i] == '(' ? 1 : -1;
	for (int i = 1; i <= n; i++) s[i] += s[i - 1];
	f[0][0] = 1;
	for (int i = 1, sum = 0; i <= n; i++) {
		int t = buf[i] == '(' ? 1 : -1;
		sum += t;
		for (int j = 0; j <= sum; j++) {
			if (s[i] - j < 0) continue;
			up(f[i][j], f[i - 1][j]);
			if (j - t >= 0) up(f[i][j], f[i - 1][j - t]);
		}
	}
	printf("%d\n", f[n][0]);
	return 0;
}