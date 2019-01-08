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
#define MAXN 262144
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
} a1[MAXN], a2[MAXN], b1[MAXN], b2[MAXN], t[MAXN];
int pro[MAXN];
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
int n = io.getint(), m = io.getint(), p = io.getint(), s = 32768, ans[MAXN];
int main() {
	for (int i = 0; i <= n; i++) {
		int x = io.getint();
		a1[i].real = x % s;
		a2[i].real = x / s;
	}
	for (int i = 0; i <= m; i++) {
		int x = io.getint();
		b1[i].real = x % s;
		b2[i].real = x / s;
	}
	PRE(MAXN), FFT(a1, MAXN, 1), FFT(a2, MAXN, 1), FFT(b1, MAXN, 1), FFT(b2, MAXN, 1);
	for (int i = 0; i < MAXN; i++) t[i] = a1[i] * b1[i];
	FFT(t, MAXN, -1);
	for (int i = 0; i < MAXN; i++) ans[i] = (ans[i] + (long long)std::round(t[i].real / (fl)MAXN)) % p;
	for (int i = 0; i < MAXN; i++) t[i] = a1[i] * b2[i];
	FFT(t, MAXN, -1);
	for (int i = 0; i < MAXN; i++) ans[i] = (ans[i] + (long long)std::round(t[i].real / (fl)MAXN) % p * s % p) % p;
	for (int i = 0; i < MAXN; i++) t[i] = a2[i] * b1[i];
	FFT(t, MAXN, -1);
	for (int i = 0; i < MAXN; i++) ans[i] = (ans[i] + (long long)std::round(t[i].real / (fl)MAXN) % p * s % p) % p;
	for (int i = 0; i < MAXN; i++) t[i] = a2[i] * b2[i];
	FFT(t, MAXN, -1);
	for (int i = 0; i < MAXN; i++) ans[i] = (ans[i] + (long long)std::round(t[i].real / (fl)MAXN) % p * s % p * s % p) % p;
	for (int i = 0; i <= n + m; i++) io.put(ans[i], i == n + m ? '\n' : ' ');
	return 0;
}