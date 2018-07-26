#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 4000010
#define MOD 1000000000
int n, m, k, ans, x[MAXN], y[MAXN], z[MAXN];
inline int fuck(int x, int p) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
int p[MAXN], v[MAXN];
inline int find(int x) {
	if (p[x] == x) return x;
	find(p[x]);
	v[x] ^= v[p[x]];
	return p[x] = p[p[x]];
}
bool ok[2] = {1, 1};
inline int calc() {
	for (int i = 1; i <= n + m; i++) p[i] = i, v[i] = 0;
	p[n + 1] = 1;
	for (int i = 1; i <= k; i++) {
		int X = find(x[i]), Y = find(y[i] + n), t = v[x[i]] ^ v[y[i] + n] ^ z[i];
		if (X != Y)
			p[Y] = X, v[Y] = t;
		else if (t)
			return 0;
	}
	int ans = 0;
	for (int i = 1; i <= n + m; i++)
		if (find(i) == i) ans++;
	return fuck(2, ans - 1);
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= k; i++) {
		scanf("%d%d%d", &x[i], &y[i], &z[i]);
		if (x[i] == 1 && y[i] == 1) {
			if (z[i])
				ok[0] = 0;
			else
				ok[1] = 0;
			i--, k--;
		}
		if ((~x[i] & 1) && (~y[i] & 1)) z[i] ^= 1;
	}
	if (ok[0]) ans = (ans + calc()) % MOD;
	for (int i = 1; i <= k; i++) z[i] ^= (x[i] > 1 && y[i] > 1);
	if (ok[1]) ans = (ans + calc()) % MOD;
	printf("%d\n", ans);
	return 0;
}