#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
// inline int judge(int mask, int n) {
//     for (int i = 1; i <= n; i++) {
//         if ((mask >> (i - 1)) & 1) {
//             for (int j = i + 2; j <= n; j += 2) {
//                 if ((mask >> (j - 1)) & 1) {
//                     if ((~mask >> (((i + j) / 2) - 1)) & 1) return 0;
//                 }
//             }
//         }
//     }
//     return 1;
// }
// inline int calc(int n) {
//     int ret = 0;
//     for (int i = 0; i < (1 << n); i++) {
//         ret += judge(i, n);
//     }
//     return ret;
// }
#define MAXN 20000010
typedef long long lnt;
int vis[MAXN], pri[MAXN], cnt[MAXN], lst[MAXN], pnt = 0;
lnt f[MAXN], g[MAXN];
inline void shai() {
	f[1] = 1;
	for (register int i = 2; i < MAXN; i++) {
		if (!vis[i]) {
			pri[++pnt] = lst[i] = i;
			cnt[i] = f[i] = 2;
		}
		for (int j = 1, next; j <= pnt; j++) {
			if ((next = i * pri[j]) >= MAXN) break;
			vis[next] = 1;
			lst[next] = pri[j];
			if (i % pri[j]) {
				f[next] = f[i] * 2;
				cnt[next] = 2;
			} else {
				f[next] = f[i] / cnt[i] * (cnt[i] + 1);
				cnt[next] = cnt[i] + 1;
				break;
			}
		}
	}
	for (register int i = 1; i < MAXN; i++)
		if (~i & 1) f[i] = f[i >> 1];
	for (register int i = 1; i < MAXN; i++) f[i] += f[i - 1];
	for (register int i = 1; i < MAXN; i++) f[i] += f[i - 1];
	for (register int i = 1; i < MAXN; i++) g[i] = 1 + i + f[i - 1];
}
int main() {
	IOX io = IOX();
	shai();
	for (int t = io.getint(); t; t--) io.putint64(g[io.getint()]), io.putchar(10);
	return 0;
}