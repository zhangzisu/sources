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
		if (ip == ib + is) throw EOF;
		return *ip++;
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
int head[MAXN], to[MAXN], next[MAXN], tot, root, ans;
inline void $(int u, int v) { next[tot] = head[u], to[tot] = v, head[u] = tot++; }
int n, p[MAXN], v[MAXN], Q[MAXN], H, T, amin[MAXN], amax[MAXN], bmin[MAXN], bmax[MAXN], cmin[MAXN], cmax[MAXN], L[MAXN], R[MAXN];
int main() {
	try {
		for (;;) {
			n = io.getint();
			memset(head + 1, -1, sizeof(int) * n);
			tot = ans = T = 0, H = 1;
			memset(amin + 1, 0, sizeof(int) * n);
			memset(amax + 1, 0, sizeof(int) * n);
			memset(cmin + 1, 0, sizeof(int) * n);
			memset(cmax + 1, 0, sizeof(int) * n);
			for (int i = 1; i <= n; i++) {
				if ((p[i] = io.getint())) {
					$(p[i], i);
				} else {
					root = i;
				}
				v[i] = io.getint();
			}
			Q[++T] = root;
			while (H <= T) {
				int x = Q[H++];
				L[x] = T + 1;
				for (int i = head[x]; ~i; i = next[i]) Q[++T] = to[i];
				R[x] = T;
			}
			for (int _ = n; _ >= 1; _--) {
				int x = Q[_], l = L[x], r = R[x];
				if (l <= r) {
					for (int i = l; i <= r; i++) {
						amin[x] = std::min(amin[x], amin[Q[i]]);
						amax[x] = std::max(amax[x], amax[Q[i]]);
					}
				}
				amin[x] = std::min(amin[x] + v[x], 0);
				amax[x] = std::max(amax[x] + v[x], 0);
			}
			for (int _ = 1; _ <= n; _++) {
				int x = Q[_], l = L[x], r = R[x];
				if (l <= r) {
					bmin[r] = amin[Q[r]], bmax[r] = amax[Q[r]];
					for (int i = r - 1; i >= l; i--) bmin[i] = std::min(bmin[i + 1], amin[Q[i]]), bmax[i] = std::max(bmax[i + 1], amax[Q[i]]);
					int dmin = std::min(0, cmin[x]), dmax = std::max(0, cmax[x]);
					for (int i = l; i < r; i++) {
						cmin[Q[i]] = std::min(0, std::min(dmin, bmin[i + 1]) + v[x]);
						cmax[Q[i]] = std::max(0, std::max(dmax, bmax[i + 1]) + v[x]);
						dmin = std::min(dmin, amin[Q[i]]);
						dmax = std::max(dmax, amax[Q[i]]);
					}
					cmin[Q[r]] = std::min(0, dmin + v[x]);
					cmax[Q[r]] = std::max(0, dmax + v[x]);
				}
			}
			for (int i = 1; i <= n; i++) {
				ans = std::max(ans, std::min(-cmin[i], amax[i]));
				ans = std::max(ans, std::min(cmax[i], -amin[i]));
			}
			io.put(ans, '\n');
		}
	} catch (...) {
		return 0;
	}
	return 0;
}
