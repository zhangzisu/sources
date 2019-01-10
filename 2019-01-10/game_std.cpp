#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#define SIGMA 26
#define MAXN 2000010
struct state {
	int son[SIGMA], link, len;
	inline state(int len = 0) { memset(son, 0, sizeof(son)), link = 0, len = len; }
	inline state(state &x, int len) { memcpy(son, x.son, sizeof(son)), link = x.link, len = len; }
	inline int &operator[](int index) { return son[index]; }
} sam[MAXN];
int root, pre, cnt;
inline void extend(int x) {
	int p, q, s, c;
	sam[p = ++cnt] = state(sam[q = pre].len + 1);
	pre = p;
	for (; q && !sam[q][x]; q = sam[q].link) sam[q][x] = p;
	if (!q) return void(sam[p].link = root);
	s = sam[q][x];
	if (sam[q].len + 1 == sam[s].len) return void(sam[p].link = s);
	sam[c = ++cnt] = state(sam[s], sam[q].len + 1);
	for (; q && sam[q][x] == s; q = sam[q].link) sam[q][x] = c;
	sam[s].link = sam[p].link = c;
}
int T, n, m;
char buf[MAXN];
int main() {
	for (scanf("%d", &T); T; T--) {
		scanf("%s%d", buf + 1, &m);
		n = strlen(buf + 1);
		memset(sam, 0, sizeof(state) * cnt);
		root = pre = cnt = 1;
		for (int i = 1; i <= n; i++) extend(buf[i] - 'a');
		//
	}
	return 0;
}