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
	inline void print(const char *s) {
		for (; *s; s++) putchar(*s);
	}
	inline void puts(const char *s) {
		print(s);
		putchar(10);
	}
};
#define MAXN 300010
int t, n, m;
int head[MAXN], next[MAXN << 1], to[MAXN << 1], tot;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
void dfs(int x, int fa, int *dis) {
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		dis[to[i]] = dis[x] + 1;
		dfs(to[i], x, dis);
	}
}
int u[MAXN], v[MAXN], d[MAXN], d0[MAXN], d1[MAXN], d2[MAXN], d3[MAXN];
int main() {
	IOX io;
	d0[0] = 0x3F3F3F3F;
	for (t = io.getint(); t; t--) {
		n = io.getint(), m = io.getint();
		memset(head + 1, -1, sizeof(int) * n);
		tot = 0;
		for (int i = 1; i < n; i++) $(io.getint(), io.getint());
		dfs(1, 0, d0);
		int max = -1, best = 0;
		for (int i = 1; i <= m; i++) {
			u[i] = io.getint(), v[i] = io.getint(), d[i] = io.getint();
			int limit = std::max(0, d0[u[i]] + d0[v[i]] - d[i] + 1) >> 1;
			if (limit > max) {
				max = limit;
				best = i;
			}
		}
		d1[u[best]] = d2[v[best]] = 0;
		dfs(u[best], 0, d1);
		dfs(v[best], 0, d2);
		int cnd = 0;
		for (int i = 1; i <= n; i++) {
			if (d1[i] + d2[i] <= d[best]) {
				if (d0[i] < d0[cnd]) cnd = i;
			}
		}
		if (!cnd) goto fail;
		d3[cnd] = 0;
		dfs(cnd, 0, d3);
		for (int i = 1; i <= m; i++) {
			if (d3[u[i]] + d3[v[i]] > d[i]) goto fail;
		}
		io.print("TAK ");
		io.putint(cnd);
		io.putchar(10);
		continue;
	fail:
		io.puts("NIE");
	}
	return 0;
}