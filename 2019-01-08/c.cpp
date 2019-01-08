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
#define MAXN 2000010
#define MOD 998244353
#define G 3
inline int fuck(int x, int y) {
	int z = 1;
	for (; y; y >>= 1) {
		if (y & 1) z = 1LL * z * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return z;
}
inline void trim(int &x) { x -= MOD, x += (x >> 31) & MOD; }
inline void up(int &x, int y) { trim(x += y); }
const int LEN = (1 << 20);
int rev[LEN];
inline void PRE(int n) {
	for (int i = 1, j = 0; i < n - 1; i++) {
		for (int t = n; ~j & t; j ^= t) t >>= 1;
		rev[i] = j;
	}
}
inline void NTT(int *a, int n) {
	for (int i = 1; i < n - 1; i++) {
		if (i < rev[i]) std::swap(a[i], a[rev[i]]);
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
int m, h[MAXN], a[MAXN], S[MAXN], R[LEN], T[LEN], ans = 0;
inline void solve() {
	int n = 1;
	while (n <= (2 * m)) n <<= 1;
	PRE(n);
	memset(S, 0, sizeof(int) * n), memset(T, 0, sizeof(int) * n), memset(R, 0, sizeof(int) * n);
	S[0] = 1;
	for (int i = 1; i <= m; i++) S[i] = 1LL * S[i - 1] * a[i] % MOD;
	for (int i = 0; i <= m; i++) T[i] = 1LL * S[i] * (MOD + 1 - a[i + 1]) % MOD;
	for (int i = 0; i <= m; i++) R[i] = 1LL * (MOD + 1 - a[m - i]) * fuck(S[m - i], MOD - 2) % MOD;
	NTT(T, n), NTT(R, n);
	for (int i = 0; i < n; i++) T[i] = 1LL * T[i] * R[i] % MOD;
	NTT(T, n), std::reverse(T + 1, T + n);
	for (int i = 0, inv = fuck(n, MOD - 2); i < n; i++) T[i] = 1LL * T[i] * inv % MOD;
	for (int i = 1; i <= m; i++) up(ans, 1LL * T[m + i] % MOD * h[i] % MOD);
}
int n = io.getint(), v[MAXN];
int main() {
	for (int i = 1; i <= n; i++) trim(h[i] = io.getint());
	for (int i = 1; i <= n; i++) trim(v[i] = io.getint());
	for (int i = 1; i <= n; i++) {
		if (v[i]) {
			m = 0;
			for (; v[i] && i <= n; i++) a[++m] = v[i];
			a[m + 1] = 0;
			solve();
		}
	}
	io.put(ans, '\n');
	return 0;
}