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
	if (n < m * 2) {
		int ans = 0;
		for (int i = 0; i < (1 << n); i++) {
			int real = i << n | i;
			for (int j = 0; j < n; j++) {
				if (!valid(real >> j)) goto rfail;
			}
			ans++;
		rfail:;
		}
		printf("%d\n", ans);
		return 0;
	}
	int mask = (1 << m) - 1;
	for (int i = 0; i < (1 << m); i++) {
		if (!valid(i)) continue;
		int next0 = (i << 1) & mask;
		if (valid(next0)) {
			trans._[i][next0]++;
		}
		int next1 = (i << 1 | 1) & mask;
		if (valid(next1)) {
			trans._[i][next1]++;
		}
	}
	int steps = n - m;
	fpow(trans, result, 1 << m, steps);
	int ans = 0;
	for (int i = 0; i < (1 << m); i++) {
		if (!valid(i)) continue;
		memset(start._, 0, sizeof(start._));
		start._[0][i] = 1;
		mul(start, result, tmp, 1 << m);
		for (int j = 0; j < (1 << m); j++) {
			if (!valid(j)) continue;
			int real = 0;
			for (int k = 0; k < m; k++)
				if ((i >> k) & 1) real |= 1 << (m + m - k - 1);
			for (int k = 0; k < m; k++)
				if ((j >> k) & 1) real |= 1 << (m - k - 1);
			for (int k = 0; k <= m; k++) {
				if (!valid(real >> k)) goto fail;
			}
			up(ans, tmp._[0][j]);
		fail:;
		}
	}
	printf("%d\n", ans);
	return 0;
}