#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int MAXN = 18;
const int MAXM = 10010;
int n, m, k, val, a[MAXM], dist[MAXN], f[1 << MAXN], g[1 << MAXN], c[1 << MAXN];
inline int lowbit(int x) { return x & -x; }
int weigit[MAXN];
inline int getWeight(int x) {
	int ans = n;
	for (int i = 0; i < n; i++)
		if ((x >> i) & 1) ans = std::min(ans, weigit[i]);
	return ans;
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i < (1 << n); i++) c[i] = c[i - lowbit(i)] + 1;
	for (int i = 1; i <= m; i++) scanf("%d", &a[i]);
	for (int i = 0; i < n; i++)
		if ((k >> i) & 1) dist[n - i - 1] = 1;
	f[0] = 1;
	for (int d = 0; d < (1 << n); d++) {
		int &val = f[d], pos = c[d];
		if (!val) continue;
		for (int i = 0; i < n; i++) {
			if ((d >> i) & 1) continue;
			for (int j = 1; j <= m; j++)
				if (!dist[pos] && ((a[j] >> i) & 1) && !(a[j] & d)) goto fail;
			f[d + (1 << i)] = 1;
			g[d + (1 << i)] = i;
		fail:;
		}
	}
	if (f[(1 << n) - 1]) {
		for (int x = (1 << n) - 1, i = n - 1; ~i; i--) {
			weigit[g[x]] = i;
			x -= 1 << g[x];
		}
		for (int i = 1; i < (1 << n); i++) putchar(dist[getWeight(i)] ? 49 : 48);
		putchar(10);
		return 0;
	}
	puts("-1");
	return 0;
}