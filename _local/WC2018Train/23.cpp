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
		for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
		return f ? -x : x;
	}
	inline unsigned getuint() {
		register unsigned x = 0;
		register char ch = getchar();
		for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
		return x;
	}
	inline long long getint64() {
		register long long x = 0, f = 0;
		register char ch = getchar();
		for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
		for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
		return f ? -x : x;
	}
	inline unsigned long long getuint64() {
		register unsigned long long x = 0;
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
#define MAXN 500010
typedef long long lnt;
int n, m, l[MAXN], r[MAXN], tmp[MAXN << 2];
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
lnt ans = 0;
void gao(int x, int fa) {
	if (x <= m) return;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		gao(to[i], x);
	}
	int t = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		tmp[++t] = l[to[i]], tmp[++t] = r[to[i]];
	}
	std::sort(tmp + 1, tmp + t + 1);
	l[x] = tmp[t / 2], r[x] = tmp[t / 2 + 1];
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		if (l[to[i]] > l[x] || r[to[i]] < l[x]) {
			ans += std::min(std::abs(l[x] - l[to[i]]), std::abs(l[x] - r[to[i]]));
		}
	}
}
int main() {
	IOX io;
	memset(head, -1, sizeof(head));
	n = io.getint();
	m = io.getint();
	for (int i = 1; i < n; i++) $(io.getint(), io.getint());
	for (int i = 1; i <= m; i++) l[i] = r[i] = io.getint();
	if (n == 1) return io.puts("0"), 0;
	if (n == 2) return io.putint(std::abs(l[1] - l[2])), io.putchar(10), 0;
	gao(n, 0);
	io.putint64(ans);
	io.putchar(10);
	return 0;
}