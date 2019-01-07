#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
#define MOD 1000000007
const int INF = (~0U) >> 1;
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int n, a[MAXN], b[MAXN], mp;
int f[MAXN], v[MAXN], s[MAXN], ans, top = 0;
int main() {
	scanf("%d", &n);
	a[mp = 0] = INF;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		if (a[i] < a[mp]) mp = i;
	}
	for (int i = 1; i <= n; i++) b[i] = a[(mp + i - 2) % n + 1];
	f[++top] = 1;
	v[top] = INF;
	for (int i = 1; i <= n; i++) {
		int sum = 0, now = 0;
		while (top && v[top] >= b[i]) up(sum, f[top--]);
		up(now, MOD - s[top]);
		up(now, MOD - 1LL * sum * b[i] % MOD);
		f[++top] = sum, v[top] = b[i], s[top] = s[top - 1];
		up(s[top], 1LL * sum * b[i] % MOD);
		f[++top] = now, v[top] = INF, s[top] = 0;
		up(ans, now);
	}
	up(ans, b[1]);
	printf("%d\n", n & 1 ? MOD - ans : ans);
	return 0;
}