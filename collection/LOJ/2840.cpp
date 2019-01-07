#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 200010
typedef long long lnt;
const lnt INF = (~0ULL) >> 2;
int n, pre[MAXN], nxt[MAXN];
lnt a[MAXN], ans = 0;
std::priority_queue<std::pair<lnt, int>> Q, P;
inline void remove(int x) {
	if (~nxt[x]) pre[nxt[x]] = pre[x];
	if (~pre[x]) nxt[pre[x]] = nxt[x];
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", a + i);
		pre[i] = i - 1;
		nxt[i] = i + 1;
		Q.emplace(a[i], i);
	}
	pre[0] = -1, nxt[0] = 1, pre[n + 1] = n, nxt[n + 1] = -1;
	Q.emplace(a[0] = -INF, 0);
	Q.emplace(a[n + 1] = -INF, n + 1);
	for (int t = (n + 1) >> 1; t; t--) {
		while (P.size() && Q.top() == P.top()) Q.pop(), P.pop();
		auto x = Q.top().second;
		Q.pop();
		ans += a[x];
		P.emplace(a[pre[x]], pre[x]);
		P.emplace(a[nxt[x]], nxt[x]);
		Q.emplace(a[x] = a[pre[x]] + a[nxt[x]] - a[x], x);
		remove(pre[x]);
		remove(nxt[x]);
		printf("%lld\n", ans);
	}
	return 0;
}