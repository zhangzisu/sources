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
	}
};
#include <map>
typedef long long lnt;
typedef unsigned long long ulnt;
inline ulnt gcd(ulnt a, ulnt b) {
	return b ? gcd(b, a % b) : a;
}
class pollardRho {
       private:
	inline static ulnt next() {
		static ulnt s = 124124124713812490;
		return s += s << 2 | 1;
	}
	inline static ulnt mul(ulnt a, ulnt b, ulnt c) {
		a %= c, b %= c;
		ulnt t = a * b - (ulnt)((long double)a * b / c + 0.5) * c;
		if (t > c) return t + c;
		return t;
	}
	inline static ulnt pow(ulnt a, ulnt b, ulnt c) {
		ulnt r = 1;
		for (; b; b >>= 1) {
			if (b & 1) r = mul(a, r, c);
			a = mul(a, a, c);
		}
		return r;
	}
	inline static ulnt f(ulnt a, ulnt b, ulnt n) {
		return (mul(a, a, n) + b) % n;
	}

       public:
	std::map<ulnt, int> result;
	inline bool test(ulnt x) {
		if (x == 2) return 1;
		if (x < 2 || (~x & 1)) return 0;
		ulnt u = x - 1, p, a, b;
		int t = 0;
		while (~u & 1) u >>= 1, t++;
		for (int i = 0; i < 5; i++) {
			p = next() % (x - 1) + 1;
			a = pow(p, u, x);
			for (int j = 0; j < t; j++) {
				b = mul(a, a, x);
				if (b == 1 && a != 1 && a != x - 1) return 0;
				a = b;
			}
			if (a != 1) return 0;
		}
		return 1;
	}
	void factor(ulnt n) {
		if (n == 1) return;
		if (test(n)) return void(result[n]++);
		if (n == 4) return void(result[2] += 2);
		for (ulnt a, x, y, p;;) {
			a = next() & 63, x = y = 2;
			while (1) {
				x = f(x, a, n), y = f(f(y, a, n), a, n);
				if (x == y) break;
				p = gcd(n, x >= y ? x - y : y - x);
				if (p > 1) {
					factor(p), factor(n / p);
					return;
				}
			}
		}
	}
} pr;
#include <cassert>
#define MOD 1000000007
#define MAXN 200010
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
std::pair<ulnt, int> factors[MAXN];
ulnt m, a[MAXN], l[MAXN], r[MAXN];
int n, k, lc, rc, best;
void dfsl(int p, ulnt cur) {
	if (p >= k) return void(l[lc++] = cur);
	if ((best >> p) & 1) return dfsl(p + 1, cur);
	dfsl(p + 1, cur);
	for (int i = 0; i < factors[p].second; i++) {
		dfsl(p + 1, cur *= factors[p].first);
	}
}
void dfsr(int p, ulnt cur) {
	if (p >= k) return void(r[rc++] = cur);
	if ((~best >> p) & 1) return dfsr(p + 1, cur);
	dfsr(p + 1, cur);
	for (int i = 0; i < factors[p].second; i++) {
		dfsr(p + 1, cur *= factors[p].first);
	}
}
int f[1000][1000];
inline int query(ulnt pos) {
	int ret = 0;
	int lp = std::lower_bound(l, l + lc, pos / gcd(pos, r[rc - 1])) - l;
	pos /= l[lp];
	for (int i = 0; i < rc; i++) {
		if (r[i] > pos) break;
		if (pos % r[i]) continue;
		up(ret, f[lp][i]);
	}
	return ret;
}
inline void add(ulnt pos, int val) {
	int rp = std::lower_bound(r, r + rc, pos / gcd(pos, l[lc - 1])) - r;
	pos /= r[rp];
	for (int i = lc - 1; ~i; i--) {
		if (l[i] < pos) break;
		if (l[i] % pos) continue;
		up(f[i][rp], val);
	}
}
int main() {
	IOX io;
	n = io.getint(), m = io.getuint64();
	for (int i = 1; i <= n; i++) a[i] = io.getuint64();
	pr.factor(m);
	for (auto v : pr.result) factors[k++] = v;
	int count = 1;
	for (int i = 0; i < k; i++) count *= (factors[i].second + 1);
	for (int d = 1; d < (1 << k); d++) {
		int left = 1, right = 1;
		for (int i = 0; i < k; i++) {
			(((d >> i) & 1) ? left : right) *= (factors[i].second + 1);
		}
		if (left + right < count) {
			count = left + right;
			best = d;
		}
	}
	dfsl(0, 1);
	dfsr(0, 1);
	std::sort(l, l + lc);
	std::sort(r, r + rc);
	for (int i = 1; i <= n; i++) {
		int cur = i == 1 ? 1 : query(a[i]);
		add(a[i], cur);
		io.putint(cur);
		io.putchar(10);
	}
	return 0;
}
