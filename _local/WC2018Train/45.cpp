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
#include <deque>
#define MAXN 400
#define MAXM 10010
namespace MCMF_Impl {
const int INF = 0x3F3F3F3F;
int head[MAXN], to[MAXM], next[MAXM], cap[MAXM], cost[MAXM], tot;
int vis[MAXN], dis[MAXN], minCost, s, t;
inline void init() {
	memset(head, -1, sizeof(head));
	tot = 0;
}
inline void $(int u, int v, int c, int w) {
	next[tot] = head[u], to[tot] = v, cap[tot] = c, cost[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, cap[tot] = 0, cost[tot] = -w, head[v] = tot++;
}
inline bool spfa() {
	std::deque<int> Q;
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3F, sizeof(dis));
	dis[t] = 0, vis[t] = 1, Q.push_back(t);
	while (Q.size()) {
		int x = Q.front();
		Q.pop_front();
		for (int i = head[x]; ~i; i = next[i]) {
			if (cap[i ^ 1] && dis[to[i]] > dis[x] + cost[i ^ 1]) {
				dis[to[i]] = dis[x] + cost[i ^ 1];
				if (vis[to[i]]) continue;
				vis[to[i]] = 1;
				Q.size() && dis[to[i]] < dis[Q.front()] ? Q.push_front(to[i]) : Q.push_back(to[i]);
			}
		}
		vis[x] = 0;
	}
	return dis[s] != INF;
}
int dfs(int x, int flow) {
	vis[x] = 1;
	if (x == t) return flow;
	int ret = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (!vis[to[i]] && cap[i] && dis[x] == dis[to[i]] + cost[i]) {
			int tmp = dfs(to[i], std::min(flow, cap[i]));
			ret += tmp, flow -= tmp, cap[i] -= tmp, cap[i ^ 1] += tmp, minCost += cost[i] * tmp;
			if (!flow) break;
		}
	}
	return ret;
}
inline int MCMF() {
	minCost = 0;
	int ret = 0;
	while (spfa()) {
		do {
			memset(vis, 0, sizeof(vis));
			ret += dfs(s, INF);
		} while (vis[t]);
	}
	return ret;
}
};  // namespace MCMF_Impl
const int r = io.getint(), c = io.getint(), dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
inline int convert(char c) {
	switch (c) {
		case 'L':
			return 3;
		case 'R':
			return 1;
		case 'U':
			return 2;
		case 'D':
			return 0;
	}
	return -1;
}
int n, pos[MAXN][MAXN][2];
int main() {
	MCMF_Impl::init();
	MCMF_Impl::s = ++n;
	MCMF_Impl::t = ++n;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			pos[i][j][0] = ++n;
			pos[i][j][1] = ++n;
		}
	}
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			int w = convert(io.getalpha());
			for (int k = 0; k < 4; k++) MCMF_Impl::$(pos[i][j][0], pos[(i + dir[k][0] + r - 1) % r + 1][(j + dir[k][1] + c - 1) % c + 1][1], 1, k != w);
			MCMF_Impl::$(MCMF_Impl::s, pos[i][j][0], 1, 0);
			MCMF_Impl::$(pos[i][j][1], MCMF_Impl::t, 1, 0);
		}
	}
	MCMF_Impl::MCMF();
	printf("%d\n", MCMF_Impl::minCost);
	return 0;
}