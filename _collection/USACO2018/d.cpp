#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, m, c, a[MAXN];
inline bool judge(int mid) {
	int k = 0;
	for (int i = 1; i <= n;) {
		int st = i;
		while (i < st + c && i <= n && a[i] - a[st] <= mid) i++;
		k++;
	}
	return k <= m;
}
int main() {
    freopen("convention.in", "r", stdin);
	freopen("convention.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &c);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	std::sort(a + 1, a + n + 1);
	int l = 0, r = 0x3F3F3F3F;
	while (l <= r) {
		int mid = (l + r) >> 1;
		judge(mid) ? r = mid - 1 : l = mid + 1;
	}
	printf("%d\n", r + 1);
}