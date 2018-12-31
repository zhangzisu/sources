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
#include <vector>
#define MAXN 310
#define MAXM 50010
namespace HLPPImpl {
typedef long long lnt;
const lnt INF = (~0ULL) >> 2;
int head[MAXN], to[MAXM << 1], next[MAXM << 1], cap[MAXM << 1], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, cap[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, cap[tot] = 0, head[v] = tot++;
}
int n, s, t, h[MAXN], gap[MAXN], inq[MAXN];
lnt prs[MAXN];
inline int HLPP() {
	std::priority_queue<std::pair<int, int>> Q;
	h[s] = n;
	prs[s] = INF;
	inq[s] = 1;
	Q.emplace(h[s], s);
	gap[0] = n - 1;
	while (Q.size()) {
		int x = Q.top().second;
		Q.pop();
		if (!prs[x] || x == t) continue;
		for (int i = head[x]; ~i; i = next[i]) {
			if (x == s || h[to[i]] + 1 == h[x]) {
				int flow = std::min(prs[x], (lnt)cap[i]);
				if (flow) {
					cap[i] -= flow, cap[i ^ 1] += flow, prs[x] -= flow, prs[to[i]] += flow;
					if (to[i] != s && !inq[to[i]]) {
						Q.emplace(h[to[i]], to[i]);
						inq[to[i]] = 1;
					}
					if (!prs[x]) break;
				}
			}
		}
		if (x != s && prs[x]) {
			if (!--gap[h[x]]) {
				int th = h[x];
				for (int i = 1; i <= n; i++) {
					if (i != s && i != t && h[i] >= th) h[i] = n, prs[i] = 0;
				}
				continue;
			}
			h[x] = n;
			for (int i = head[x]; ~i; i = next[i]) {
				if (cap[i]) {
					h[x] = std::min(h[x], h[to[i]] + 1);
				}
			}
			++gap[h[x]];
			Q.emplace(h[x], x);
		} else {
			inq[x] = 0;
		}
	}
	return prs[t];
}
}  // namespace HLPPImpl
std::vector<int> go[MAXN];
int n = io.getint(), ans = 0, match[MAXN], vis[MAXN];
int dfs(int x) {
	for (int y : go[x]) {
		if (vis[y]) continue;
		vis[y] = 1;
		if (!match[y] || dfs(match[y])) return match[y] = x, 1;
	}
	return 0;
}
int main() {
	for (int i = 1; i <= n; i++) {
		for (int j = io.getint(); j; j--) {
			go[i].push_back(io.getint());
		}
	}
	for (int i = 1; i <= n; i++) memset(vis, 0, sizeof(vis)), dfs(i);
	memset(HLPPImpl::head, -1, sizeof(HLPPImpl::head));
	HLPPImpl::s = n + 1, HLPPImpl::t = HLPPImpl::n = n + 2;
	for (int i = 1; i <= n; i++) {
		int x = -io.getint();
		if (x > 0) {
			ans += x;
			HLPPImpl::$(HLPPImpl::s, i, x);
		} else if (x < 0) {
			HLPPImpl::$(i, HLPPImpl::t, -x);
		}
		for (auto j : go[i]) {
			if (match[j] != i) {
				HLPPImpl::$(i, match[j], 0x3F3F3F3F);
			}
		}
	}
	io.put(HLPPImpl::HLPP() - ans, '\n');
	return 0;
}