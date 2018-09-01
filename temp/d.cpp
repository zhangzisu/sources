#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int a, n, pr[5000010], pnt, ans;
std::bitset<20000010> vis;
inline int get(int x) { return a * x + 1; }
int main() {
	scanf("%d%d", &a, &n);
	for (int i = 1; get(i) <= n; i++) {
		if (!vis[i]) {
			pr[++pnt] = i;
		} else {
			ans++;
		}
		for (int j = 1; j <= pnt; j++) {
			if (1LL * get(i) * get(pr[j]) > n) break;
			int x = get(i) * get(pr[j]);
			int k = (x - 1) / a;
			if (k * a + 1 == x) vis[k] = 1;
			if (get(i) % get(pr[j]) == 0) break;
		}
	}
	printf("%d\n", ans);
	return 0;
}