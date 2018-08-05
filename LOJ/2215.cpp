#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
typedef long long lnt;
lnt l, r, k, *f[51][51];
int digit[64];
lnt dfs0(int pos, int sum, bool flag) {
	assert(sum < 1800);
	if (pos < 0) return sum;
	if (!flag && ~f[0][pos][sum]) return f[0][pos][sum];
	int upper = flag ? digit[pos] : k - 1;
	lnt ret = 0;
	for (int i = 0; i <= upper; i++) {
		ret += dfs0(pos - 1, sum + i * pos, flag && i == upper);
	}
	if (!flag) f[0][pos][sum] = ret;
	return ret;
}
lnt dfs1(int pos, int sum, bool flag, int arg) {
	assert(sum < 1800);
	assert(sum > -1800);
	if (pos < 0) return std::max(sum, 0);
	if (!flag && ~f[arg][pos][sum]) return f[arg][pos][sum];
	int upper = flag ? digit[pos] : k - 1;
	lnt ret = 0;
	for (int i = 0; i <= upper; i++) {
		ret += dfs1(pos - 1, sum + (pos < arg ? 1 : -1) * i, flag && i == upper, arg);
	}
	if (!flag) f[arg][pos][sum] = ret;
	return ret;
}
inline lnt solve(lnt x) {
	int top = 0;
	for (; x; x /= k) digit[top++] = x % k;
	lnt all = dfs0(top - 1, 0, 1);
	for (int i = 1; i < top; i++) {
		all -= dfs1(top - 1, 0, 1, i);
	}
	return all;
}
int main() {
	scanf("%lld%lld%lld", &l, &r, &k);
	for (int i = 0; i < 51; i++) {
		for (int j = 0; j < 51; j++) {
			lnt *tmp = (lnt *)calloc(3600, sizeof(lnt));
			for (int k = 0; k < 3600; k++) tmp[k] = -1;
			f[i][j] = tmp + 1800;
		}
	}
	printf("%lld\n", solve(r) - solve(l - 1));
	return 0;
}