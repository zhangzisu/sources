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
	inline int getint() {
		register int x = 0, f = 0;
		register char ch = getchar();
		for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
		for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
		return f ? -x : x;
	}
	inline unsigned getuint() {
		register unsigned x = 0;
		register char ch = getchar();
		for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
		return x;
	}
	inline unsigned long long getuint64() {
		register unsigned long long x = 0;
		register char ch = getchar();
		for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
		return x;
	}
	inline char getalpha() {
		register char ch = getchar();
		while (!isalpha(ch)) ch = getchar();
		return ch;
	}
	inline void putint(int x) {
		if (!x) return putchar('0');
		if (x < 0) putchar(45), x = -x;
		register int _6;
		for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
		while (_6) putchar(tmp[_6--]);
	}
	inline void putint64(long long x) {
		if (!x) return putchar('0');
		if (x < 0) putchar(45), x = -x;
		register int _6;
		for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
		while (_6) putchar(tmp[_6--]);
	}
	inline void puts(const char *s) {
		for (; *s; s++) putchar(*s);
		putchar(10);
	}
};
#define MOD 998244353
#define G 3
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline int trim(int x) { return x >= MOD ? x - MOD : x; }
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
	for (int k = 1; k < n; k <<= 1) {
		int t = k << 1;
		int wn = fuck(G, (MOD - 1) / t);
		for (int i = 0; i < n; i += t) {
			for (int j = 0, w = 1; j < k; j++, w = 1LL * w * wn % MOD) {
				int x = a[i + j], y = 1LL * w * a[i + j + k] % MOD;
				a[i + j] = trim(x + y);
				a[i + j + k] = trim(x - y + MOD);
			}
		}
	}
}
const int N = 1 << 23;
int n, m, k, len, f[N], g[N];
char op[N];
int main() {
	IOX io;
	n = io.getint(), m = io.getint(), k = io.getint();
	len = n * m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			f[i * m + j] = io.getdigit();
		}
	}
	int cx = 0, cy = 0, minx = 0, miny = 0, maxx = 0, maxy = 0;
	for (int i = 0; i < k; i++) {
		switch (op[i] = io.getalpha()) {
			case 'w':
				cx--;
				break;
			case 'a':
				cy--;
				break;
			case 's':
				cx++;
				break;
			case 'd':
				cy++;
				break;
		}
		minx = std::min(minx, cx);
		miny = std::min(miny, cy);
		maxx = std::max(maxx, cx);
		maxy = std::max(maxy, cy);
	}
	cx = -minx, cy = -miny;
	g[cx * m + cy] = 1;
	for (int i = 0; i < k; i++) {
		switch (op[i]) {
			case 'w':
				cx--;
				break;
			case 'a':
				cy--;
				break;
			case 's':
				cx++;
				break;
			case 'd':
				cy++;
				break;
		}
		g[cx * m + cy] = 1;
	}
	std::reverse(g, g + len);
    // fprintf(stderr, "Input done\n");
	NTT(f, N);
    // fprintf(stderr, "NTT #1 done\n");
	NTT(g, N);
    // fprintf(stderr, "NTT #2 done\n");
	for (int i = 0; i < N; i++) f[i] = 1LL * f[i] * g[i] % MOD;
	NTT(f, N);
    // fprintf(stderr, "NTT #3 done\n");
	std::reverse(f + 1, f + N);
	for (int i = 0, inv = fuck(N, MOD - 2); i < N; i++) f[i] = 1LL * f[i] * inv % MOD;
	int ans = 0;
	for (int i = 0; i < n - (maxx - minx); i++) {
		for (int j = 0; j < m - (maxy - miny); j++) {
			ans += !f[i * m + j + len - 1];
		}
	}
    io.putint(ans);
    io.putchar(10);
	return 0;
}