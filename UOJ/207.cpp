#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
struct splay_t {
	int s[2], f, rev, sum, tmp, val;
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
	node[x].sum = node[node[x].s[0]].sum ^ node[x].val ^ node[node[x].s[1]].sum;
}
inline void rotate(int x) {
	int f = node[x].f, p = node[f].f, v = node[f].s[0] == x;
	node[node[f].s[v ^ 1] = node[x].s[v]].f = f;
	p && (node[p].s[node[p].s[1] == f] = x);
	node[x].f = p, node[f].f = x, node[x].s[v] = f;
	pushUp(f), pushUp(x);
}
int stack[MAXN];
inline void splay(int x) {
	int top = 0;
	for (stack[++top] = x; !isRoot(stack[top]); top++) stack[top + 1] = node[stack[top]].f;
	for (int i = top; i >= 1; i--) pushDown(stack[i]);
	while (!isRoot(x)) {
		int y = node[x].f;
		if (isRoot(y)) {
			rotate(x);
		} else {
			int z = node[y].f;
			if ((node[z].s[1] == y) ^ (node[y].s[1] == x)) {
				rotate(y), rotate(x);
			} else {
				rotate(x), rotate(x);
			}
		}
	}
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
inline void setRoot(int x, int y) {
	access(x);
	splay(x);
	node[x].rev ^= 1;
}
inline void link(int x, int y) {
	setRoot(x);
    setRoot(y);
	node[x].f = y;
    node[y].tmp ^= node[x].tmp;
}
inline void cut(int x, int y) {
	setRoot(x);
	access(y);
	splay(y);
	node[y].l = node[x].f = 0;
}
int main() {
	//
	return 0;
}