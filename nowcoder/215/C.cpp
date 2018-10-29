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
#define MAXN 2010
#define MOD 998244353
int n, k, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
int size[MAXN], f[MAXN][MAXN], g[MAXN], ans = 0;
void dfs(int x, int fa) {
	size[x] = 1;
	f[x][1] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		dfs(to[i], x);
		for (int j = 0; j <= size[x] + size[to[i]]; j++) g[j] = 0;
		for (int j = 0; j <= size[x]; j++) {
			for (int k = 0; k <= size[to[i]]; k++) {
				up(g[j + k], 1LL * f[x][j] * f[to[i]][k] % MOD);
			}
		}
		for (int j = 0; j <= size[x] + size[to[i]]; j++) f[x][j] = g[j];
		size[x] += size[to[i]];
	}
	for (int i = 1; i <= k; i++) up(f[x][0], f[x][i]);
}
int main() {
	IOX io;
	n = io.getint();
	k = io.getint();
	memset(head, -1, sizeof(head));
	for (int i = 1; i < n; i++) $(io.getint(), io.getint());
	dfs(1, 0);
	printf("%d\n", f[1][0]);
	return 0;
}