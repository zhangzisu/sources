#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#define MAXN 1000010
std::deque<int> Q;
int n, k, d[MAXN], level[MAXN], ans;
int head[MAXN], next[MAXN << 1], to[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int main() {
	scanf("%d%d", &n, &k);
	if (!k) return puts("0"), 0;
	if (n == 1 || k == 1) return puts("1"), 0;
	memset(head, -1, sizeof(head));
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v), d[u]++, d[v]++;
	for (int i = 1; i <= n; i++) {
		if (d[i] == 1) {
			level[i] = 1;
			Q.push_back(i);
		}
	}
	while (Q.size()) {
		int x = Q.front();
		Q.pop_front();
		ans++;
		if (level[x] >= (k >> 1)) continue;
		for (int i = head[x]; ~i; i = next[i]) {
			if (!level[to[i]] && --d[to[i]] == 1) {
				level[to[i]] = level[x] + 1;
				Q.push_back(to[i]);
			}
		}
	}
	if (k & 1) {
		for (int i = 1; i <= n; i++) {
			if (!level[i]) {
				ans++;
				break;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}