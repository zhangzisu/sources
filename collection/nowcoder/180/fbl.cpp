#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
typedef long long lnt;
lnt n;
int m;
struct Matrix {
	int _[32][32];
	inline void from(const Matrix &o) {
		memcpy(_, o._, sizeof(_));
	}
};
inline void mul(const Matrix &a, const Matrix &b, Matrix &result, int T) {
	for (int i = 0; i < T; i++) {
		for (int j = 0; j < T; j++) {
			result._[i][j] = 0;
			for (int k = 0; k < T; k++)
				result._[i][j] = (result._[i][j] + 1LL * a._[i][k] * b._[k][j]) % MOD;
		}
	}
}
inline void fpow(const Matrix &origin, Matrix &result, int T, lnt p) {
	Matrix tmp, a;
	for (int i = 0; i < T; i++)
		for (int j = 0; j < T; j++) result._[i][j] = i == j;
	a.from(origin);
	while (p) {
		if (p & 1) mul(result, a, tmp, T), result.from(tmp);
		mul(a, a, tmp, T), a.from(tmp);
		p >>= 1;
	}
}
inline void print(const Matrix &origin, int T) {
	for (int i = 0; i < T; i++) {
		printf("> ");
		for (int j = 0; j < T; j++) printf("%4d", origin._[i][j]);
		puts("");
	}
	puts("");
}
inline bool valid(int x) {
	int c = 0;
	for (int i = 0; i < m; i++)
		if ((x >> i) & 1) c++;
	return c <= (m - c);
}
Matrix trans, result, start, tmp;
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int main() {
	scanf("%lld%d", &n, &m);
	int ans = 0;
	for (int i = 0; i < (1 << n); i++) {
		int real = i << n | i;
		for (int j = 0; j <= n; j++) {
			if (!valid(real >> j)) goto rfail;
		}
		ans++;
        printf("%d\n", i);
	rfail:;
	}
	printf("%d\n", ans);
	return 0;
}