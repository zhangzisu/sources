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
} io;
#include <bitset>
const int N = 500;
const int INF = 0x3F3F3F3F;
int n = io.getint(), m = io.getint(), w[N][N], dis[N], tmp[N];
std::bitset<N> g[N][4], Q[4];
int main() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			w[i][j] = io.getint();
			if (w[i][j]) g[i][w[i][j] - 1].set(j);
		}
	}
	while (m--) {
		if (io.getalpha() == 'Q') {
			int x = io.getint() - 1;
			memset(dis, 0x3F, sizeof(dis));
			dis[x] = 0;
			Q[0] = g[x][0], Q[1] = g[x][1], Q[2] = g[x][2], Q[3] = g[x][3];
			for (int cur = 1; Q[0].any() || Q[1].any() || Q[2].any() || Q[3].any(); cur++) {
				int c = 0;
				for (int x = Q[0]._Find_first(); x < N; x = Q[0]._Find_next(x)) {
					if (dis[x] > cur) dis[tmp[c++] = x] = cur;
				}
				Q[0] = Q[1], Q[1] = Q[2], Q[2] = Q[3], Q[3].reset();
				for (int i = 0; i < c; i++) Q[0] |= g[tmp[i]][0], Q[1] |= g[tmp[i]][1], Q[2] |= g[tmp[i]][2], Q[3] |= g[tmp[i]][3];
			}
			int ans = 0;
			for (int i = 0; i < n; i++) {
				ans += (i + 1) * (dis[i] == INF ? 0 : dis[i]);
			}
			io.putint(ans);
			io.putchar(10);
		} else {
			int i = io.getint() - 1, j = io.getint() - 1;
			if (w[i][j]) g[i][w[i][j] - 1].reset(j);
			w[i][j] = io.getint();
			if (w[i][j]) g[i][w[i][j] - 1].set(j);
		}
	}
	return 0;
}