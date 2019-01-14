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
} io;
#define MAXN 110
#define MAXV 100010
using matrix = int[MAXN][MAXN];
int pri[MAXV], vis[MAXV], pnt = 0;
inline void shai() {
	for (int i = 2; i < MAXV; i++) {
		if (!vis[i]) pri[++pnt] = i;
		for (int j = i + i; j < MAXV; j += i) vis[j] = 1;
	}
}
int MOD;
inline void trim(int &x) { x -= MOD, x += (x >> 31) & MOD; }
inline void up(int &x, int y) { trim(x += y); }
inline int fuck(int x, int y) {
	int z = 1;
	for (; y; y >>= 1) {
		if (y & 1) z = 1LL * z * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return z;
}
int fac[MAXV], fnt = 0;
inline int isRt(int g) {
	for (int i = 1; i <= fnt; i++) {
		if (fuck(g, (MOD - 1) / fac[i]) == 1) return 0;
	}
	return 1;
}
inline int getRt() {
	int phi = MOD - 1;
	for (int i = 1; pri[i] * pri[i] <= phi; i++) {
		if (phi % pri[i]) continue;
		while (phi % pri[i] == 0) phi /= pri[i];
		fac[++fnt] = pri[i];
	}
	if (phi != 1) fac[++fnt] = phi;
	for (int i = 2; i < MOD; i++)
		if (isRt(i)) return i;
	throw "GG";
}
inline int det(matrix &a, int n) {
	int ret = 1;
	for (int i = 0; i < n; i++) {
		int p = i;
		while (!a[p][i] && p < n) p++;
		if (p >= n) return 0;
		if (p != i) {
			for (int j = i; j < n; j++) std::swap(a[i][j], a[p][j]);
		}
		ret = 1LL * ret * a[i][i] % MOD;
		int inv = fuck(a[i][i], MOD - 2);
		for (p = i + 1; p < n; p++) {
			if (!a[p][i]) continue;
			int delta = 1LL * a[p][i] * inv % MOD;
			for (int j = i; j < n; j++) {
				up(a[p][j], MOD - 1LL * a[i][j] * delta % MOD);
			}
		}
	}
	return ret;
}
int n = io.getint(), m = io.getint();
matrix a, b, c;
int main() {
	srand(time(NULL));
	shai();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = io.getint();
		}
	}
	MOD = 233 * m + 1;
	while (vis[MOD]) MOD += m;
	int g = getRt();
	int rt = fuck(g, (MOD - 1) / m);
	// printf(">>> MOD = %d, G = %d, rt = %d\n", MOD, g, rt);
	for (int gao = 10; gao; gao--) {
		int sum = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				c[i][j] = rand() + 1;
			}
		}
		for (int base = 0; base < m; base++) {
			int x = fuck(rt, base);
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					b[i][j] = ~a[i][j] ? 1LL * fuck(x, a[i][j]) * c[i][j] % MOD : 0;
				}
			}
			up(sum, det(b, n));
		}
		if (sum) {
			io.put("Yes\n");
			return 0;
		}
	}
	io.put("No\n");
	return 0;
}