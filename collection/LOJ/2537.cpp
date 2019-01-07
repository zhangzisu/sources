#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 300010
#define MAXM 5000010
#define MOD 998244353
std::vector<int> V;
inline int fuck(int x, int p) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
int n, m, root, son[MAXN][3], val[MAXN], sum[MAXM], tag[MAXM], L[MAXM], R[MAXM], all = 0;
inline void pushDown(int x) {
	if (tag[x] != 1) {
		sum[L[x]] = 1LL * sum[L[x]] * tag[x] % MOD;
		sum[R[x]] = 1LL * sum[R[x]] * tag[x] % MOD;
		tag[L[x]] = 1LL * tag[L[x]] * tag[x] % MOD;
		tag[R[x]] = 1LL * tag[R[x]] * tag[x] % MOD;
		tag[x] = 1;
	}
}
inline int declare(int l, int r, int p) {
	int n = ++all;
	sum[n] = 1;
	tag[n] = 1;
	if (l == r) return n;
	int mid = (l + r) >> 1;
	p <= mid ? L[n] = declare(l, mid, p) : R[n] = declare(mid + 1, r, p);
	return n;
}
inline int merge(int n0, int n1, int l, int r, int v0, int v1, int p) {
	if (!n0) return sum[n1] = 1LL * sum[n1] * v0 % MOD, tag[n1] = 1LL * tag[n1] * v0 % MOD, n1;
	if (!n1) return sum[n0] = 1LL * sum[n0] * v1 % MOD, tag[n0] = 1LL * tag[n0] * v1 % MOD, n0;
	int mid = (l + r) >> 1;
	pushDown(n0);
	pushDown(n1);
	int s0 = sum[R[n0]], s1 = sum[R[n1]], s2 = sum[L[n0]], s3 = sum[L[n1]];
	L[n0] = merge(L[n0], L[n1], l, mid, (v0 + 1LL * p * s0 % MOD) % MOD, (v1 + 1LL * p * s1 % MOD) % MOD, p);
	R[n0] = merge(R[n0], R[n1], mid + 1, r, (v0 + 1LL * (MOD + 1 - p) * s2 % MOD) % MOD, (v1 + 1LL * (MOD + 1 - p) * s3 % MOD) % MOD, p);
	sum[n0] = (sum[L[n0]] + sum[R[n0]]) % MOD;
	return n0;
}
int calc(int x) {
	if (son[x][0] == 2) {
		int l = calc(son[x][1]);
		int r = calc(son[x][2]);
		return merge(l, r, 1, m, 0, 0, (MOD + 1 - val[x]) % MOD);
	} else if (son[x][0] == 1) {
		return calc(son[x][1]);
	} else {
		return declare(1, m, val[x]);
	}
}
int query(int n, int l, int r) {
	if (!n) return 0;
	if (l == r) return 1LL * l * V[l - 1] % MOD * sum[n] % MOD * sum[n] % MOD;
	int mid = (l + r) >> 1;
	pushDown(n);
	return (query(L[n], l, mid) + query(R[n], mid + 1, r)) % MOD;
}
int main() {
	scanf("%d", &n);
	for (int i = 1, p; i <= n; i++) {
		scanf("%d", &p);
		if (p) {
			son[p][++son[p][0]] = i;
		} else {
			root = i;
		}
	}
	for (int i = 1, inv = fuck(10000, MOD - 2); i <= n; i++) {
		scanf("%d", &val[i]);
		if (son[i][0]) {
			val[i] = 1LL * val[i] * inv % MOD;
		} else {
			V.push_back(val[i]);
		}
	}
	std::sort(V.begin(), V.end());
	V.erase(std::unique(V.begin(), V.end()), V.end());
	m = V.size();
	for (int i = 1; i <= n; i++) {
		if (!son[i][0]) {
			val[i] = (std::lower_bound(V.begin(), V.end(), val[i]) - V.begin()) + 1;
		}
	}
	printf("%d\n", query(calc(root), 1, m));
	return 0;
}