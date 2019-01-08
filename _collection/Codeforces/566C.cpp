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
#include <cmath>
#define MAXN 200010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], val[MAXN << 1], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int n, all, root, w[MAXN], size[MAXN], f[MAXN], vis[MAXN];
double calc(int x, int fa, double dis) {
	double ret = sqrt(dis) * dis * w[x];
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		ret += calc(to[i], x, dis + val[i]);
	}
	return ret;
}
double cd(int x, int fa, double dis) {
	double ret = sqrt(dis) * w[x];
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		ret += cd(to[i], x, dis + val[i]);
	}
	return ret;
}
void get(int x, int fa) {
	size[x] = 1, f[x] = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (vis[to[i]] || to[i] == fa) continue;
		get(to[i], x);
		size[x] += size[to[i]];
		f[x] = std::max(f[x], size[to[i]]);
	}
	f[x] = std::max(f[x], all - size[x]);
	if (f[x] < f[root]) root = x;
}
int main() {
	IOX io;
	memset(head, -1, sizeof(head));
	n = io.getint();
	for (int i = 1; i <= n; i++) w[i] = io.getint();
	for (int i = 1; i < n; i++) {
		int u = io.getint(), v = io.getint(), w = io.getint();
		$(u, v, w);
	}
	// for(int i = 1;i <= n;i++)printf("%d: %f\n", i, calc(i, 0, 0));
	f[root = 0] = 0x3F3F3F3F;
	all = n;
	get(1, 0);
	double ans = calc(root, 0, 0);
	int pos = root;
	while (true) {
		// printf("%d\n", root);
		get(root, 0);
		vis[root] = 1;
		int tr = 0;
		double best = -1;
		for (int i = head[root]; ~i; i = next[i]) {
			if (vis[to[i]]) continue;
			double delta = cd(to[i], root, val[i]);
			if (delta > best) {
				best = delta;
				tr = to[i];
			}
		}
		if (!tr) break;
		root = 0;
		all = size[tr];
		get(tr, 0);
		double tmp = calc(root, 0, 0);
		if (tmp < ans) {
			ans = tmp;
			pos = root;
		}
	}
	printf("%d %.10f\n", pos, ans);
	return 0;
}