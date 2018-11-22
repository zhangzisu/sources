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
#define MAXN 100010
const int INF = (~0U) >> 1;
int n, m;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int fa[MAXN], dfn[MAXN], nxt[MAXN], pos[MAXN], top[MAXN];
int deep[MAXN], size[MAXN], dfsclk = 0;
void pre(int x) {
	size[x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x]) continue;
		fa[to[i]] = x;
		deep[to[i]] = deep[x] + 1;
		pre(to[i]);
		size[x] += size[to[i]];
	}
}
void split(int x) {
	pos[dfn[x] = ++dfsclk] = x;
	if (!top[x]) top[x] = x;
	int max = 0;
	for (int i = head[x]; ~i; i = next[i])
		if (to[i] != fa[x] && size[to[i]] > size[max]) max = to[i];
	if (max) nxt[x] = max, top[max] = top[x], split(max);
	for (int i = head[x]; ~i; i = next[i])
		if (to[i] != fa[x] && to[i] != max) split(to[i]);
}
int val[MAXN], min[MAXN << 2], tag[MAXN << 2], root;
inline void pushDown(int n) {
	if (tag[n]) {
		tag[n << 1] = tag[n << 1 | 1] = min[n << 1] = min[n << 1 | 1] = tag[n];
		tag[n] = 0;
	}
}
void build(int n, int l, int r) {
	if (l == r) return void(min[n] = val[pos[l]]);
	int mid = (l + r) >> 1;
	build(n << 1, l, mid);
	build(n << 1 | 1, mid + 1, r);
	min[n] = std::min(min[n << 1], min[n << 1 | 1]);
}
void set(int n, int l, int r, int L, int R, int v) {
	if (L > R) return;
	if (l == L && r == R) return min[n] = tag[n] = v, void();
	int mid = (l + r) >> 1;
	pushDown(n);
	if (R <= mid) {
		set(n << 1, l, mid, L, R, v);
	} else if (L > mid) {
		set(n << 1 | 1, mid + 1, r, L, R, v);
	} else {
		set(n << 1, l, mid, L, mid, v), set(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	}
	min[n] = std::min(min[n << 1], min[n << 1 | 1]);
}
int get(int n, int l, int r, int L, int R) {
	if (L > R) return INF;
	if (l == L && r == R) return min[n];
	int mid = (l + r) >> 1;
	pushDown(n);
	if (R <= mid) return get(n << 1, l, mid, L, R);
	if (L > mid) return get(n << 1 | 1, mid + 1, r, L, R);
	return std::min(get(n << 1, l, mid, L, mid), get(n << 1 | 1, mid + 1, r, mid + 1, R));
}
int main() {
	IOX io = IOX();
	n = io.getint();
	m = io.getint();
	memset(head, -1, sizeof(head));
	for (int i = 1; i < n; i++) $(io.getint(), io.getint());
	for (int i = 1; i <= n; i++) val[i] = io.getint();
	root = io.getint();
	pre(root);
	split(root);
	build(1, 1, n);
	for (int op, u, v, w; m; m--) {
		op = io.getint();
		if (op == 1) {
			root = io.getint();
		} else if (op == 2) {
			u = io.getint(), v = io.getint(), w = io.getint();
			while (top[u] != top[v]) {
				if (deep[top[u]] < deep[top[v]]) std::swap(u, v);
				set(1, 1, n, dfn[top[u]], dfn[u], w);
				u = fa[top[u]];
			}
			if (deep[u] > deep[v]) std::swap(u, v);
			set(1, 1, n, dfn[u], dfn[v], w);
		} else if (op == 3) {
			u = io.getint();
			if (root == u) {
				io.putint(get(1, 1, n, 1, n));
			} else if (dfn[root] >= dfn[u] && dfn[root] < dfn[u] + size[u]) {
				v = root;
				while (top[v] != top[u] && fa[top[v]] != u) v = fa[top[v]];
				u = top[u] == top[v] ? nxt[u] : top[v];
				io.putint(std::min(get(1, 1, n, 1, dfn[u] - 1), get(1, 1, n, dfn[u] + size[u], n)));
			} else {
				io.putint(get(1, 1, n, dfn[u], dfn[u] + size[u] - 1));
			}
            io.putchar(10);
		}
	}
	return 0;
}