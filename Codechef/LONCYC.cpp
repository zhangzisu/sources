#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
#define MAXM 5000010
int head[MAXN], to[MAXM << 1], next[MAXM << 1], tot;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
inline void init() {
	memset(head, -1, sizeof(head));
	tot = 0;
}
int t, n, m;
int main() {
	for (scanf("%d", &t); t; t--) {
        init();
		scanf("%d%d", &n, &m);
		//
	}
	return 0;
}