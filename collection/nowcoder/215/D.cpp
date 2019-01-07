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
	}
};
#include <vector>
#define MAXN 100010
int vis[MAXN], pr[MAXN], low[MAXN], pnt = 0;
inline void shai() {
	for (int i = 2; i < MAXN; i++) {
		if (!vis[i]) pr[++pnt] = i, low[i] = i;
		for (int j = 1; j <= pnt; j++) {
			if (i * pr[j] >= MAXN) break;
			vis[i * pr[j]] = 1;
			low[i * pr[j]] = pr[j];
			if (i % pr[j] == 0) break;
		}
	}
}
int n, x, k, p, sum[MAXN], f[MAXN], tmp1[MAXN], tmp2[MAXN];
inline int fuck(register int x, register int p, register int MOD) {
	register int y = 1;
	for (; p; p >>= 1) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return y;
}
int *cd[MAXN], size[MAXN], pool[2000000], *last = pool;
int tmp[MAXN];
int main() {
	shai();
	IOX io;
	n = io.getint();
	for (int i = 1; i < 100001; i++) {
		int t1 = 0, t2 = 0;
		for (int j = 1; j * j <= i; j++) {
			if (i % j) continue;
			tmp1[t1++] = j;
			if (j * j == i) continue;
			tmp2[t2++] = i / j;
		}
		size[i] = t1 + t2;
		std::reverse(tmp2, tmp2 + t2);
		cd[i] = last;
		last += size[i];
		memcpy(cd[i], tmp1, sizeof(int) * t1);
		memcpy(cd[i] + t1, tmp2, sizeof(int) * t2);
	}
	for (int t = 1; t <= n; t++) {
		register int x, k, p;
		x = io.getint(), k = io.getint(), p = io.getint();
		register int c = size[x], ans = 0;
		for (int i = 0; i < c; i++) {
			int now = cd[x][i];
			f[now] = 0;
			if (vis[now]) {
				tmp[now] = 1LL * tmp[now / low[now]] * tmp[low[now]] % p;
			} else {
				tmp[now] = fuck(now, k, p);
			}
		}
		for (int i = c - 1; i >= 0; i--) {
			int now = cd[x][i];
			sum[now]++;
			f[now] += sum[now];
			for (int j = 0; j < size[now] - 1; j++) {
				f[cd[now][j]] -= f[now];
			}
			ans += 1LL * tmp[now] * f[now] % p;
			if (ans >= p) ans -= p;
		}
		io.putint(ans);
		io.putchar(10);
	}
}