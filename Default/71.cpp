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
	inline int specialget() {
		register char ch = getchar();
		register int x = 0;
		for (; ch == '?'; ch = getchar()) x++;
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
#include <set>
#include <vector>
namespace HLPPImpl {
typedef long long lnt;
const lnt INF = (~0ULL) >> 2;
int head[100], to[600], next[600], cap[600], tot;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, cap[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, cap[tot] = 0, head[v] = tot++;
	// fprintf(stderr, "%d - %d: %d\n", u, v, w);
}
int n, s, t, h[400], gap[400], inq[400];
lnt prs[400];
inline void init() {
	memset(head, -1, sizeof(head)), tot = 0;
	memset(h, 0, sizeof(h));
	memset(gap, 0, sizeof(gap));
	memset(inq, 0, sizeof(inq));
	memset(prs, 0, sizeof(prs));
}
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
int n = io.getint(), m, c[10], g[10][10], p[10], vis[10], pos[10][10][2], cur[10], pw[10];
std::set<int> S;
std::vector<std::pair<int, int>> ans;
inline void solve() {
	memset(vis, 0, sizeof(vis)), S.clear(), ans.clear();
	for (int i = 1; i <= m - 2; i++) vis[p[i]]++;
	for (int i = 1; i <= m; i++) {
		if (!vis[i]) S.insert(i);
	}
	for (int i = 1; i <= m - 2; i++) {
		int v = *S.begin();
		if (!g[v][p[i]] && !g[p[i]][v]) return;
		ans.emplace_back(v, p[i]);
		S.erase(v);
		if (!--vis[p[i]]) S.insert(p[i]);
	}
	if (!g[*S.begin()][*S.rbegin()]) return;
	ans.emplace_back(*S.begin(), *S.rbegin());
	for (auto &item : ans) {
		if (item.first > item.second) std::swap(item.first, item.second);
		g[item.first][item.second]--;
	}
	HLPPImpl::init();
	HLPPImpl::n = 0;
	HLPPImpl::s = ++HLPPImpl::n;							 // 1
	HLPPImpl::t = ++HLPPImpl::n;							 // 2
	for (int i = 1; i <= m; i++) HLPPImpl::$(HLPPImpl::s, ++HLPPImpl::n, c[i] - 1);  // 2 + i
	for (int i = 1; i <= m; i++) {
		for (int j = i; j <= m; j++) {
			int cur = ++HLPPImpl::n;
			HLPPImpl::$(cur, HLPPImpl::t, g[i][j]);
			pos[i][j][0] = HLPPImpl::tot + 1;
			HLPPImpl::$(2 + i, cur, g[i][j]);
			pos[i][j][1] = HLPPImpl::tot + 1;
			HLPPImpl::$(2 + j, cur, g[i][j]);
		}
	}
	if (HLPPImpl::HLPP() == n - m) {
		for (auto item : ans) io.put(pw[item.first], ' ', pw[item.second], '\n');
		for (int i = 1; i <= m; i++) {
			for (int j = i; j <= m; j++) {
				for (int k = 1; k <= HLPPImpl::cap[pos[i][j][0]]; k++) {
					io.put(pw[j], ' ', cur[i]++, '\n');
				}
				for (int k = 1; k <= HLPPImpl::cap[pos[i][j][1]]; k++) {
					io.put(pw[i], ' ', cur[j]++, '\n');
				}
			}
		}
		exit(0);
	} else {
		for (const auto &item : ans) g[item.first][item.second]++;
	}
}
void dfs(int d) {
	if (d > m - 2) return solve();
	for (int i = 1; i <= m; i++) {
		p[d] = i;
		dfs(d + 1);
	}
}
int main() {
	for (int i = 1; i <= n; i *= 10) {
		++m;
		c[m] = std::min(i * 10, n + 1) - i;
		pw[m] = i;
		cur[m] = i + 1;
	}
	for (int i = 1; i < n; i++) {
		int x = io.specialget();
		int y = io.specialget();
		if (x > y) std::swap(x, y);
		if (y > m) {
			io.put(-1, '\n');
			return 0;
		}
		g[x][y]++;
	}
	if (m == 1) {
		for (int i = 1; i < n; i++) io.put(i, ' ', i + 1, '\n');
		return 0;
	} else {
		dfs(1);
	}
	io.put(-1, '\n');
	return 0;
}