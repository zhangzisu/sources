#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 20000010
typedef long long lnt;
int vis[MAXN], pri[2000000], pnt, t, n;
lnt phi[MAXN];
int main() {
	for (int i = 2; i < MAXN; i++) {
		if (!vis[i]) pri[++pnt] = i, phi[i] = i - 1;
		for (int j = 1; j <= pnt; j++) {
			if (i * pri[j] >= MAXN) break;
			vis[i * pri[j]] = 1;
			if (i % pri[j]) {
				phi[i * pri[j]] = phi[i] * (pri[j] - 1);
			} else {
				phi[i * pri[j]] = phi[i] * pri[j];
				break;
			}
		}
	}
	for (int i = 1; i < MAXN; i++) phi[i] = phi[i - 1] + (phi[i] >> (i & 1));
	for (scanf("%d", &t); t; t--) scanf("%d", &n), printf("%lld\n", phi[n]);
	return 0;
}