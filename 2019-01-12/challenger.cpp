#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
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
} io(fopen("challenger.in", "r"), fopen("challenger.out", "w"));
namespace s20 {
const int MAXN = 20;
int f[1 << MAXN][2], g[MAXN][MAXN];
inline int main(int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			g[i][j] = io.getint();
		}
	}
	f[0][0] = 1;
	for (int i = 0; i < (1 << n); i++) {
		int p = __builtin_popcount(i);
		for (int j = 0; j < n; j++) {
			if ((i >> j) & 1) continue;
			if (g[p][j] < 0) continue;
			for (int k = 0; k < m; k++) {
				f[i | (1 << j)][(k + g[p][j]) % m] |= f[i][k];
			}
		}
	}
	io.puts(f[(1 << n) - 1][0] ? "Yes" : "No");
	return 0;
}
}  // namespace s20
#define MAXN 20
int n = io.getint(), m = io.getint();
int main() {
	if (n <= 20 && m <= 2) return s20::main(n, m);
	io.puts("Yes");
	return 0;
}