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
#include <queue>
#define MAXN 100010
int n = io.getint(), l = io.getint(), s = io.getint(), a[MAXN];
int main() {
	for (int i = 1; i <= n; i++) a[i] = io.getint();
	if (l == 0) {
		if (s == 1) {
			io.put(a[n] - a[1], '\n');
		} else {
			io.put(-1, '\n');
		}
	} else if (l == n - 1) {
		if (s == n) {
			io.put(a[n] - a[1], '\n');
		} else {
			io.put(-1, '\n');
		}
	} else {
		long long ans = (~0ULL) >> 1;
		if (l >= s - 1) {
			int rest = l - s + 1;
			long long tmp = 0LL + a[n] - a[1] + a[s] - a[1] + a[n] - a[n - rest];
			ans = std::min(ans, tmp);
			std::priority_queue<int> Q;
			for (int i = s + 2; i <= n - rest; i++) Q.push(a[i - 1] - a[i]);
			for (int i = n - rest + 1; i <= n; i++) {
				tmp -= a[i] - a[i - 1];
				Q.push(a[i - 1] - a[i]);
				tmp -= 2 * Q.top();
				Q.pop();
				ans = std::min(ans, tmp);
			}
			ans = std::min(ans, 0LL + a[n] - a[1] + a[n] - a[s]);
		}
		if (n - l - 1 >= n - s) {
			int rest = s - l - 1;
			long long tmp = 0LL + a[n] - a[1] + a[n] - a[s] + a[1 + rest] - a[1];
			ans = std::min(ans, tmp);
			std::priority_queue<int> Q;
			for (int i = s - 2; i >= 1 + rest; i--) Q.push(a[i] - a[i + 1]);
			for (int i = rest; i >= 1; i--) {
				tmp -= a[i + 1] - a[i];
				Q.push(a[i] - a[i + 1]);
				tmp -= 2 * Q.top();
				Q.pop();
				ans = std::min(ans, tmp);
			}
			ans = std::min(ans, 0LL + a[n] - a[1] + a[s] - a[1]);
		}
		io.put(ans, '\n');
	}
	return 0;
}
