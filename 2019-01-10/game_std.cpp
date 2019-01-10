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
	inline state(int len = 0) : len(len) { memset(son, 0, sizeof(son)), link = 0; }
	inline state(state &x, int len) : len(len) { memcpy(son, x.son, sizeof(son)), link = x.link; }
	inline int &operator[](int index) { return son[index]; }
} sam[MAXN];
int root, pre, cnt;
inline int extend(int x) {
	int p, q, s, c;
	sam[p = ++cnt] = state(sam[q = pre].len + 1);
	pre = p;
	for (; q && !sam[q][x]; q = sam[q].link) sam[q][x] = p;
	if (!q) return sam[p].link = root, p;
	s = sam[q][x];
	if (sam[q].len + 1 == sam[s].len) return sam[p].link = s, p;
	sam[c = ++cnt] = state(sam[s], sam[q].len + 1);
	for (; q && sam[q][x] == s; q = sam[q].link) sam[q][x] = c;
	return sam[s].link = sam[p].link = c, p;
}
int T, n, m, id[MAXN], sum[MAXN], sg[MAXN], pos[MAXN], fa[MAXN][18], tmp[27], sgclk;
char buf[MAXN];
int main() {
	for (scanf("%d", &T); T; T--) {
		memset(sum, 0, sizeof(int) * (n + 1));
		memset(sg, 0, sizeof(int) * (cnt + 1));
		sam[root = pre = cnt = 1] = state();

		scanf("%s%d", buf + 1, &m);
		n = strlen(buf + 1);
		for (int i = 1; i <= n; i++) pos[i] = extend(buf[i] - 'a');
		for (int i = 1; i <= cnt; i++) sum[sam[i].len]++;
		for (int i = 1; i <= n; i++) sum[i] += sum[i - 1];
		for (int i = 1; i <= cnt; i++) id[sum[sam[i].len]--] = i;
		for (int _ = cnt; _; _--) {
			int x = id[_];
			++sgclk;
			for (int i = 0; i < 26; i++) {
				if (!sam[x][i]) continue;
				tmp[sg[sam[x][i]]] = sgclk;
			}
			for (int i = 0; i <= 26; i++) {
				if (tmp[i] != sgclk) {
					sg[x] = i;
					break;
				}
			}
		}
		for (int _ = 1; _ <= cnt; _++) {
			int x = id[_];
			fa[x][0] = sam[x].link;
			for (int j = 1; j < 18; j++) fa[x][j] = fa[fa[x][j - 1]][j - 1];
		}
		int ans = 0;
		for (int i = 1, l, r; i <= m; i++) {
			scanf("%d%d", &l, &r);
			// int p = 1;
			// for (int j = l; j <= r; j++) p = sam[p][buf[j] - 'a'];
			// ans ^= sg[p];
			// continue;
			int p = pos[r];
			for (int j = 17; ~j; j--) {
				if (!fa[p][j]) continue;
				if (sam[fa[p][j]].len < r - l + 1) continue;
				p = fa[p][j];
			}
			ans ^= sg[p];
			// fprintf(stderr, "-> %d\n", p);
		}
		puts(ans ? "Alice" : "Bob");
	}
	return 0;
}