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
#define MAXN 100010
int n = io.getint(), m, a[MAXN], b[MAXN];
namespace jiangzeming {
	int b[10];
	inline int main() {
		for (int i = 0; i < n; i++) b[i] = i;
		int ans = 0;
		do {
			int x = a[b[0]];
			for (int i = 1; i < n; i++) x = x % a[b[i]];
			ans = std::max(ans, x);
		} while (std::next_permutation(b, b + n));
		io.put(ans, '\n');
		return 0;
	}
}  // namespace jiangzeming
namespace xijingping {
	int f[2000], g[2000];
	inline int main() {
		int ans = 0;
		std::sort(a, a + n);
		if (a[0] != a[1]) ans = a[0];
		for (int i = n - 1; a[i] != a[0]; i--) {
			memcpy(g, f, sizeof(g));
			f[a[i]] = 1;
			for (int j = 0; j < 2000; j++) {
				if (!g[j]) continue;
				f[j % a[i]] = 1;
			}
		}
		for (int i = 0; i < 2000; i++) {
			if (!f[i]) continue;
			ans = std::max(ans, i % a[0]);
		}
		io.put(ans, '\n');
		return 0;
	}
}  // namespace xijingping
int main() {
	int max = 0;
	for (int i = 0; i < n; i++) max = std::max(max, a[i] = io.getint());
	if (n <= 10) return jiangzeming::main();
	if (max < 2000) return xijingping::main();
	std::sort(a, a + n);
	memcpy(b, a, sizeof(b));
	m = std::unique(b, b + n) - b;
	if (a[0] != a[1]) {
		int ans = a[0];
		for (int i = 1; i < n; i++) ans = std::max(ans, a[i] % a[0]);
		io.put(ans, '\n');
	} else {
		int ans = 0;
		for (int i = 0; i < m; i++) ans = std::max(ans, b[i] % b[0]);
		for (int i = 8000; i < 16500; i++) {
			if (!b[i]) continue;
			for (int j = i; j < i + 5000; j++) {
				if (!b[j]) continue;
				ans = std::max(ans, b[j] % b[i] % b[0]);
			}
		}
		for (int i = 0; i < 300; i++) {
			if (!b[i]) continue;
			for (int j = i; j < i + 300; j++) {
				if (!b[j]) continue;
				for (int k = j; k < j + 300; k++) {
					if (!b[k]) continue;
					ans = std::max(ans, b[k] % b[j] % b[i] % b[0]);
				}
			}
		}
		io.put(ans, '\n');
	}
	return 0;
}