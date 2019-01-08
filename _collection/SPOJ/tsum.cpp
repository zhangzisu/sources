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
		for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
		return f ? -x : x;
	}
	inline unsigned getuint() {
		register unsigned x = 0;
		register char ch = getchar();
		for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
		return x;
	}
	inline long long getint64() {
		register long long x = 0, f = 0;
		register char ch = getchar();
		for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
		for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
		return f ? -x : x;
	}
	inline unsigned long long getuint64() {
		register unsigned long long x = 0;
		register char ch = getchar();
		for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
		return x;
	}
	inline void putint(int x) {
		if (!x) return putchar('0');
		if (x < 0) putchar(45), x = -x;
		register int _6;
		for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
		while (_6) putchar(tmp[_6--]);
	}
	inline void putint64(long long x) {
		if (!x) return putchar('0');
		if (x < 0) putchar(45), x = -x;
		register int _6;
		for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
		while (_6) putchar(tmp[_6--]);
	}
	inline void print(const char *s) {
		for (; *s; s++) putchar(*s);
	}
	inline void puts(const char *s) {
		print(s);
		putchar(10);
	}
};
#include <cmath>
const int INF = 0x3F3F3F3F;
const int N = 17;
const int LEN = 1 << N;
const double PI = acos(-1);
struct complex {
	double real, image;
	inline complex(double real = 0, double image = 0) : real(real), image(image) {}
	inline complex friend operator+(complex a, complex b) {
		return complex(a.real + b.real, a.image + b.image);
	}
	inline complex friend operator-(complex a, complex b) {
		return complex(a.real - b.real, a.image - b.image);
	}
	inline complex friend operator*(complex a, complex b) {
		return complex(a.real * b.real - a.image * b.image, a.real * b.image + a.image * b.real);
	}
} val[LEN], f[LEN], g[LEN];
inline void FFT(complex *a, int n, int e) {
	for (int i = 1, j = 0; i < n - 1; i++) {
		for (int t = n; ~j & t; j ^= t) t >>= 1;
		if (i < j) std::swap(a[i], a[j]);
	}
	for (int i = 1; i < n; i <<= 1) {
		int t = i << 1;
		complex wn(cos(PI / i), e * sin(PI / i));
		for (int j = 0; j < n; j += t) {
			complex w(1);
			for (int k = 0; k < i; k++) {
				auto x = a[j + k], y = w * a[j + k + i];
				a[j + k] = x + y;
				a[j + k + i] = x - y;
				w = w * wn;
			}
		}
	}
}
int n, min = INF, s[LEN];
long long ans[LEN];
int main() {
	IOX io;
	n = io.getint();
	for (int i = 1; i <= n; i++) min = std::min(min, s[i] = io.getint());
	for (int i = 1; i <= n; i++) s[i] -= min;

	for (int i = 0; i < LEN; i++) f[i] = complex();
	for (int i = 1; i <= n; i++) f[s[i]].real++;
	FFT(f, LEN, 1);
	for (int i = 0; i < LEN; i++) g[i] = f[i] * f[i] * f[i];
	FFT(g, LEN, -1);
	for (int i = 0; i < LEN; i++) ans[i] += std::round(g[i].real / LEN);

	for (int i = 0; i < LEN; i++) g[i] = complex();
	for (int i = 1; i <= n; i++) g[s[i] + s[i]].real++;
	FFT(g, LEN, 1);
	for (int i = 0; i < LEN; i++) g[i] = g[i] * f[i];
	FFT(g, LEN, -1);
	for (int i = 0; i < LEN; i++) ans[i] -= 3LL * std::round(g[i].real / LEN);

	for (int i = 1; i <= n; i++) ans[s[i] + s[i] + s[i]] += 2;
	for (int i = 0; i < LEN; i++) {
		if (!ans[i]) continue;
		io.putint(i + 3 * min);
		io.print(" : ");
		io.putint64(ans[i] / 6);
		io.putchar(10);
	}
	return 0;
}
