#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int sg[MAXN];
void dp(int x, int fa) {
	sg[x] = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		dp(to[i], x);
		sg[x] ^= sg[to[i]] + 1;
	}
}
int main() {
	scanf("%d", &n);
	memset(head, -1, sizeof(head));
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
	dp(1, 0);
	puts(sg[1] ? "Alice" : "Bob");
	return 0;
}