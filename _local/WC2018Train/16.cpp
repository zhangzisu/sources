#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int MAXN = 24;
int n, p;
inline void up(int &x, int y) {
	if ((x += y) >= p) x -= p;
}
inline int fuck(int x, int y) {
	int z = 1;
	for (; y; y >>= 1) {
		if (y & 1) z = 1LL * z * x % p;
		x = 1LL * x * x % p;
	}
	return z;
}
int tmp[MAXN + 1], pos[MAXN + 1], f[1 << MAXN], ans;
double g[1 << MAXN], sum;
int main() {
	scanf("%d%d", &n, &p);
	f[1] = 1;
	g[1] = 1;
	for (int i = 1; i < (1 << n); i++) {
		if (!f[i]) continue;
		int now = 0;
		for (int j = 0; j <= n; j++) tmp[j] = 0;
		for (int j = n - 1; j >= 0; j--) {
			if ((i >> j) & 1) {
				pos[++now] = j;
			}
			tmp[now]++;
		}
		if ((i >> (n - 1)) & 1) {
			up(ans, 1LL * f[i] * now % p);
			sum += g[i] * now;
		} else {
			for (int j = 2; j <= now; j++) {
				int nxt = (i >> pos[j] << pos[j] << 1) | (i & ((1 << pos[j]) - 1));
				up(f[nxt], 1LL * f[i] * tmp[j - 1] % p);
				g[nxt] += g[i] * tmp[j - 1];
			}
			up(f[i << 1 | 1], 1LL * f[i] * tmp[now] % p);
			g[i << 1 | 1] += g[i] * tmp[now];
		}
	}
	for (int i = 2; i < n; i++) {
		ans = 1LL * ans * fuck(i, p - 2) % p;
		sum /= i;
	}
	printf("%d\n", (int)round(sum));
	printf("%d\n", ans);
	return 0;
}