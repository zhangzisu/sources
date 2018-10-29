#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <unordered_map>
typedef unsigned long long lnt;
const int MAXN = 10000000;
int prime[1000000], num;
int vis[MAXN + 5], mu[MAXN + 5];
inline void shai() {
	mu[1] = 1;
	for (int i = 2; i <= MAXN; i++) {
		if (!vis[i]) prime[++num] = i, mu[i] = -1;
		for (int j = 1; j <= num && (lnt)i * prime[j] <= MAXN; j++) {
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			}
			mu[i * prime[j]] = mu[i] * mu[prime[j]];
		}
	}
	for (int i = 1; i <= MAXN; i++) mu[i] += mu[i - 1];
}
std::unordered_map<lnt, int> S;
inline int sum(lnt n) {
	if (n <= MAXN) return mu[n];
	if (S.find(n) != S.end()) return S[n];
	int ret = 1;
	lnt l, r;
	for (l = 2; l * l <= n; l++) ret -= sum(n / l);
	for (lnt t = n / l; l <= n; l = r + 1, t--) {
		r = n / t;
		ret -= (r - l + 1) * sum(t);
	}
	return S[n] = ret;
}
lnt n, m;
lnt ans = 0;
lnt fuck(lnt x, lnt p) {
	lnt y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = y * x;
		x = x * x;
	}
	return y;
}
int main() {
	shai();
	scanf("%llu%llu", &n, &m);
	for (lnt i = 1, j; i <= m; i = j + 1) {
		j = std::min(m, (m / (m / i)));
		ans += (sum(j) - sum(i - 1)) * fuck(m / i, n);
	}
	printf("%llu\n", ans);
	return 0;
}
