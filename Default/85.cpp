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
#include <bitset>
#define MOD 998244353
#define INV 499122177
inline void trim(int &x) { x -= MOD, x += (x >> 31) & MOD; }
inline int fuck(int x, int y) {
	int z = 1;
	for (; y; y >>= 1) {
		if (y & 1) z = 1LL * z * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return z;
}
inline void FWT(int *a, int n) {
	for (int i = 1; i < n; i <<= 1) {
		int t = i << 1;
		for (int j = 0; j < n; j += t) {
			for (int k = 0; k < i; k++) {
				int x = a[j + k], y = a[j + k + i];
				trim(a[j + k] = x + y);
				trim(a[j + k + i] = MOD + x - y);
			}
		}
	}
}
const int MAXN = 1 << 20;
int n = io.getint(), m = io.getint(), k = 1 << n, ans = n * m, f[MAXN], g[MAXN], cnt[MAXN];
inline int lowbit(int x) { return x & -x; }
std::bitset<MAXN> buf[20];
int main() {
	for (int i = 1; i < k; i++) cnt[i] = cnt[i - lowbit(i)] + 1;
	for (int i = 0; i < k; i++) g[i] = std::min(cnt[i], n - cnt[i]);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) buf[i][j] = io.getdigit();
	}
	for (int j = 0; j < m; j++) {
		int t = 0;
		for (int i = 0; i < n; i++) t = (t << 1) | buf[i][j];
		f[t]++;
	}
	FWT(f, k);
	FWT(g, k);
	for (int i = 0; i < k; i++) f[i] = 1LL * f[i] * g[i] % MOD;
	FWT(f, k);
	for (int i = 0, inv = fuck(k, MOD - 2); i < k; i++) ans = std::min(ans, int(1LL * f[i] * inv % MOD));
	io.put(ans, '\n');
	return 0;
}
