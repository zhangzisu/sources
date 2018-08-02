#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
struct state {
	int son[26], link, len, size;
	inline int& operator[](int index) {
		return son[index];
	}
} sam[MAXN];
int all = 1, last = 1, n;
int head[MAXN], to[MAXN], next[MAXN], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
inline void insert(char c) {
	int p, q;
	sam[q = ++all].len = sam[p = last].len + 1;
	sam[last = q].size = 1;
	for (; p && !sam[p][c - 'a']; p = sam[p].link) sam[p][c - 'a'] = q;
	if (!p) return sam[q].link = 1, void();
	int np = sam[p][c - 'a'];
	if (sam[np].len == sam[p].len + 1) return sam[q].link = np, void();
	int nq = ++all;
	memcpy(sam[nq].son, sam[np].son, sizeof(int) * 26);
	sam[nq].len = sam[p].len + 1;
	sam[nq].link = sam[np].link;
	sam[np].link = sam[q].link = nq;
	for (; p && sam[p][c - 'a'] == np; p = sam[p].link) sam[p][c - 'a'] = nq;
}
int size[MAXN];
long long ans;
void dfs(int x) {
	size[x] = sam[x].size;
	for (int i = head[x]; ~i; i = next[i]) {
		dfs(to[i]);
		ans += 1LL * size[x] * size[to[i]] * sam[x].len;
		size[x] += size[to[i]];
	}
}
char buf[MAXN];
int main() {
	memset(head, -1, sizeof(head));
	scanf("%s", buf + 1);
	n = strlen(buf + 1);
	std::reverse(buf + 1, buf + n + 1);
	for (int i = 1; i <= n; i++) insert(buf[i]);
	for (int i = 2; i <= all; i++) $(sam[i].link, i);
	dfs(1);
	printf("%lld\n", 1LL * (n - 1) * (1 + n) * n / 2 - ans * 2);
	return 0;
}