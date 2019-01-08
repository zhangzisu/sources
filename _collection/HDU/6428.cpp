#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 10000010
const int MOD = 1 << 30;
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int vis[MAXN], val[MAXN], phi[MAXN], last[MAXN], pri[2000010], b[MAXN], c[MAXN], pnt = 0;
inline void shai() {
	b[1] = c[1] = phi[1] = val[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		if (!vis[i]) {
			val[i] = i - 2;
			phi[i] = i - 1;
			pri[++pnt] = b[i] = c[i] = last[i] = i;
		}
		for (int j = 1; j <= pnt; j++) {
			int next = i * pri[j];
			if (next >= MAXN) break;
			vis[next] = 1;
			if (1LL * b[i] * b[i] % next) {
				b[next] = b[i] * pri[j];
			} else {
				b[next] = b[i];
			}
			if (1LL * c[i] * c[i] % next * c[i] % next) {
				c[next] = c[i] * pri[j];
			} else {
				c[next] = c[i];
			}
			if (i % pri[j]) {
				phi[next] = phi[i] * phi[pri[j]];
				val[next] = val[i] * val[pri[j]];
				last[next] = pri[j];
			} else {
				phi[next] = phi[i] * pri[j];
				last[next] = last[i] * pri[j];
				val[next] = val[i / last[i]] * (phi[pri[j] * last[i]] - phi[last[i]]);
				break;
			}
		}
	}
}
int t, A, B, C;
int main() {
	shai();
	for (scanf("%d", &t); t; t--) {
		scanf("%d%d%d", &A, &B, &C);
		int ans = 0;
		for (int i = 1; i <= A; i++) {
			up(ans, 1LL * val[i] * (A / i) * (B / b[i]) * (C / c[i]) % MOD);
		}
		printf("%d\n", ans);
	}
	return 0;
}