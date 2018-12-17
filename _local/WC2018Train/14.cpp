#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 3010
typedef long long lnt;
int n, m, k;
lnt a, b, c, t, ans, s[MAXN], last[MAXN], next[MAXN], rest[MAXN];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	scanf("%lld%lld%lld", &a, &b, &c);
	scanf("%lld", &t);
	for (int i = 1; i <= m; i++) scanf("%lld", s + i);
	k -= m;
	s[m + 1] = n + 1;
	for (int i = 1; i <= m; i++) {
		lnt cur = 1LL * (s[i] - 1) * b;
		if (cur > t) {
			next[i] = n + 1;
			continue;
		}
		rest[i] = t - cur;
		last[i] = s[i];
		next[i] = std::min(s[i + 1], s[i] + rest[i] / a + 1);
		ans += next[i] - s[i];
	}
	for (int q = 1; q <= k; q++) {
		int p = 0;
		lnt max = 0;
		for (int i = 1; i <= m; i++) {
			if (next[i] >= s[i + 1]) continue;
			lnt cur = 1LL * (next[i] - last[i]) * c;
			if (cur > rest[i]) continue;
			lnt r = std::min(s[i + 1], next[i] + (rest[i] - cur) / a + 1);
			lnt tmp = r - next[i];
			if (tmp > max) {
				max = tmp;
				p = i;
			}
		}
		if (!max) break;
		ans += max;
		lnt cur = 1LL * (next[p] - last[p]) * c;
		rest[p] -= cur;
		last[p] = next[p];
		next[p] = std::min(s[p + 1], next[p] + rest[p] / a + 1);
	}
	printf("%lld\n", ans - 1);
	return 0;
}