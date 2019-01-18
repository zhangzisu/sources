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
		return ip == ib + is ? EOF : *ip++;
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
#include <cassert>
#include <functional>
#define MAXN 100010
#define SQRT 320
struct block_t {
	int l, r, len, offset, max, tim, w[SQRT], p[MAXN], s[MAXN], v[MAXN];
	inline void ensure(int x) {
		if (v[x] != tim) v[x] = tim, p[x] = x, s[x] = 0;
	}
	inline int find(int x) { return ensure(x), x == p[x] ? x : p[x] = find(p[x]); }
	inline void operate(int start, int end, std::function<void(int &)> op);
	inline void modify(int x);
} b[SQRT];
int n = io.getint(), m = io.getint(), belong[MAXN], tmp[SQRT];
inline void block_t::operate(int start, int end, std::function<void(int &)> op) {
	start -= l, end -= l;
	for (int i = 0; i < len; i++) tmp[i] = find(w[i]) - offset;
	for (int i = start; i <= end; i++) op(tmp[i]);
	offset = max = 0, ++tim;
	for (int i = 0; i < len; i++) max = std::max(max, w[i] = tmp[i]), ensure(w[i]), s[w[i]]++;
}
inline void block_t::modify(int x) {
	if (x >= max) return;
	if (2 * x <= max) {
		for (int i = 1 + offset; i <= x + offset; i++) ensure(i + x), ensure(i), s[i + x] += s[i], p[i] = i + x;
		offset += x, max -= x;
	} else {
		for (int i = x + offset + 1; i <= max + offset; i++) ensure(i - x), ensure(i), s[i - x] += s[i], p[i] = i - x;
		max = x;
	}
}
int main() {
	for (int id = 0, l = 1; l <= n; id++, l += SQRT) {
		int r = std::min(l + SQRT - 1, n);
		b[id].l = l, b[id].r = r, b[id].len = r - l + 1;
		for (int i = l; i <= r; i++) belong[i] = id;
		b[id].operate(l, r, [](int &x) { x = io.getint(); });
	}
	for (int op, l, r, x; m; m--) {
		op = io.getint(), l = io.getint(), r = io.getint(), x = io.getint();
		int L = belong[l], R = belong[r];
		if (op == 1) {
			auto func = [x](int &v) {if(v>x)v-=x; };
			if (L == R) {
				b[L].operate(l, r, func);
			} else {
				if (l != b[L].l) b[L].operate(l, b[L].r, func), L++;
				if (r != b[R].r) b[R].operate(b[R].l, r, func), R--;
				for (int i = L; i <= R; i++) b[i].modify(x);
			}
		} else {
			int ans = 0;
			auto func = [x, &ans](int &v) {if(v==x)ans++; };
			if (L == R) {
				b[L].operate(l, r, func);
			} else {
				if (l != b[L].l) b[L].operate(l, b[L].r, func), L++;
				if (r != b[R].r) b[R].operate(b[R].l, r, func), R--;
				for (int i = L; i <= R; i++) {
					if (b[i].max >= x) {
						ans += b[i].s[x + b[i].offset];
					}
				}
			}
			io.put(ans, '\n');
		}
	}
	return 0;
}