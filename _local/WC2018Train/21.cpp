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
		putchar(10);
	}
};
#define MAXN 200010
int n, m, p[MAXN], val[MAXN], sum[MAXN], P[MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
inline int FIND(int x) { return x == P[x] ? x : P[x] = FIND(P[x]); }
int L[MAXN], R[MAXN], F[MAXN], REV[MAXN], SUM[MAXN];
// void log() {
// 	fprintf(stderr, "===== LOG START =====\n");
// 	fprintf(stderr, "ID\tL\tR\tF\tSUM\n");
// 	for (int i = 1; i <= n; i++) {
// 		if (find(i) == i) {
// 			fprintf(stderr, "%d\t%d\t%d\t%d\t%d\n", i, L[i], R[i], F[i], SUM[i]);
// 		} else {
// 			fprintf(stderr, "%d\t%d\n", i, find(i));
// 		}
// 	}
// 	fprintf(stderr, "=====  LOG END  =====\n");
// }
inline void ensure(int &x) { x = find(x); }
inline int isRoot(int x) {
	ensure(F[x]);
	return !F[x] || (L[F[x]] != x && R[F[x]] != x);
}
inline void reverse(int x) { std::swap(L[x], R[x]), REV[x] ^= 1; }
inline void pushDown(int x) {
	// ensure(F[x]);
	if (!isRoot(x)) pushDown(F[x]);
	if (REV[x]) reverse(L[x]), reverse(R[x]), REV[x] ^= 1;
}
inline void pushUp(int x) {
	SUM[x] = SUM[L[x]] + SUM[R[x]] + sum[x];
}
inline void l(int x) {
	// ensure(F[x]);
	int y = F[x];
	F[R[y] = L[x]] = y;
	(L[F[y]] == y) && (L[F[y]] = x);
	(R[F[y]] == y) && (R[F[y]] = x);
	F[x] = F[y], F[y] = x, L[x] = y;
	pushUp(y);
}
inline void r(int x) {
	// ensure(F[x]);
	int y = F[x];
	F[L[y] = R[x]] = y;
	(L[F[y]] == y) && (L[F[y]] = x);
	(R[F[y]] == y) && (R[F[y]] = x);
	F[x] = F[y], F[y] = x, R[x] = y;
	pushUp(y);
}
inline void splay(int x) {
	pushDown(x);
	while (!isRoot(x)) {
		// ensure(F[x]);
		int y = F[x];
		if (isRoot(y)) {
			x == L[y] ? r(x) : l(x);
		} else {
			if (y == L[F[y]]) {
				x == L[y] ? r(y) : l(x);
				r(x);
			} else {
				x == R[y] ? l(y) : r(x);
				l(x);
			}
		}
	}
	pushUp(x);
}
inline void access(int x) {
	for (int t = 0; x; ensure(F[x]), x = F[x])
		splay(x), R[x] = t, pushUp(x), t = x;
}
inline void set(int x) {
	access(x), splay(x), reverse(x);
}
inline void link(int x, int y) { set(x), F[x] = y; }
inline void merge(int x, int y) {
	if (L[x]) merge(L[x], y);
	if (R[x]) merge(R[x], y);
	L[x] = R[x] = 0;
	if (x == y) return;
	sum[y] += sum[x];
	p[x] = y;
}
int main() {
	/*IOX io;
	n = io.getint(), m = io.getint();
	for (int i = 1; i <= n; i++) {
		SUM[i] = sum[i] = val[i] = io.getint();
		p[i] = P[i] = i;
	}
	// fprintf(stderr, "INPUT DONE\n");
	for (int p, a, b; m; m--) {
		p = io.getint(), a = io.getint(), b = io.getint();
		// if (m % 1000 == 0) fprintf(stderr, "NEXT %d\n", m);
		if (p == 1) {
			a = find(a), b = find(b);
			if (a == b) continue;
			if (FIND(a) != FIND(b)) {
				link(a, b);
				P[FIND(a)] = FIND(b);
			} else {
				set(a), access(b), splay(b), merge(b, b);
			}
		} else if (p == 2) {
			int p = find(a);
			access(p), splay(p);
			sum[p] -= val[a];
			sum[p] += val[a] = b;
			pushUp(p);
		} else {
			a = find(a), b = find(b);
			if (FIND(a) == FIND(b)) {
				// fprintf(stderr, ">>>>>>>>>> NEW RECORD\n");
				set(a), access(b), splay(b);
				// log();
				io.putint(SUM[b]);
				io.putchar(10);
				// fprintf(stderr, ">>>>>>>>>> END RECORD\n");
			} else {
				io.puts("-1");
			}
		}
	}*/
	
	return 0;
}
