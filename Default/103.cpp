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
#define MAXN 250010
#define MOD 998244353
inline void trim(int &x) { x -= MOD, x += (x >> 31) & MOD; }
inline void up(int &x, int y) { trim(x += y); }
using vector_t = int[4];
using matrix_t = int[4][4];
const matrix_t ONE = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
inline void mul(const matrix_t &a, const matrix_t &b, matrix_t &c) {
	memset(c, 0, sizeof(c));
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			if (!a[i][k]) continue;
			for (int j = 0; j < 4; j++) {
				if (!b[k][j]) continue;
				up(c[i][j], 1LL * a[i][k] * b[k][j] % MOD);
			}
		}
	}
}
inline void mul(const matrix_t &a, const vector_t &b, vector_t &c) {
	memset(c, 0, sizeof(c));
	for (int j = 0; j < 4; j++) {
		if (!b[j]) continue;
		for (int i = 0; i < 4; i++) {
			if (!a[i][j]) continue;
			up(c[i], 1LL * a[i][j] * b[j] % MOD);
		}
	}
}
vector_t val[MAXN << 2], vt;
matrix_t tag[MAXN << 2], mt;
int dirty[MAXN << 2];
void build(int n, int l, int r) {
	val[n][3] = r - l + 1;
	memcpy(tag[n], ONE, sizeof(ONE));
	if (l == r) {
		val[n][0] = io.getint();
		val[n][1] = io.getint();
		val[n][2] = io.getint();
		return;
	}
	int mid = (l + r) >> 1;
	build(n << 1, l, mid);
	build(n << 1 | 1, mid + 1, r);
	trim(val[n][0] = val[n << 1][0] + val[n << 1 | 1][0]);
	trim(val[n][1] = val[n << 1][1] + val[n << 1 | 1][1]);
	trim(val[n][2] = val[n << 1][2] + val[n << 1 | 1][2]);
}
inline void pushDown(int n) {
	if (dirty[n]) {
		mul(tag[n], tag[n << 1], mt), memcpy(tag[n << 1], mt, sizeof(mt));
		mul(tag[n], val[n << 1], vt), memcpy(val[n << 1], vt, sizeof(vt));
		mul(tag[n], tag[n << 1 | 1], mt), memcpy(tag[n << 1 | 1], mt, sizeof(mt));
		mul(tag[n], val[n << 1 | 1], vt), memcpy(val[n << 1 | 1], vt, sizeof(vt));
		dirty[n << 1] = dirty[n << 1 | 1] = 1;
		memcpy(tag[n], ONE, sizeof(ONE));
		dirty[n] = 0;
	}
}
void apply(int n, int l, int r, int L, int R, const matrix_t &v) {
	if (l == L && r == R) {
		mul(v, tag[n], mt), memcpy(tag[n], mt, sizeof(mt));
		mul(v, val[n], vt), memcpy(val[n], vt, sizeof(vt));
		dirty[n] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	pushDown(n);
	if (R <= mid) {
		apply(n << 1, l, mid, L, R, v);
	} else if (L > mid) {
		apply(n << 1 | 1, mid + 1, r, L, R, v);
	} else {
		apply(n << 1, l, mid, L, mid, v);
		apply(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	}
	trim(val[n][0] = val[n << 1][0] + val[n << 1 | 1][0]);
	trim(val[n][1] = val[n << 1][1] + val[n << 1 | 1][1]);
	trim(val[n][2] = val[n << 1][2] + val[n << 1 | 1][2]);
}
void query(int n, int l, int r, int L, int R, int &a, int &b, int &c) {
	if (l == L && r == R) {
		up(a, val[n][0]);
		up(b, val[n][1]);
		up(c, val[n][2]);
		return;
	}
	int mid = (l + r) >> 1;
	pushDown(n);
	if (R <= mid) return query(n << 1, l, mid, L, R, a, b, c);
	if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R, a, b, c);
	query(n << 1, l, mid, L, mid, a, b, c);
	query(n << 1 | 1, mid + 1, r, mid + 1, R, a, b, c);
}
int n = io.getint();
const matrix_t OP1 = {{1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
const matrix_t OP2 = {{1, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
const matrix_t OP3 = {{1, 0, 0, 0}, {0, 1, 0, 0}, {1, 0, 1, 0}, {0, 0, 0, 1}};
matrix_t OP4 = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
matrix_t OP5 = {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
matrix_t OP6 = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}};
int main() {
	build(1, 1, n);
	for (int m = io.getint(); m; m--) {
		int op = io.getint(), l = io.getint(), r = io.getint(), v = op >= 4 && op <= 6 ? io.getint() : 0;
		switch (op) {
			case 1:
				apply(1, 1, n, l, r, OP1);
				break;
			case 2:
				apply(1, 1, n, l, r, OP2);
				break;
			case 3:
				apply(1, 1, n, l, r, OP3);
				break;
			case 4:
				OP4[0][3] = v;
				apply(1, 1, n, l, r, OP4);
				break;
			case 5:
				OP5[1][1] = v;
				apply(1, 1, n, l, r, OP5);
				break;
			case 6:
				OP6[2][3] = v;
				apply(1, 1, n, l, r, OP6);
				break;
			case 7:
				int a = 0, b = 0, c = 0;
				query(1, 1, n, l, r, a, b, c);
				io.put(a, ' ', b, ' ', c, '\n');
				break;
		}
	}
	return 0;
}
