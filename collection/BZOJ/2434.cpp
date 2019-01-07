#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#define MAXN 500010
int head[MAXN], next[MAXN], to[MAXN], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
std::vector<int> where[MAXN], query[MAXN], id[MAXN];
int pos[MAXN], m, root = 1, cnt = 1;
struct trie_t {
	int son[26], fail, fa, in, out;
	inline trie_t() {
		memset(son, 0, sizeof(son));
		fail = fa = in = out = 0;
	}
	inline int &operator[](int index) {
		return son[index];
	}
} trie[MAXN];
char buf[MAXN];
inline void in() {
	scanf("%s", buf);
	int p = root;
	for (int i = 0, t = 0; buf[i]; i++) {
		if (islower(buf[i])) {
			if (!trie[p][buf[i] - 'a'])
				trie[trie[p][buf[i] - 'a'] = ++cnt].fa = p;
			p = trie[p][buf[i] - 'a'];
		} else {
			if (buf[i] == 'B') {
				p = trie[p].fa;
			} else {
				where[p].push_back(++t);
				pos[t] = p;
			}
		}
	}
}
std::queue<int> Q;
inline void build() {
	Q.push(root);
	while (Q.size()) {
		int x = Q.front();
		Q.pop();
		for (int i = 0; i < 26; i++) {
			int &y = trie[x][i];
			if (y) {
				int p = trie[x].fail;
				while (p && !trie[p][i]) p = trie[p].fail;
				trie[y].fail = p ? trie[p][i] : root;
				Q.push(y);
			}
		}
	}
}
inline int lowbit(int x) { return x & -x; }
int BIT[MAXN];
inline void add(int x, int y) {
	for (; x <= cnt; x += lowbit(x)) BIT[x] += y;
}
inline int qry(int x) {
	register int y;
	for (; x; x -= lowbit(x)) y += BIT[x];
	return y;
}
int dfsclk = 0;
void dfs(int x) {
	trie[x].in = ++dfsclk;
	for (int i = head[x]; ~i; i = next[i]) dfs(to[i]);
	trie[x].out = dfsclk;
}
int ans[MAXN];
void solve(int p) {
	std::vector<int> &where = ::where[p];
	add(trie[p].in, 1);
	for (int i = 0; i < (int)where.size(); i++) {
		std::vector<int> &query = ::query[where[i]];
		std::vector<int> &id = ::id[where[i]];
		for (int j = 0; j < (int)query.size(); j++) {
			ans[id[j]] = qry(trie[pos[query[j]]].out) - qry(trie[pos[query[j]]].in - 1);
		}
	}
	for (int i = 0; i < 26; i++)
		if (trie[p][i]) solve(trie[p][i]);
	add(trie[p].in, -1);
}
int main() {
	memset(head, -1, sizeof(head));
	in();
	build();
	for (int x, y, i = scanf("%d", &m); i <= m; i++) {
		scanf("%d%d", &x, &y);
		std::swap(x, y);
		query[x].push_back(y);
		id[x].push_back(i);
	}
	memset(head, -1, sizeof(head));
	for (int i = 2; i <= cnt; i++) {
		$(trie[i].fail, i);
	}
	dfs(root);
	solve(root);
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
	return 0;
}