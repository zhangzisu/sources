#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
const int INF = 0x3F3F3F3F;
int n, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int d[MAXN], c[MAXN], b[MAXN];
void pre(int x, int fa) {
	b[x] = c[x];
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa) continue;
		pre(to[i], x);
		if (!b[to[i]]) d[x]++, d[to[i]]++;
		b[x] &= b[to[i]];
	}
}
int f[MAXN][2], all, max, root;
void dp(int x, int fa) {
	int g = ((d[x] + c[x]) & 1) ? 0 : 2;
	all += d[x] + (g >> 1);
	int now0 = 0, now1 = 0, flag = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa || b[to[i]]) continue;
		flag = 1;
		dp(to[i], x);
		max = std::max(max, f[to[i]][0] + now1 + g);
		max = std::max(max, f[to[i]][1] + now0 + g);
		now0 = std::max(now0, f[to[i]][0]);
		now1 = std::max(now1, f[to[i]][1]);
	}
	f[x][0] = now0 + g;
	if (flag) f[x][1] = now1 + g;
}
char buf[MAXN];
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
	for (int i = (scanf("%s", buf + 1), 1); i <= n; i++)
		if (!(c[i] = (buf[i] == 'B'))) root = i;
	if (!root) return puts("0"), 0;
	memset(f, 0x80, sizeof(f));
	pre(root, 0);
	dp(root, 0);
	printf("%d\n", all - max);
	return 0;
}