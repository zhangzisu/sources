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
#define MAXN 500010
#define MAXM 50000010
int L[MAXM], R[MAXM], sum[MAXM], cnt = 0;
inline int add(int n, int l, int r, int v) {
	int cur = ++cnt;
	L[cur] = L[n], R[cur] = R[n], sum[cur] = sum[n] + 1;
	if (l == r) return cur;
	int mid = (l + r) >> 1;
	v <= mid ? L[cur] = add(L[n], l, mid, v) : R[cur] = add(R[n], mid + 1, r, v);
	return cur;
}
inline int qry(int n, int m, int l, int r, int _l, int _r) {
	if (l == _l && r == _r) return sum[n] - sum[m];
	int mid = (l + r) >> 1;
	if (_r <= mid) return qry(L[n], L[m], l, mid, _l, _r);
	if (_l > mid) return qry(R[n], R[m], mid + 1, r, _l, _r);
	return qry(L[n], L[m], l, mid, _l, mid) + qry(R[n], R[m], mid + 1, r, mid + 1, _r);
}
inline int find(int n, int m, int l, int r, int k) {
	if (l == r) return l;
	int mid = (l + r) >> 1;
	if ((sum[L[n]] - sum[L[m]]) >= k) return find(L[n], L[m], l, mid, k);
	return find(R[n], R[m], mid + 1, r, k - (sum[L[n]] - sum[L[m]]));
}
int n, root[MAXN], cur = 0;
int main() {
	IOX io;
	n = io.getint();
	for (int opt, l, r, x; n; n--) {
		opt = io.getint();
		if (opt == 0) {
			x = io.getint();
			root[cur + 1] = add(root[cur], 0, 524287, x);
			cur++;
		} else if (opt == 1) {
			int ans = 0;
			l = io.getint(), r = io.getint(), x = io.getint();
			for (int i = 18; i >= 0; i--) {
				int l0 = ans, r0 = ans + (1 << i) - 1;
				int l1 = ans + (1 << i), r1 = ans + (2 << i) - 1;
				int c0 = qry(root[r], root[l - 1], 0, 524287, l0, r0);
				int c1 = qry(root[r], root[l - 1], 0, 524287, l1, r1);
				if (c1 && !(((x >> i) & 1) && c0)) ans |= 1 << i;
			}
			io.putint(ans);
			io.putchar(10);
		} else if (opt == 2) {
			x = io.getint();
			cur -= x;
		} else if (opt == 3) {
			l = io.getint(), r = io.getint(), x = io.getint();
			io.putint(qry(root[r], root[l - 1], 0, 524287, 0, x));
			io.putchar(10);
		} else if (opt == 4) {
			l = io.getint(), r = io.getint(), x = io.getint();
			io.putint(find(root[r], root[l - 1], 0, 524287, x));
			io.putchar(10);
		}
	}
	return 0;
}