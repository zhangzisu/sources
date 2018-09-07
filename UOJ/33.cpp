#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 200010
#define SQRT 450
typedef long long lnt;
int n, p[MAXN], fa[MAXN], f[MAXN], g[MAXN], d[MAXN], h[MAXN];
lnt s[MAXN];
std::vector<int> v[MAXN];
int main() {
	for (int i = (scanf("%d", &n), 2); i <= n; i++) scanf("%d", &p[i]);
	d[0] = -1;
	for (int i = 1; i <= n; i++) h[d[fa[i] = i] = d[p[i]] + 1]++;
	for (int i = n; i >= 1; i--) h[i - 1] += h[i];
	for (int d = 1; d < SQRT; d++) {
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		for (int i = n; i >= 2; i--) {
			f[i] += 1;
			if (fa[i]) {
				g[fa[i]] += f[i];
				fa[i] = p[fa[i]];
			}
			s[d] += 1LL * f[p[i]] * g[i];
			f[p[i]] += g[i];
		}
	}
	for (int i = n; i >= 2; i--) {
		std::vector<int> &t = v[i];
		std::vector<int> &f = v[p[i]];
		t.push_back(1);
		if (f.size() < t.size()) std::swap(f, t);
		int lenf = (int)f.size();
		int lent = (int)t.size();
		if (lent >= SQRT) {
			for (int j = SQRT; j < n; j++) {
				int A = 0, B = 0;
				for (int k = lenf - j; k >= 0; k -= j) A += f[k];
				for (int k = lent - j; k >= 0; k -= j) B += t[k];
				s[j] += 1LL * A * B;
			}
		}
		for (int i = 1; i <= lent; i++) f[lenf - i] += t[lent - i];
		t.clear();
	}
	for (int i = n - 1; i; i--)
		for (int j = i + i; j < n; j += i) s[i] -= s[j];
	for (int i = 1; i < n; i++) printf("%lld\n", s[i] + h[i]);
	return 0;
}
