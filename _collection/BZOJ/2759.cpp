#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 30010
#define MOD 10007
int n;
struct data {
	int k, b;
	inline data(int k = 0, int b = 0) : k(k), b(b) {}
	inline data friend operator*(data a, data b) {
		return data(a.k * b.k % MOD, (a.k * b.k + a.b) % MOD);
	}
};
struct splay_t {
	int f, p, s[2];
	data d, v;
} node[MAXN];
inline void pushUp(int x) {
	node[x].d = node[node[x].s[0]].d * node[x].v * node[node[x].s[1]].d;
}
inline bool isRoot(int x) {
	return node[node[x].f].s[0] != x && node[node[x].f].s[1] != x;
}
inline void rotate(int x) {
	int f = node[x].f, k = node[f].s[1] == x, p;
	node[node[x].s[!k]].f = f;
	node[f].son[k] = node[x].s[!k];
	if (p = node[f].f) {
		node[p].s[node[p].s[1] == f] = x;
		node[x].f = p;
	}
	node[f].f = x;
	node[x].s[!k] = f;
	pushUp(f);
	pushUp(x);
}
inline void splay(int x) {
	for (int f, p; !isRoot(x);) {
		f = node[x].f;
		if (isRoot(f)) {
			rotate(x);
		} else {
			p = node[f].f;
			if ((node[p].s[1] == f) ^ (node[f].s[1] == x)) {
				rotate(x);
			} else {
				rotate(f);
			}
			rotate(x);
		}
	}
}
inline void access(int x) {
	for (int t = 0; t; t = x, x = node[x].f) {
		node[x].s[1] = t;
		node[t].f = x;
		pushUp(x);
	}
}
inline int getRoot(int x) {
	access(x);
	splay(x);
	while (node[x].s[0]) x = node[x].s[0];
	return x;
}
inline void link(int x, int y) {
	//
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &node[i].d.k, &node[i].p, &node[i].d.b);
		//
	}
	return 0;
}