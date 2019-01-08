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
	inline void put(unsigned x) {
		if (!x) return putchar('0');
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
	inline void put(unsigned long long x) {
		if (!x) return putchar('0');
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
#define MAXN 2010
using lnt = long long;
lnt MOD, a[MAXN], b[MAXN];
// inline void exgcd(lnt a, lnt b, lnt &x, lnt &y) { b ? (exgcd(b, a % b, y, x), y -= a / b * x) : (x = 1, y = 0); }
inline lnt exgcd(lnt m, lnt n, lnt &x, lnt &y) {
	if (n == 0) {
		x = 1;
		y = 0;
		return m;
	}
	register lnt a, b, c, d, q, r, t;
	a = y = 1;
	x = b = 0;
	c = m;
	d = n;
	q = c / d;
	r = c % d;
	while (r) {
		c = d;
		d = r;
		t = a;
		a = x;
		x = t - q * x;
		t = b;
		b = y;
		y = t - q * y;
		q = c / d;
		r = c % d;
	}
	return d;
}
inline void trim(lnt &x) { x -= MOD, x += (x >> 63LL) & MOD; }
inline void up(lnt &a, lnt b) { trim(a += b); }
int n, m;
int main() {
	n = io.getint(), m = io.getint();
	MOD = io.getuint64();
	for (int i = 1; i <= n; i++) {
		a[i] = io.getuint64() % MOD;
		b[i] = 1;
	}
	for (int op, l, r; m; m--) {
		op = io.getint(), l = io.getint(), r = io.getint();
		if (op == 1) {
			lnt delta = io.getuint64() % MOD;
			for (register int i = l; i <= r; i++) up(a[i], (__int128)b[i] * delta % MOD);
		} else {
			for (register int i = l; i <= r; i++) {
				if (!a[i]) {
					a[i] = 0, b[i] = 1;
				} else {
					std::swap(a[i], b[i]);
				}
			}
		}
		lnt x = a[1], y = b[1], z, w;
		for (register int i = 2; i <= n; i++) {
			x = (__int128)x * b[i] % MOD;
			up(x, (__int128)y * a[i] % MOD);
			y = (__int128)y * b[i] % MOD;
		}
		exgcd(y, MOD, z, w);
		if (z < 0) z += MOD;
		z %= MOD;
		w = (__int128)x * z % MOD;
		io.put(w, '\n');
	}
	return 0;
}