#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define MAXN 10010
int n, m, a[MAXN], ans;
std::map<unsigned, int> M;
int main() {
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		unsigned v;
		scanf("%u", &v);
		int &p = M[v];
		if (!p) p = ++n;
		a[p]++;
	}
	double max = -1e100;
	for (int t = 10; t <= 10000000; t *= 10) {
		if (t < n) continue;
		double p = -m * log(t);
		for (int i = 1; i <= n; i++) p += log(t - i + 1) - log(i);
		if (p > max) max = p, ans = t;
	}
	printf("%d\n", ans);
	return 0;
}