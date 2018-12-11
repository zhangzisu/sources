#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 200010
typedef long long lnt;
int n, a[MAXN], pre[MAXN], nxt[MAXN];
std::priority_queue<std::pair<int, int>> Q, P;
lnt ans = 0;
inline std::pair<int, int> top() {
	while (P.size() && Q.top() == P.top()) Q.pop(), P.pop();
	return Q.top();
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		pre[i] = i - 1;
		nxt[i] = i + 1;
		Q.emplace(a[i], i);
	}
	for (int t = (n + 1) >> 1; t; t--) {
		auto x = top();
		Q.pop();
		ans += x.first;
		if (pre[x.second] >= 1) {
			P.emplace(a[pre[x.second]], pre[x.second]);
			Q.emplace(a[pre[x.second]] -= x.first, pre[x.second]);
		}
		if (nxt[x.second] <= n) {
			P.emplace(a[nxt[x.second]], nxt[x.second]);
			Q.emplace(a[nxt[x.second]] -= x.first, nxt[x.second]);
		}
		pre[nxt[x.second]] = pre[x.second];
		nxt[pre[x.second]] = nxt[x.second];
        printf("%lld\n", ans);
	}
	return 0;
}