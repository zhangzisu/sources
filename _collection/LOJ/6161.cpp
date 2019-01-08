#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
typedef long long lnt;
int n, T, C, t[MAXN], c[MAXN];
lnt sumq, sumc;
int main() {
	scanf("%d%d%d", &n, &T, &C);
	sumq = 1LL * T * C, sumc = C;
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", t + i, c + i);
		sumq += 1LL * t[i] * c[i];
		sumc += c[i];
	}
	double ans = 1. * sumq / sumc;
	double sumn = 0;
	for (int i = 1; i <= n; i++) {
		double need = 1. * (1LL * t[i] * c[i] - ans * c[i]) / (ans - T);
		sumn += need;
	}
	if (std::abs(sumn - sumc) <= 1e-5) {
		puts("Possible");
		printf("%.4f\n", ans);
	} else {
		puts("Impossible");
	}
	return 0;
}