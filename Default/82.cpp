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
#include <vector>
#define MAXN 100010
#define MAXM 10010
typedef long long lnt;
int n = io.getint(), a[MAXN], s[MAXN], pos[MAXM];
lnt f[MAXN];
std::vector<int> cvx[MAXM];
inline lnt A(int x) { return f[x - 1] + 1LL * a[x] * s[x] * s[x]; }
inline lnt B(int x) { return 1LL * a[x] * s[x]; }
int main() {
	for (int i = 1; i <= n; i++) a[i] = io.getint();
	for (int i = 1; i <= n; i++) s[i] = s[pos[a[i]]] + 1, pos[a[i]] = i;
	for (int i = 1; i <= n; i++) {
		std::vector<int> &cvx = ::cvx[a[i]];
		if (cvx.size()) {
			register int l = 0, r = cvx.size() - 2;
			while (l <= r) {
				register int mid = (l + r) >> 1;
				if ((A(cvx[mid + 1]) - A(cvx[mid])) >= (B(cvx[mid + 1]) - B(cvx[mid])) * s[i] * 2) {
					l = mid + 1;
				} else {
					r = mid - 1;
				}
				f[i] = std::max(f[i], f[cvx[mid + 1] - 1] + 1LL * a[i] * (s[i] - s[cvx[mid + 1]] + 1) * (s[i] - s[cvx[mid + 1]] + 1));
				f[i] = std::max(f[i], f[cvx[mid] - 1] + 1LL * a[i] * (s[i] - s[cvx[mid]] + 1) * (s[i] - s[cvx[mid]] + 1));
			}
			f[i] = std::max(f[i], f[cvx[cvx.size() - 1] - 1] + 1LL * a[i] * (s[i] - s[cvx[cvx.size() - 1]] + 1) * (s[i] - s[cvx[cvx.size() - 1]] + 1));
			f[i] = std::max(f[i], f[cvx[0] - 1] + 1LL * a[i] * (s[i] - s[cvx[0]] + 1) * (s[i] - s[cvx[0]] + 1));
		}
		f[i] = std::max(f[i], 1LL * a[i] * s[i] * s[i]);
		f[i] = std::max(f[i], f[i - 1] + a[i]);
		while (cvx.size() > 1 && (A(i) - A(cvx[cvx.size() - 1])) * (B(cvx[cvx.size() - 1]) - B(cvx[cvx.size() - 2])) >= (A(cvx[cvx.size() - 1]) - A(cvx[cvx.size() - 2])) * (B(i) - B(cvx[cvx.size() - 1]))) cvx.pop_back();
		cvx.push_back(i);
	}
	io.put(f[n], '\n');
	return 0;
}