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
#define MOD 998244353
#define G 3
inline void trim(int &x) {
	if (x >= MOD) x -= MOD;
}
inline void up(int &x, int y) { trim(x += y); }
inline int fuck(int x, int y) {
	int z = 1;
	for (; y; y >>= 1) {
		if (y & 1) z = 1LL * z * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return z;
}
inline void NTT(int *a, int n) {
	for (int i = 1, j = 0; i < n - 1; i++) {
		for (int t = n; ~j & t; j ^= t) t >>= 1;
		if (i < j) std::swap(a[i], a[j]);
	}
	for (int i = 1; i < n; i <<= 1) {
		int t = i << 1, wn = fuck(G, (MOD - 1) / t);
		for (int j = 0; j < n; j += t) {
			for (int k = 0, w = 1; k < i; k++, w = 1LL * w * wn % MOD) {
				int x = a[j + k], y = 1LL * w * a[j + k + i] % MOD;
				trim(a[j + k] = x + y);
				trim(a[j + k + i] = MOD + x - y);
			}
		}
	}
}
#define MAXN 500000
int n = io.getint(), w = io.getint(), f[MAXN], t0[MAXN], t1[MAXN], cnt = 0, sum = 0;
inline std::pair<int, int> CNTT(int l, int r) {
	if (l == r) {
		int s = cnt, e = cnt + io.getint();
		f[s] = 1, f[e] = -1, cnt = e + 1;
		return std::make_pair(s, e);
	}
	int mid = (l + r) >> 1;
	auto ls = CNTT(l, mid), rs = CNTT(mid + 1, r);
	int len = rs.second - ls.first + 1, n = 1;
	while (n < len) n <<= 1;
	memset(t0, 0, sizeof(int) * n);
	memset(t1, 0, sizeof(int) * n);
	memcpy(t0, f + ls.first, sizeof(int) * (ls.second - ls.first + 1));
	memcpy(t1, f + rs.first, sizeof(int) * (rs.second - rs.first + 1));
	NTT(t0, n), NTT(t1, n);
	for (int i = 0; i < n; i++) t0[i] = 1LL * t0[i] * t1[i] % MOD;
	NTT(t0, n), std::reverse(t0 + 1, t0 + n);
	for (int i = 0, inv = fuck(n, MOD - 2); i < n; i++) t0[i] = 1LL * t0[i] * inv % MOD;
	memcpy(f + ls.first, t0, sizeof(int) * len);
	return std::make_pair(ls.first, rs.second);
}
int main() {
	auto ans = CNTT(1, n - 1);
	for (int i = 0; i <= ans.second; i++) up(sum, 1LL * w * fuck(i + w, MOD - 2) % MOD * f[i] % MOD);
	io.put(sum, '\n');
	return 0;
}