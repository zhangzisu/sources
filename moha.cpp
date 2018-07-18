#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef long long LL;

const int M = 23, P = ((7 * 17) << M) + 1, G = 3;
const int MAXN = (1 << 18) + 10;
int N = 1 << 16;

inline int add(int a, int b) {
	return (a + b) % P;
}

inline int sub(int a, int b) {
	return (a - b + P) % P;
}

inline int mul(int a, int b) {
	return (LL)a * (LL)b % P;
}

inline int exp(int a, int b) {
	int ans = 1;
	for (; b; b >>= 1) {
		if (b & 1) ans = mul(ans, a);
		a = mul(a, a);
	}
	return ans;
}

inline int inv(int a) {
	return exp(a, P - 2);
}

int eps[MAXN], ieps[MAXN], temp[5][MAXN];

inline void init() {
	int g = exp(G, (P - 1) / N), ig = inv(g);
	eps[0] = ieps[0] = 1;
	for (int i = 1; i < N; i++) eps[i] = mul(eps[i - 1], ig), ieps[i] = mul(ieps[i - 1], g);
}

inline void trans(int n, int a[], int w[]) {
	for (int i = 0, j = 0; i != n; i++) {
		if (i < j) std::swap(a[i], a[j]);
		for (int l = n >> 1; (j ^= l) < l; l >>= 1)
			;
	}
	for (int i = 2; i <= n; i <<= 1) {
		int l = i >> 1, d = N / i;
		for (int j = 0; j != n; j += i)
			for (int k = 0; k != l; k++) {
				int t = mul(a[j + k + l], w[d * k]);
				a[j + k + l] = sub(a[j + k], t);
				a[j + k] = add(a[j + k], t);
			}
	}
}

inline void dft(int n, int a[]) {
	trans(n, a, eps);
}

inline void idft(int n, int a[]) {
	trans(n, a, ieps);
	for (int i = 0, in = inv(n); i < n; i++) a[i] = mul(a[i], in);
}

inline void inv(int n, int a[], int b[]) {
	int *t = temp[0];
	std::fill(b, b + (n << 1), 0);
	b[0] = inv(a[0]);
	for (int i = 2; i <= n; i = i << 1) {
		std::copy(a, a + i, t);
		std::fill(t + i, t + (i << 1), 0);
		dft((i << 1), t);
		dft((i << 1), b);
		for (int j = 0; j < (i << 1); j++) b[j] = 1LL * b[j] * (2 - 1LL * t[j] * b[j] % P + P) % P;
		idft((i << 1), b);
		std::fill(b + i, b + (i << 1), 0);
	}
}

inline void drv(int n, int a[], int b[]) {
	for (int i = 1; i < n; i++) b[i - 1] = mul(i, a[i]);
	b[n - 1] = 0;
}

inline void itg(int n, int a[], int b[]) {
	for (int i = n - 1; i; i--) b[i] = mul(a[i - 1], inv(i));
	b[0] = 0;
}

inline void ln(int n, int a[], int b[]) {
	int *t = temp[1];
	inv(n, a, b);
	drv(n, a, t);
	std::fill(b + n, b + n + n, 0);
	std::fill(t + n, t + n + n, 0);
	dft(n << 1, b), dft(n << 1, t);
	for (int i = 0; i < (n << 1); i++) b[i] = mul(b[i], t[i]);
	idft(n << 1, b);
	std::fill(b + n, b + n + n, 0);
	itg(n, b, b);
}

inline void exp(int n, int a[], int b[]) {
	int *t = temp[2];
	std::fill(b, b + (n << 1), 0);
	b[0] = 1;
	for (int i = 2; i <= n; i = i << 1) {
		ln(i, b, t);
		t[0] = sub(a[0] + 1, t[0]);
		for (int k = 1; k < i; k++) t[k] = sub(a[k], t[k]);
		std::fill(t + i, t + (i << 1), 0);
		dft((i << 1), b), dft((i << 1), t);
		for (int k = 0; k < (i << 1); k++) b[k] = mul(b[k], t[k]);
		idft((i << 1), b);
		std::fill(b + i, b + (i << 1), 0);
	}
}

const int I2 = inv(2);

inline void sqrt(int n, int a[], int b[]) {
	int *t = temp[3];
	std::fill(b, b + (n << 1), 0);
	b[0] = 1;
	for (int i = 2; i <= n; i <<= 1) {
		inv(i, b, t);
		dft(i, b);
		for (int j = 0; j < i; j++) b[j] = mul(b[j], b[j]);
		idft(i, b);
		for (int j = 0; j < i; j++) b[j] = add(b[j], a[j]);
		dft((i << 1), b), dft((i << 1), t);
		for (int j = 0; j < (i << 1); j++) b[j] = mul(b[j], t[j]);
		idft((i << 1), b);
		for (int j = 0; j < i; j++) b[j] = mul(b[j], I2);
		std::fill(b + i, b + (i << 1), 0);
	}
}

int f[MAXN] = {1, 6, 1}, g[MAXN], h[MAXN] = {1, 1}, l[MAXN];

int main() {
	init();
	int n = 1 << 15, a = 0, b = 0;
	scanf("%d%d", &a, &b);
	sqrt(n, f, g);
	for (int i = 0; i < n; i++) h[i] = mul(I2, add(h[i], g[i]));
	ln(n, h, l);
    for (int i = 0; i < 10; i++) printf("%d ", l[i]);
	for (int i = 0; i < n; i++) l[i] = mul(a + 1, l[i]);
	exp(n, l, h);
	inv(n, g, l);
	dft(n << 1, h), dft(n << 1, l);
	for (int i = 0; i < (n << 1); i++) h[i] = mul(h[i], l[i]);
	idft(n << 1, h);
	for (int i = 1; i <= b; i++) printf("%d\n", i <= a ? h[i] : 0);
	return 0;
}
