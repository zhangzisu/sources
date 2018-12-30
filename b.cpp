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
#define MAXN 200010
typedef long long lnt;
lnt m, n, x[MAXN], ans;
lnt s1[MAXN], s2[MAXN];
int main() {
	m = io.getint64(), n = io.getint64();
	for (int i = 1; i <= n; i++) x[i] = io.getint64();
	for (int i = 1; i <= n; i++) {
		s1[i] = s1[i - 1] + x[i];
		s2[i] = s2[i - 1] + m - x[i];
	}
	ans = std::max(ans, x[n]);
	ans = std::max(ans, m - x[1]);
	for (int i = 1; i <= n; i++) {
		{
			int l = i + 1, r = n, len = (r - l + 1) / 2;
			if (l <= r) {
				lnt tmp = 2 * x[i];
				tmp += 2 * (s1[l + len - 1] - s1[l - 1]);
				tmp += 2 * (s2[r] - s2[r - len]);
				if (len * 2 == r - l + 1) {
					tmp -= s1[l + len - 1] - s1[l + len - 2];
				} else {
					tmp += s2[l + len] - s2[l + len - 1];
				}
				ans = std::max(ans, tmp);
			}
		}
		{
			int l = 1, r = i - 1, len = (r - l + 1) / 2;
			if (l <= r) {
				lnt tmp = 2 * (m - x[i]);
				tmp += 2 * (s1[l + len - 1] - s1[l - 1]);
				tmp += 2 * (s2[r] - s2[r - len]);
				if (len * 2 == r - l + 1) {
					tmp -= s2[l + len] - s2[l + len - 1];
				} else {
					tmp += s1[l + len] - s1[l + len - 1];
				}
				ans = std::max(ans, tmp);
			}
		}
	}
	io.put(ans, '\n');
	return 0;
}