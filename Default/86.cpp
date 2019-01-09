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
#include <queue>
#define MAXN 60
#define MAXM 30010
const int LEN = 1 << 17;
typedef long long lnt;
inline void FWT(lnt *a, int n) {
	for (int i = 1; i < n; i <<= 1) {
		int t = i << 1;
		for (int j = 0; j < n; j += t) {
			for (int k = 0; k < i; k++) {
				a[j + k] += a[j + k + i];
			}
		}
	}
}
inline void IFWT(lnt *a, int n) {
	for (int i = 1; i < n; i <<= 1) {
		int t = i << 1;
		for (int j = 0; j < n; j += t) {
			for (int k = 0; k < i; k++) {
				a[j + k] -= a[j + k + i];
			}
		}
	}
}
int head[MAXN], to[MAXM], next[MAXM], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int n = io.getint(), m = 0, Q[MAXN], spc[MAXN], d[MAXN], id[MAXN], f[MAXN], ban[MAXN];
lnt G[LEN], H[LEN];
int main() {
	memset(head, -1, sizeof(head));
	{
		register char ch = io.getchar();
		while (ch != '-' && ch != '?') ch = io.getchar();
		for (int i = 1; i <= n; i++, ch = io.getchar()) spc[i] = ch == '?';
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (io.getalpha() == 'Y') $(i, j), d[j]++;
			}
		}
	}
	{
		int H = 1, T = 0;
		for (int i = 1; i <= n; i++) {
			if (!d[i]) Q[++T] = i;
		}
		while (H <= T) {
			int x = Q[H++];
			for (int i = head[x]; ~i; i = next[i]) {
				if (i & 1) continue;
				if (!--d[to[i]]) Q[++T] = to[i];
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (spc[Q[i]]) {
			id[++m] = Q[i];
		}
	}
	int k = (m + 1) >> 1, l = m - k + 1, N = 1 << std::max(k, l);
	id[m + 1] = 2;
	for (int d = 0; d < (1 << (l - 1)); d++) {
		for (int i = 0; i < l - 1; i++) ban[id[k + i + 1]] = (d >> i) & 1;
		memset(f, 0, sizeof(f));
		f[2] = 1;
		for (int _ = n; _ >= 1; _--) {
			int x = Q[_];
			if (ban[x]) continue;
			for (int i = head[x]; ~i; i = next[i]) {
				if (i & 1) continue;
				f[x] ^= f[to[i]];
			}
		}
		int state = 0;
		for (int i = 0; i < l; i++) state |= f[id[k + i + 1]] << i;
		H[state]++;
	}
	for (int d = 0; d < (1 << k); d++) {
		for (int i = 0; i < k; i++) ban[id[i + 1]] = (d >> i) & 1;
		memset(f, 0, sizeof(f));
		f[1] = 1;
		for (int _ = 1; _ <= n; _++) {
			int x = Q[_];
			for (int i = head[x]; ~i; i = next[i]) {
				if (~i & 1) continue;
				if (ban[to[i]]) continue;
				f[x] ^= f[to[i]];
			}
		}
		int state = 0;
		for (int i = 0; i < l; i++) state |= f[id[k + i + 1]] << i;
		G[state]++;
	}
	FWT(G, N), FWT(H, N);
	for (int i = 0; i < N; i++) G[i] *= H[i];
	IFWT(G, N);
	lnt ret = 0;
	for (int i = 0; i < N; i++) {
		if (~__builtin_popcount(i) & 1) ret += G[i];
	}
	io.put(ret, '\n');
	return 0;
}
