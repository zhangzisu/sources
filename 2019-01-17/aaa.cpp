#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, m;
long long ans = 0;
int map[1000010], a[1000010], b[1000010];
int vis[1000010], pri[1000010], pre[1000010], pnt = 0;
inline void shai() {
	for (int i = 2; i <= 1000000; i++) {
		if (!vis[i]) pri[++pnt] = i, pre[i] = i;
		for (int j = 1; j <= pnt; j++) {
			if (1LL * i * pri[j] > 1000000) break;
			vis[i * pri[j]] = 1;
			pre[i * pri[j]] = pri[j];
			if (i % pri[j] == 0) break;
		}
	}
}
int max[1000010], vb;
void dfs(int p, int a, int cur) {
	if (cur > vb) return;
	if (pri[p] > 1000) {
		// fprintf(stderr, "ANS: update, %d = %d\n", cur, map[cur]);
		ans += map[cur];
		return;
	}
	int cnt = 0, t = pri[p];
	for (; a % t == 0; a /= t) cnt++;
	for (int i = 0, x = cur; i <= max[t] && x <= vb; i++, x *= t) {
		if (std::max(i, cnt) & 1) continue;
		dfs(p + 1, a, x);
	}
}
int main() {
    freopen("a.in", "r", stdin);
	shai();
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", &b[i]);
		map[b[i]]++;
		vb = std::max(vb, b[i]);
		for (int x = b[i]; x != 1;) {
			int c = 0, t = pre[x];
			for (; x % t == 0; x /= t) c++;
			max[t] = std::max(max[t], c);
		}
	}
	// fprintf(stderr, "PASS %d", __LINE__);
	for (int i = 1; i <= n; i++) dfs(1, a[i], 1);
	printf("%lld\n", ans);
	return 0;
}