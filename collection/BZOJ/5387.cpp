#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int MAXN = 1 << 20;
int n, m, pri[MAXN], vis[MAXN], f[MAXN];
inline void shai() {
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) {
			pri[++m] = i;
		}
		for (int j = 1; j <= m; j++) {
			if (i * pri[j] > n) break;
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
		}
	}
}
int main() {
	scanf("%d", &n);
	shai();
	for (int i = 1; i <= m && 2 * pri[i] <= n; i++) {
		for (int j = i + 1; j <= m && pri[i] + pri[j] <= n; j++) {
			f[pri[i] + pri[j]] += 2;
		}
		f[pri[i] + pri[i]]++;
	}
	long long ans = 0;
	for (int i = 0; i <= n; i++) ans += 1LL * f[i] * f[n - i];
	printf("%lld\n", ans);
	return 0;
}