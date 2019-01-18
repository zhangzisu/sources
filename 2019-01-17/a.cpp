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
		return ip == ib + is ? EOF : *ip++;
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
	inline int getint() {
		register int x = 0;
		register char ch = getchar();
		while (!isdigit(ch)) ch = getchar();
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
inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int n = io.getint(), m = io.getint();
long long ans = 0;
int a[1000010], b[1000010];
int vis[1000010], pri[1000010], pre[1000010], pnt = 0;
inline void shai() {
	for (int i = 2; i <= 1000000; i++) {
		if (!vis[i]) pri[++pnt] = i, pre[i] = i;
		for (int j = 1; j <= pnt; j++) {
			if (1LL * i * pri[j] > 1000000) break;
			vis[i * pri[j]] = 1;
			pre[i * pri[j]] = pri[j];
			if (i % pri[j] == 0) break;
		}
	}
}
int vb;
int dfs(int v, int x, int cur) {
	if (cur > vb) return 0;
	if (x == 1) {
		int r = 0;
		for (int i = 1; 1LL * i * i * cur <= vb; i++) {
			if (gcd(i, v) != 1) continue;
			r += b[i * i * cur];
		}
		return r;
	}
	int y = pre[x], c = 0, r = 0;
	for (; x % y == 0; x /= y) c++;
	for (int i = 0;; i++, cur = cur * y) {
		if (~std::max(i, c) & 1) {
			r += dfs(v, x, cur);
		}
		if (1LL * cur * y > vb) break;
	}
	return r;
}
int main() {
	shai();
	for (int i = 1; i <= n; i++) a[io.getint()]++;
	for (int i = 1, x; i <= m; i++) {
		x = io.getint();
		vb = std::max(vb, x);
		b[x]++;
	}
	for (int i = 1; i <= 1000000; i++) {
		if (a[i]) {
			ans += 1LL * a[i] * dfs(i, i, 1);
		}
	}
	io.put(ans, '\n');
	return 0;
}
