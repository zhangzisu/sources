#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
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
	inline int nextDigit() {
		register char ch = getchar();
		while (!isdigit(ch)) ch = getchar();
		return ch ^ 48;
	}
	inline char nextAlpha() {
		register char ch = getchar();
		while (!isalpha(ch)) ch = getchar();
		return ch;
	}
	inline int32_t nextInt32() {
		register int32_t x = 0;
		register bool f = 0;
		register char ch = getchar();
		for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
		for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
		return f ? -x : x;
	}
	inline uint32_t nextUInt32() {
		register uint32_t x = 0;
		register char ch = getchar();
		for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
		return x;
	}
	inline int64_t nextInt64() {
		register int64_t x = 0;
		register bool f = 0;
		register char ch = getchar();
		for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
		for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
		return f ? -x : x;
	}
	inline uint64_t nextUInt64() {
		register uint64_t x = 0;
		register char ch = getchar();
		for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
		return x;
	}
	inline std::string next() {
		std::string ret;
		register char ch = getchar();
		while (!isalpha(ch)) ch = getchar();
		for (; isalpha(ch); ch = getchar()) ret.push_back(ch);
		return ret;
	}
	inline std::string gets() {
		std::string ret;
		register char ch = getchar();
		for (; ch != '\r' && ch != '\n'; ch = getchar()) ret.push_back(ch);
		return ret;
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
#include <string>
#define MAXN 2010
#define MAXL 10000010
#define MAXM 1000010
const int INF = 0x3F3F3F3F;
int son[MAXL][2], fail[MAXL], id[MAXL], cnt = 1;
std::queue<int> Q;
inline void build() {
	son[0][0] = son[0][1] = 1;
	fail[1] = 0;
	Q.push(1);
	while (Q.size()) {
		int x = Q.front();
		Q.pop();
		for (int i = 0; i < 2; i++) {
			int &y = son[x][i];
			if (y) {
				fail[y] = son[fail[x]][i];
				Q.push(y);
			} else {
				y = son[fail[x]][i];
			}
		}
		if (!id[x]) id[x] = id[fail[x]];
	}
}
int n = io.nextInt32(), G[MAXN][MAXN];
std::string buf[MAXN];
int head[MAXN], to[MAXM], cap[MAXM], next[MAXM], tot = 0;
inline void $(int u, int v, int c) {
	next[tot] = head[u], to[tot] = v, cap[tot] = c, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, cap[tot] = 0, head[v] = tot++;
}
int level[MAXN], cur[MAXN];
inline int bfs(int s, int t) {
	memset(level, 0, sizeof(level));
	memcpy(cur, head, sizeof(cur));
	level[s] = 1;
	Q.push(s);
	while (Q.size()) {
		int x = Q.front();
		Q.pop();
		for (int i = head[x]; ~i; i = next[i]) {
			if (!level[to[i]] && cap[i]) {
				level[to[i]] = level[x] + 1;
				Q.push(to[i]);
			}
		}
	}
	return level[t];
}
inline int dfs(int x, int t, int flow) {
	if (x == t) return flow;
	int ret = 0;
	for (int &i = cur[x]; ~i; i = next[i]) {
		if (level[to[i]] == level[x] + 1 && cap[i]) {
			int tmp = dfs(to[i], t, std::min(flow, cap[i]));
			flow -= tmp, cap[i] -= tmp, ret += tmp, cap[i ^ 1] += tmp;
			if (!flow) return ret;
		}
	}
	return ret;
}
inline int dinic(int s, int t) {
	int ret = 0;
	while (bfs(s, t)) ret += dfs(s, t, INF);
	return ret;
}
int main() {
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= n; i++) {
		buf[i] = io.next();
		int p = 1;
		for (int j = 0; j < (int)buf[i].size(); j++) {
			int &nx = son[p][buf[i][j] == 'b'];
			if (!nx) nx = ++cnt;
			p = nx;
		}
		id[p] = i;
	}
	build();
	for (int i = 1; i <= n; i++) {
		int p = 1;
		for (int j = 0; j < (int)buf[i].size(); j++) {
			p = son[p][buf[i][j] == 'b'];
			if (j == (int)buf[i].size() - 1) p = fail[p];
			if (id[p]) G[i][id[p]] = 1;
		}
	}
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				G[i][j] |= G[i][k] && G[k][j];
			}
		}
	}
	for (int i = 1; i <= n; i++) $(2 * n + 1, i, 1);
	for (int i = 1; i <= n; i++) $(i + n, 2 * n + 2, 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (G[i][j]) {
				// fprintf(stderr, "%d - %d\n", i, j);
				$(i, j + n, 1);
			}
		}
	}
	int ans = n - dinic(2 * n + 1, 2 * n + 2);
	io.put(ans, '\n');
	for (int i = 1; i <= n; i++)
		if (level[i] && !level[i + n]) io.put(i, ' ');
	io.put('\n');
	return 0;
}
