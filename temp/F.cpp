#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
#define MAXK 2010
typedef long long lnt;
int n, k;
lnt p[MAXN], d[MAXN], f[MAXN][MAXK];
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%lld%lld", &p[i], &d[i]);
	d[1] = 0;
	for (int i = 1; i <= n; i++) p[i] -= (d[i] += d[i - 1]);
	for (int i = 1; i <= n; i++) {
		//
	}
	return 0;
}