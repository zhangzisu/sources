#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
class IO {
       protected:
	static const int BSIZE = 65536;
	int is;
	char ib[BSIZE], ob[BSIZE], *ip, *op;
	FILE *in, *out;

       public:
	inline IO(FILE *in = stdin, FILE *out = stdout) {
		ip = ib + BSIZE, op = ob, is = 0;
		this->in = in;
		this->out = out;
	}
	inline ~IO() {
		fwrite(ob, 1, op - ob, out);
	}
	inline char getchar() {
		if (ip == ib + BSIZE) is = fread(ib, 1, BSIZE, in), ip = ib;
		return ip == ib + is ? 0 : *ip++;
	}
	inline void putchar(char c) {
		if (op == ob + BSIZE) fwrite(ob, 1, BSIZE, out), op = ob;
		*op++ = c;
	}
};
class IOX : public IO {
       protected:
	int tmp[64];

       public:
	inline IOX(FILE *in = stdin, FILE *out = stdout) : IO(in, out) {}
	inline int getdigit() {
		register char ch = getchar();
		while (!isdigit(ch)) ch = getchar();
		return ch ^ 48;
	}
	inline char getalpha() {
		register char ch = getchar();
		while (!isalpha(ch)) ch = getchar();
		return ch;
	}
	inline int getint() {
		register int x = 0, f = 0;
		register char ch = getchar();
		for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
		for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
		return f ? -x : x;
	}
	inline unsigned getuint() {
		register unsigned x = 0;
		register char ch = getchar();
		for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
		return x;
	}
	inline long long getint64() {
		register long long x = 0, f = 0;
		register char ch = getchar();
		for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
		for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
		return f ? -x : x;
	}
	inline unsigned long long getuint64() {
		register unsigned long long x = 0;
		register char ch = getchar();
		for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
		return x;
	}
	inline void put(int x) {
		if (!x) return putchar('0');
		if (x < 0) putchar(45), x = -x;
		register int _6;
		for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
		while (_6) putchar(tmp[_6--]);
	}
	inline void put(long long x) {
		if (!x) return putchar('0');
		if (x < 0) putchar(45), x = -x;
		register int _6;
		for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
		while (_6) putchar(tmp[_6--]);
	}
	inline void put(const char *s) {
		for (; *s; s++) putchar(*s);
	}
	inline void put(char c) { putchar(c); }
	template <typename T, typename... Args>
	inline void put(T first, Args... rest) { put(first), put(rest...); }
	inline void puts(const char *s) {
		put(s);
		putchar(10);
	}
} io;
#include <cmath>
const int N = 65536;
#define MOD 1000000007
inline void trim(int &x) { x -= MOD, x += (x >> 31) & MOD; }
inline void up(int &x, int y) { trim(x += y); }
inline int fuck(int x, int y) {
	int z = 1;
	for (; y; y >>= 1) {
		if (y & 1) z = 1LL * z * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return z;
}
namespace NTTImpl {
using fl = long double;
const fl PI = std::acos(-1);
struct complex {
	fl real, imag;
	inline complex(fl real = 0, fl imag = 0) : real(real), imag(imag) {}
	inline complex friend operator+(complex a, complex b) {
		return complex(a.real + b.real, a.imag + b.imag);
	}
	inline complex friend operator-(complex a, complex b) {
		return complex(a.real - b.real, a.imag - b.imag);
	}
	inline complex friend operator*(complex a, complex b) {
		return complex(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real);
	}
} a1[N], a2[N], b1[N], b2[N], t[N];
int pro[N];
inline void PRE(int n) {
	for (int i = 1, j = 0; i < n - 1; i++) {
		for (int t = n; ~j & t; j ^= t) t >>= 1;
		pro[i] = j;
	}
}
inline void FFT(complex *a, int n, int e) {
	for (int i = 1; i < n - 1; i++) {
		if (i < pro[i]) std::swap(a[i], a[pro[i]]);
	}
	for (int i = 1; i < n; i <<= 1) {
		int t = i << 1;
		complex wn = complex(std::cos(PI / i), e * std::sin(PI / i));
		for (int j = 0; j < n; j += t) {
			complex w(1, 0);
			for (int k = 0; k < i; k++, w = w * wn) {
				complex x = a[j + k], y = w * a[j + k + i];
				a[j + k] = x + y;
				a[j + k + i] = x - y;
			}
		}
	}
}
inline void NTT(int *a, int *b, int *c) {
	for (int i = 0; i < N; i++) {
		a1[i] = complex(a[i] % N);
		a2[i] = complex(a[i] / N);
	}
	for (int i = 0; i < N; i++) {
		b1[i] = complex(b[i] % N);
		b2[i] = complex(b[i] / N);
	}
	memset(c, 0, sizeof(int) * N);
	PRE(N), FFT(a1, N, 1), FFT(a2, N, 1), FFT(b1, N, 1), FFT(b2, N, 1);
	for (int i = 0; i < N; i++) t[i] = a1[i] * b1[i];
	FFT(t, N, -1);
	for (int i = 0; i < N; i++) up(c[i], ((long long)std::round(t[i].real / (fl)N) % MOD + MOD) % MOD);
	for (int i = 0; i < N; i++) t[i] = a1[i] * b2[i];
	FFT(t, N, -1);
	for (int i = 0; i < N; i++) up(c[i], ((long long)std::round(t[i].real / (fl)N) % MOD * N % MOD + MOD) % MOD);
	for (int i = 0; i < N; i++) t[i] = a2[i] * b1[i];
	FFT(t, N, -1);
	for (int i = 0; i < N; i++) up(c[i], ((long long)std::round(t[i].real / (fl)N) % MOD * N % MOD + MOD) % MOD);
	for (int i = 0; i < N; i++) t[i] = a2[i] * b2[i];
	FFT(t, N, -1);
	for (int i = 0; i < N; i++) up(c[i], ((long long)std::round(t[i].real / (fl)N) % MOD * N % MOD * N % MOD + MOD) % MOD);
}
}  // namespace NTTImpl
int n = 0, k, ans;
int frc[N], inv[N], path[N], bin[N], f[N], g[N], h[N];
inline int C(int n, int m) { return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD; }
void dfs(int x) {
	if (x == 1) return;
	if (x & 1) {
		path[++n] = 1;
		dfs(x - 1);
	} else {
		path[++n] = 0;
		dfs(x >> 1);
	}
}
int main() {
	long long tmp = io.getint64();
	k = io.getint();
	if (tmp > k) {
		io.put(0, '\n');
		return 0;
	}
	dfs((int)tmp);
	frc[0] = 1;
	for (int i = 1; i < N; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
	inv[N - 1] = fuck(frc[N - 1], MOD - 2);
	for (int i = N - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
	bin[0] = 1;
	for (int i = 1; i < N; i++) trim(bin[i] = bin[i - 1] << 1);
	for (int i = 1; i <= k; i++) f[i] = 1;
	NTTImpl::PRE(N);
	for (int i = n, now = 1; i >= 1; i--) {
		if (path[i]) {
			for (int j = 0; j <= k; j++) g[j] = 1LL * f[j] * bin[j] % MOD * inv[j] % MOD;
			for (int j = 1; j <= k; j++) h[j] = inv[j];
			NTTImpl::NTT(h, g, f);
			for (int j = 0; j <= k; j++) f[j] = 1LL * f[j] * frc[j] % MOD;
			for (int j = k + 1; j < N; j++) f[j] = 0;
			now++;
		} else {
			for (int j = 0; j <= k; j++) g[j] = 1LL * f[j] * fuck(bin[j], now) % MOD * inv[j] % MOD;
			for (int j = 0; j <= k; j++) h[j] = 1LL * f[j] * inv[j] % MOD;
			NTTImpl::NTT(h, g, f);
			for (int j = 0; j <= k; j++) f[j] = 1LL * f[j] * frc[j] % MOD;
			for (int j = k + 1; j < N; j++) f[j] = 0;
			now *= 2;
		}
	}
	for (int i = 0; i <= k; i++) up(ans, 1LL * f[i] * C(k, i) % MOD);
	io.put(ans, '\n');
	return 0;
}