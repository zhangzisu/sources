#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, s, x[MAXN];
long long p[MAXN], ans = 0;
int main() {
	scanf("%d%d", &n, &s);
	for (int i = 1; i <= n; i++) scanf("%d%lld", &x[i], &p[i]);
	int l = 1, r = n, last = 0;
	while (l < r && x[l] < s && x[r] > s) {
		if (p[l] < p[r]) {
			ans += last == 1 ? 0 : (x[r] - x[l]);
			last = 1;
			p[r] += p[l];
			l++;
		} else {
			ans += last == 2 ? 0 : (x[r] - x[l]);
			last = 2;
			p[l] += p[r];
			r--;
		}
	}
	printf("%lld\n", ans + std::max(s - x[l], x[r] - s));
	return 0;
}