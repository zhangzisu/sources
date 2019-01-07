#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define BLOCK 350
#define MAXN 100010

typedef long long lnt;

lnt t, n, m, k, q, a[MAXN], b[MAXN];
lnt f[3][BLOCK][MAXN], g[3][BLOCK][MAXN], tmp[3][MAXN];
char buf[MAXN];

inline lnt calc(lnt l, lnt r, lnt type) {
	tmp[0][a[l]] = 1;
	tmp[1][a[l]] = l;
	tmp[2][a[l]] = l * l;
	lnt ans[3] = {0, 0, 0};
	for (lnt j = l + 1; j <= r; j++) {
		ans[0] += tmp[0][a[j]];
		ans[1] += tmp[0][a[j]] * j - tmp[1][a[j]];
		ans[2] += tmp[0][a[j]] * j * j + tmp[2][a[j]] - 2 * j * tmp[1][a[j]];
		tmp[0][a[j]] += 1;
		tmp[1][a[j]] += j;
		tmp[2][a[j]] += j * j;
	}
	memset(tmp[0], 0, sizeof(lnt) * k);
	memset(tmp[1], 0, sizeof(lnt) * k);
	memset(tmp[2], 0, sizeof(lnt) * k);
	return ans[type];
}

inline lnt CALC(lnt l, lnt L, lnt R, lnt r, lnt type) {
	lnt ans[3] = {0, 0, 0};
	for (lnt j = l; j <= L; j++) {
		tmp[0][a[j]]++;
		tmp[1][a[j]] += j;
		tmp[2][a[j]] += j * j;
	}
	for (lnt j = R; j <= r; j++) {
		ans[0] += tmp[0][a[j]];
		ans[1] += tmp[0][a[j]] * j - tmp[1][a[j]];
		ans[2] += tmp[0][a[j]] * j * j + tmp[2][a[j]] - 2 * j * tmp[1][a[j]];
	}
	memset(tmp[0], 0, sizeof(lnt) * k);
	memset(tmp[1], 0, sizeof(lnt) * k);
	memset(tmp[2], 0, sizeof(lnt) * k);
	return ans[type];
}

lnt DDD, GCC;
int main() {
	scanf("%lld", &t);
	while (t--) {
		DDD = GCC = 0;
		scanf("%s", buf + 1);
		n = strlen(buf + 1) + 1;
		m = sqrt(n);
		for (lnt i = 1; i < n; i++) a[i] = a[i - 1] ^ (1 << (buf[i] - 'a'));
		memcpy(b, a, sizeof(lnt) * n);
		std::sort(b, b + n);
		k = std::unique(b, b + n) - b;
		for (lnt i = 0; i < n; i++) a[i] = std::lower_bound(b, b + k, a[i]) - b;

		for (lnt i = 0; i * m < n; i++) {
			lnt p = i * m;
			f[0][i][p] = f[1][i][p] = f[2][i][p] = 0;
			tmp[0][a[p]] = 1;
			tmp[1][a[p]] = p;
			tmp[2][a[p]] = p * p;
			for (lnt j = p - 1; ~j; j--) {
				f[0][i][j] = f[0][i][j + 1] + tmp[0][a[j]];
				f[1][i][j] = f[1][i][j + 1] + tmp[1][a[j]] - tmp[0][a[j]] * j;
				f[2][i][j] = f[2][i][j + 1] + tmp[0][a[j]] * j * j + tmp[2][a[j]] - 2 * j * tmp[1][a[j]];
				tmp[0][a[j]] += 1;
				tmp[1][a[j]] += j;
				tmp[2][a[j]] += j * j;
			}
			memset(tmp[0], 0, sizeof(lnt) * k);
			memset(tmp[1], 0, sizeof(lnt) * k);
			memset(tmp[2], 0, sizeof(lnt) * k);
			tmp[0][a[p]] = 1;
			tmp[1][a[p]] = p;
			tmp[2][a[p]] = p * p;
			for (lnt j = p + 1; j < n; j++) {
				f[0][i][j] = f[0][i][j - 1] + tmp[0][a[j]];
				f[1][i][j] = f[1][i][j - 1] + tmp[0][a[j]] * j - tmp[1][a[j]];
				f[2][i][j] = f[2][i][j - 1] + tmp[0][a[j]] * j * j + tmp[2][a[j]] - 2 * j * tmp[1][a[j]];
				if (f[2][i][j] < 0) {
					fprintf(stderr, "%lld\n", f[2][i][j]);
					return 0;
				}
				tmp[0][a[j]] += 1;
				tmp[1][a[j]] += j;
				tmp[2][a[j]] += j * j;
			}
			memset(tmp[0], 0, sizeof(lnt) * k);
			memset(tmp[1], 0, sizeof(lnt) * k);
			memset(tmp[2], 0, sizeof(lnt) * k);
		}
		scanf("%lld", &q);
		while (q--) {
			lnt x, y, l, r, t;
			scanf("%lld%lld%lld", &x, &y, &t);
			l = (x + DDD) % (n - 1) + 1;
			r = (y + GCC) % (n - 1) + 1;
			if (l > r) std::swap(l, r);
			l--;

			lnt L = l / m;
			lnt R = r / m;
			lnt ans = 0;
			if (L == R) {
				ans = calc(l, r, t);
			} else {
				ans = f[t][L + 1][r] + f[t][R][l] - f[t][L + 1][R * m];
				ans += CALC(l, (L + 1) * m - 1, R * m + 1, r, t);
			}
			printf("%lld\n", ans);
			DDD = GCC;
			GCC = ans;
		}
	}
	return 0;
}