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
#define MAXN 1000010
int n, m, k, s[MAXN], c[MAXN], t[MAXN], v[MAXN], bit[MAXN];
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int y) {
	for (; x < MAXN; x += lowbit(x)) bit[x] += y;
}
inline int qry(int x) {
	int y = 0;
	for (; x; x -= lowbit(x)) y += bit[x];
	return y;
}
int next[MAXN], ans[MAXN], res = 0;
int main() {
	IOX io;
	n = io.getint(), m = io.getint();
	for (int i = 1; i <= n; i++) s[io.getint()] = i;
	for (int i = 1; i <= m; i++) v[i] = t[i] = io.getint();
	std::sort(v + 1, v + m + 1);
	k = std::unique(v + 1, v + m + 1) - v - 1;
	for (int i = 1; i <= n; i++) c[i] = qry(s[i]), add(s[i], 1);
	memset(bit, 0, sizeof(bit));
	for (int i = 2, p = 0; i <= n; i++) {
		while (qry(s[i]) != c[p + 1]) {
			for (int j = i - p; j < i - next[p]; j++) add(s[j], -1);
			p = next[p];
		}
		next[i] = ++p;
		add(s[i], 1);
	}
	memset(bit, 0, sizeof(bit));
	for (int i = 1, p = 0; i <= m; i++) {
		t[i] = std::lower_bound(v + 1, v + k + 1, t[i]) - v;
		while (p == n || qry(t[i]) != c[p + 1]) {
			for (int j = i - p; j < i - next[p]; j++) add(t[j], -1);
			p = next[p];
		}
		if (++p == n) {
			ans[++res] = i - n + 1;
		}
		add(t[i], 1);
	}
	printf("%d\n", res);
	for (int i = 1; i <= res; i++) printf("%d%c", ans[i], " \n"[i == res]);
	return 0;
}