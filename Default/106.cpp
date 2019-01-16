#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 65536
int ilen = 0;
char ibuf[BUF], *ipnt = ibuf + BUF;
inline int getChar() {
	if (ipnt == ibuf + BUF) ilen = fread(ibuf, sizeof(char), BUF, stdin), ipnt = ibuf;
	return (ipnt == ibuf + ilen) ? EOF : *ipnt++;
}
inline int getInt() {
	register char ch = getChar();
	register int x = 0;
	while (!isdigit(ch)) ch = getChar();
	for (; isdigit(ch); ch = getChar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
	return x;
}
#include <queue>
#define MAXN 200010
using lnt = long long;
const lnt INF = 0x3F3F3F3F3F3F3F3FLL;
int head[MAXN], to[MAXN << 1], val[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
};
lnt ds[MAXN], dt[MAXN], tag[MAXN << 2];
int fa[MAXN], id[MAXN], pre[MAXN], nxt[MAXN], cnt = 0;
void modify(int n, int l, int r, int L, int R, lnt v) {
	if (l == L && r == R) return tag[n] = std::min(tag[n], v), void();
	int mid = (l + r) >> 1;
	if (R <= mid) return modify(n << 1, l, mid, L, R, v);
	if (L > mid) return modify(n << 1 | 1, mid + 1, r, L, R, v);
	modify(n << 1, l, mid, L, mid, v);
	modify(n << 1 | 1, mid + 1, r, mid + 1, R, v);
}
lnt query(int n, int l, int r, int p) {
	lnt ret = tag[n];
	do {
		int mid = (l + r) >> 1;
		if (p <= mid) {
			r = mid;
			n = n << 1;
		} else {
			l = mid + 1;
			n = n << 1 | 1;
		}
		ret = std::min(ret, tag[n]);
	} while (l < r);
	return ret;
}
int main() {
	memset(head, -1, sizeof(head));
	int m = (getInt(), getInt());
	for (int i = 1; i <= m; i++) {
		int u = getInt(), v = getInt(), w = getInt();
		$(u, v, w);
	}
	int s = getInt(), t = getInt(), q = getInt();
	{
		static std::priority_queue<std::pair<lnt, int>> Q;
		memset(ds, 0x3F, sizeof(ds));
		Q.emplace(ds[s] = 0, s);
		while (Q.size()) {
			auto x = Q.top();
			Q.pop();
			if (-x.first != ds[x.second]) continue;
			for (int i = head[x.second]; ~i; i = next[i]) {
				if (ds[to[i]] > val[i] - x.first) {
					Q.emplace(-(ds[to[i]] = val[i] - x.first), to[i]);
				}
			}
		}
		if (ds[t] == INF) {
			while (q--) puts("infinity");
			return 0;
		}
		memset(dt, 0x3F, sizeof(dt));
		Q.emplace(dt[t] = 0, t);
		while (Q.size()) {
			auto x = Q.top();
			Q.pop();
			if (-x.first != dt[x.second]) continue;
			for (int i = head[x.second]; ~i; i = next[i]) {
				if (dt[to[i]] > val[i] - x.first) {
					fa[to[i]] = x.second;
					Q.emplace(-(dt[to[i]] = val[i] - x.first), to[i]);
				}
			}
		}
	}
	for (int x = s; x; x = fa[x]) id[x] = ++cnt;
	{
		static std::queue<int> Q;
		memset(pre, 0x3F, sizeof(pre));
		Q.push(s);
		while (Q.size()) {
			int x = Q.front();
			Q.pop();
			if (id[x]) pre[x] = id[x];
			for (int i = head[x]; ~i; i = next[i]) {
				if (ds[to[i]] == ds[x] + val[i]) {
					if (pre[to[i]] == 0x3F3F3F3F) Q.push(to[i]);
					pre[to[i]] = std::min(pre[to[i]], pre[x]);
				}
			}
		}
		Q.push(t);
		while (Q.size()) {
			int x = Q.front();
			Q.pop();
			if (id[x]) nxt[x] = id[x];
			for (int i = head[x]; ~i; i = next[i]) {
				if (dt[to[i]] == dt[x] + val[i]) {
					if (nxt[to[i]] == 0) Q.push(to[i]);
					nxt[to[i]] = std::max(nxt[to[i]], pre[x]);
				}
			}
		}
	}
	memset(tag, 0x3F, sizeof(tag));
	for (int i = 0; i < tot; i += 2) {
		int u = to[i], v = to[i ^ 1];
		if (id[u] > id[v]) std::swap(u, v);
		if (id[u] && id[v] && id[u] + 1 == id[v]) continue;
		if (pre[u] >= nxt[v]) continue;
		modify(1, 1, cnt - 1, pre[u], nxt[v] - 1, ds[u] + dt[v] + val[i]);
		// fprintf(stderr, "Update %d - %d to %lld\n", pre[u], nxt[v] - 1, ds[u] + dt[v] + val[i]);
	}
	for (int u, v; q; q--) {
		u = getInt(), v = getInt();
		if (id[u] > id[v]) std::swap(u, v);
		if (id[u] && id[v] && id[u] + 1 == id[v]) {
			lnt ans = query(1, 1, cnt - 1, id[u]);
			if (ans == INF) {
				puts("Infinity");
			} else {
				printf("%lld\n", ans);
			}
		} else {
			printf("%lld\n", ds[t]);
		}
	}
	return 0;
}
