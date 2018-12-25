#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2010
#define MOD 998244353
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int n, w[MAXN], a[MAXN][MAXN];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	w[2] = 1;
	for (int i = 3; i <= n; i++) w[i] = 1LL * (i - 1) * (w[i - 1] + w[i - 2]) % MOD;
	//
	return 0;
}