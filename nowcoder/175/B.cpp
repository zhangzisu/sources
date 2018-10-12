#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 4000010
#define LOGN 21
typedef long long lnt;
lnt a[MAXN];
int n, ans, vis[MAXN];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++) {
		if (vis[i]) continue;
		int left = i, right = i;
		while (left > 1 && a[left-1] % a[i] == 0) vis[--left] = 1;
		while (right < n && a[right+1] % a[i] == 0) vis[++right] = 1;
		ans = std::max(ans, right - left + 1);
	}
	printf("%d\n", ans);
	return 0;
}