#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 30010
#define MBIT 7
int n, v[MAXN];
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int main() {
	scanf("%d%*d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &v[i]);
	memset(head, -1, sizeof(head));
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
	//
	return 0;
}