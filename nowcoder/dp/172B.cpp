#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
typedef long long lnt;
lnt p2[60], p3[40], p5[20], p7[20], l, r, L, R;
const int d2[10] = {0, 0, 1, 0, 2, 0, 1, 0, 3, 0};
const int d3[10] = {0, 0, 0, 1, 0, 0, 1, 0, 0, 2};
const int d5[10] = {0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
const int d7[10] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
lnt f[18][57][38][20][20], g[18][2];
int stk[20];
lnt dfs(int x, int c2, int c3, int c5, int c7, bool prefix, bool flag) {
	if (x < 0) return (p2[c2] * p3[c3] * p5[c5] * p7[c7] >= L && p2[c2] * p3[c3] * p5[c5] * p7[c7] <= R) && !prefix;
	lnt &v = f[x][c2][c3][c5][c7];
	if (!flag && !prefix && ~v) return v;
	int upper = flag ? stk[x] : 9;
	lnt tmp = 0;
	for (int i = prefix ? 0 : 1; i <= upper; i++) {
		tmp += dfs(x - 1, c2 + d2[i], c3 + d3[i], c5 + d5[i], c7 + d7[i], prefix && i == 0, flag && i == upper);
	}
	if (!flag && !prefix) v = tmp;
	return tmp;
}
lnt fsd(int x, bool sum, bool prefix, bool flag) {
	if (x < 0) return !sum;
	lnt &v = g[x][sum];
	if (!flag && !prefix && ~v) return v;
	int upper = flag ? stk[x] : 9;
	lnt tmp = 0;
	for (int i = 0; i <= upper; i++) {
		tmp += fsd(x - 1, sum && (prefix || i != 0), prefix && i == 0, flag && i == upper);
	}
	if (!flag && !prefix) v = tmp;
	return tmp;
}
lnt calc(lnt x) {
	if (x < 0) return 0;
	int len = 0;
	while (x) stk[len++] = x % 10, x /= 10;
	return dfs(len - 1, 0, 0, 0, 0, 1, 1) + (L == 0 ? fsd(len - 1, 1, 1, 1) + 1 : 0);
}
int main() {
	p2[0] = p3[0] = p5[0] = p7[0] = 1;
	for (int i = 1; i < 60; i++) p2[i] = p2[i - 1] * 2;
	for (int i = 1; i < 40; i++) p3[i] = p3[i - 1] * 3;
	for (int i = 1; i < 20; i++) p5[i] = p5[i - 1] * 5;
	for (int i = 1; i < 20; i++) p7[i] = p7[i - 1] * 7;
	memset(f, -1, sizeof(f));
	memset(g, -1, sizeof(g));
	scanf("%lld%lld%lld%lld", &l, &r, &L, &R);
	printf("%lld\n", calc(r) - calc(l - 1));
	return 0;
}