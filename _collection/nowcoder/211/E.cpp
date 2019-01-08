#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
inline int getint() {
	register int x = 0, f = 0;
	register char ch = getchar();
	while (!isdigit(ch) && (ch ^ 45)) ch = getchar();
	if (!(ch ^ 45)) f = 1, ch = getchar();
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return f ? -x : x;
}
#define N 200010
#define D 20
int n, q, a[N];
int digit[N << 2][20], lazy[N << 2][20], delta[N << 2];
inline void move(int n, int d) {
	static int a[D], b[D];
	memcpy(a, digit[n], sizeof(a));
	memcpy(b, lazy[n], sizeof(b));
	for (int i = 0; i < D; i++) {
		digit[n][(i + d + D) % D] = a[i];
		lazy[n][(i + d + D) % D] = b[i];
	}
}
inline void pu(int n) {
	for (int i = 0; i < D; i++) digit[n][i] = digit[n << 1][i] + digit[n << 1 | 1][i];
}
void build(int n, int l, int r) {
	if (l == r) {
		for (int i = 0; i < D; i++) digit[n][i] = (a[l] >> i) & 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(n << 1, l, mid);
	build(n << 1 | 1, mid + 1, r);
	pu(n);
}
inline int pd(int n, int l, int r) {
	int mid = (l + r) >> 1;
	if (delta[n]) {
		move(n << 1, delta[n]), (delta[n << 1] += delta[n]) %= D;
		move(n << 1 | 1, delta[n]), (delta[n << 1 | 1] += delta[n]) %= D;
		delta[n] = 0;
	}
	for (int i = 0; i < 20; i++) {
		if (lazy[n][i] == 0) {
			lazy[n << 1][i] = 0, lazy[n << 1 | 1][i] = 0, digit[n << 1][i] = 0, digit[n << 1 | 1][i] = 0;
		} else if (lazy[n][i] == 1) {
			lazy[n << 1][i] = 1, lazy[n << 1 | 1][i] = 1, digit[n << 1][i] = mid - l + 1, digit[n << 1 | 1][i] = r - mid;
		}
		lazy[n][i] = -1;
	}
	return mid;
}
long long query(int n, int l, int r, int L, int R) {
	if (l == L && r == R) {
		long long ret = 0;
		for (int i = 0; i < D; i++) ret += 1LL * digit[n][i] * (1 << i);
		return ret;
	}
	int mid = pd(n, l, r);
	if (R <= mid) return query(n << 1, l, mid, L, R);
	if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R);
	return query(n << 1, l, mid, L, mid) + query(n << 1 | 1, mid + 1, r, mid + 1, R);
}
void _or(int n, int l, int r, int L, int R, int d) {
	if (l == L && r == R) {
		for (int i = 0; i < D; i++)
			if ((d >> i) & 1)
				digit[n][i] = r - l + 1, lazy[n][i] = 1;
		return;
	}
	int mid = pd(n, l, r);
	if (R <= mid)
		_or(n << 1, l, mid, L, R, d);
	else if (L > mid)
		_or(n << 1 | 1, mid + 1, r, L, R, d);
	else
		_or(n << 1, l, mid, L, mid, d), _or(n << 1 | 1, mid + 1, r, mid + 1, R, d);
	for (int i = 0; i < D; i++) digit[n][i] = digit[n << 1][i] + digit[n << 1 | 1][i];
}
void _and(int n, int l, int r, int L, int R, int d) {
	if (l == L && r == R) {
		for (int i = 0; i < D; i++)
			if (!((d >> i) & 1))
				digit[n][i] = 0, lazy[n][i] = 0;
		return;
	}
	int mid = pd(n, l, r);
	if (R <= mid)
		_and(n << 1, l, mid, L, R, d);
	else if (L > mid)
		_and(n << 1 | 1, mid + 1, r, L, R, d);
	else
		_and(n << 1, l, mid, L, mid, d), _and(n << 1 | 1, mid + 1, r, mid + 1, R, d);
	for (int i = 0; i < D; i++) digit[n][i] = digit[n << 1][i] + digit[n << 1 | 1][i];
}
void shift(int n, int l, int r, int L, int R, int d) {
	if (l == L && r == R) return move(n, d), (delta[n] += d) %= D, void();
	int mid = pd(n, l, r);
	if (R <= mid)
		shift(n << 1, l, mid, L, R, d);
	else if (L > mid)
		shift(n << 1 | 1, mid + 1, r, L, R, d);
	else
		shift(n << 1, l, mid, L, mid, d), shift(n << 1 | 1, mid + 1, r, mid + 1, R, d);
	for (int i = 0; i < D; i++) digit[n][i] = digit[n << 1][i] + digit[n << 1 | 1][i];
}
int main() {
	n = getint(), q = getint();
	for (int i = 1; i <= n; i++) a[i] = getint();
	memset(lazy, -1, sizeof(lazy));
	build(1, 1, n);
	for (int opt, l, r, v; q; q--) {
		opt = getint(), l = getint(), r = getint(), v = getint();
		switch (opt) {
			case 1:
				shift(1, 1, n, l, r, -v);
				break;
			case 2:
				shift(1, 1, n, l, r, v);
				break;
			case 3:
				_or(1, 1, n, l, r, v);
				break;
			case 4:
				_and(1, 1, n, l, r, v);
				break;
			case 5:
				printf("%lld\n", query(1, 1, n, l, r));
				break;
		}
	}
	return 0;
}