#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
inline int $() {
	register int x = 0;
	register char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 400010
struct splay_t {
	int s[2], f, rev, sum, tmp;
} node[MAXN];
inline bool isRoot(int x) {
	return node[node[x].f].s[0] != x && node[node[x].f].s[1] != x;
}
inline void pushDown(int x) {
	if (node[x].rev) {
		std::swap(node[x].s[0], node[x].s[1]);
		node[node[x].s[0]].rev ^= 1;
		node[node[x].s[1]].rev ^= 1;
		node[x].rev = 0;
	}
}
inline void pushUp(int x) {
	node[x].sum = node[node[x].s[0]].sum ^ node[x].tmp ^ node[node[x].s[1]].sum;
}
inline int ch(int x) {
	return node[node[x].f].s[1] == x;
}
inline void rotate(int x) {
	int f = node[x].f, p = node[f].f, v = ch(x);
	isRoot(f) || (node[p].s[ch(f)] = x);
	node[node[f].s[v] = node[x].s[v ^ 1]].f = f;
	node[x].f = p, node[node[x].s[v ^ 1] = f].f = x;
	pushUp(f), pushUp(x);
}
inline void dd(int x) {
	if (!isRoot(x)) dd(node[x].f);
	pushDown(x);
}
inline void splay(int x) {
	dd(x);
	for (; !isRoot(x); rotate(x))
		if (!isRoot(node[x].f)) rotate(ch(node[x].f) == ch(x) ? node[x].f : x);
}
inline void access(int x) {
	for (int y = 0; x; y = x, x = node[x].f) {
		splay(x);
		node[x].tmp ^= node[node[x].s[1]].sum ^ node[y].sum;
		node[x].s[1] = y;
		node[y].f = x;
		pushUp(x);
	}
}
inline void setRoot(int x) {
	access(x);
	splay(x);
	node[x].rev ^= 1;
}
inline void link(int x, int y) {
	setRoot(x);
	setRoot(y);
	node[x].f = y;
	node[y].tmp ^= node[x].sum;
	pushUp(y);
}
inline void cut(int x, int y) {
	setRoot(x);
	access(y);
	splay(y);
	node[y].s[0] = node[x].f = 0;
	pushUp(y);
}
inline void update(int x, int v) {
	access(x);
	splay(x);
	node[x].sum ^= v, node[x].tmp ^= v;
}
inline int query(int x, int y) {
	setRoot(x);
	access(y);
	return node[y].tmp;
}
int n, m, t, u[MAXN], v[MAXN], w[MAXN], all;
constexpr int mask = (1 << 15) - 1;
inline int randint() {
	return (rand() << 15) | (rand() & mask);
}
int main() {
	srand(time(NULL));
	$(), n = $(), m = $();
	for (int i = 1; i < n; i++) link($(), $());
	for (int op, x, y; m; m--) {
		op = $();
		if (op == 1) {
			cut($(), $());
			link($(), $());
		} else if (op == 2) {
			x = $(), y = $();
			all ^= (w[++t] = randint());
			update(u[t] = x, w[t]);
			update(v[t] = y, w[t]);
		} else if (op == 3) {
			x = $();
			all ^= w[x];
			update(u[x], w[x]);
			update(v[x], w[x]);
		} else if (op == 4) {
			puts(query($(), $()) == all ? "YES" : "NO");
		}
	}
	return 0;
}