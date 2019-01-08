#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <vector>
#define MAXN 100010

struct trie {
	std::map<int, int> son;
	int fail, sum, vis;
} acm[MAXN];
int root = 1, cnt = 1, n, m, pos[MAXN], ans[MAXN], res[MAXN];

inline void insert(int id) {
	int p = root, l, x;
	for (scanf("%d", &l); l; l--) {
		scanf("%d", &x);
		if (!acm[p].son.count(x))
			acm[p].son[x] = ++cnt;
		p = acm[p].son[x];
	}
	acm[p].sum++;
	pos[id] = p;
}

std::queue<int> Q;
inline void build() {
	Q.push(root);
	while (Q.size()) {
		int p = Q.front();
		Q.pop();
		for (std::map<int, int>::iterator it = acm[p].son.begin(); it != acm[p].son.end(); it++) {
			if (p == root) {
				acm[it->second].fail = root;
			} else {
				int q = acm[p].fail;
				while (q && !acm[q].son.count(it->first)) q = acm[q].fail;
				if (q) {
					acm[it->second].fail = acm[q].son[it->first];
				} else {
					acm[it->second].fail = root;
				}
			}
			Q.push(it->second);
		}
	}
}

int vis[MAXN];
std::vector<int> val[MAXN][2];
inline int query(std::vector<int> &v) {
	int p = root, ret = 0;
	for (int _x = 0, x; _x < (int)v.size(); _x++) {
		x = v[_x];
		while (p != root && !acm[p].son.count(x)) p = acm[p].fail;
		p = acm[p].son[x];
		if (!p) p = root;
		for (int q = p; q != root; q = acm[q].fail) {
			if (!vis[q]) {
				vis[q] = 1;
				acm[q].vis++;
				ret += acm[q].sum;
			}
		}
	}
	return ret;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 0, k; j <= 1; j++) {
			scanf("%d", &k);
			for (int l = 1, x; l <= k; l++)
				scanf("%d", &x), val[i][j].push_back(x);
		}
	}
	for (int i = 1; i <= m; i++) insert(i);
	build();
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		ans[i] += query(val[i][0]);
		ans[i] += query(val[i][1]);
	}
	for (int i = 1; i <= m; i++) printf("%d\n", acm[pos[i]].vis);
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
	puts("");
	return 0;
}