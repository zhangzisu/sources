#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <vector>
#define MAXN 100010
int left[MAXN], val[2][MAXN], ans[MAXN], n, m, q, t;
std::vector<std::pair<int, int>> d[MAXN];
char buf[MAXN];
std::deque<int> Q;
inline int calc(int l, int d) {
	return !l || !d;
}
int main() {
	for (scanf("%d", &t); t; t--) {
		memset(val, 0, sizeof(val));
		scanf("%s", buf);
		m = strlen(buf);
		for (int i = 1; i <= m; i++) val[0][i] = buf[i - 1] == '1';
		scanf("%s", buf);
		n = strlen(buf);
		for (int i = 1; i <= n; i++) left[i] = buf[i - 1] == '1';
		for (int x, y, i = scanf("%d", &q); i <= q; i++) {
			scanf("%d%d", &x, &y);
			d[x].emplace_back(y, i);
		}
		int flag = 0, fucker = 0;
		for (int i = 1; i <= n; i++) {
			if (!flag) {
				int now = i & 1;
				int pre = now ^ 1;
				val[now][0] = left[i];
				for (int j = 1; j <= m; j++)
					val[now][j] = calc(val[pre][j], val[now][j - 1]);
				for (auto x : d[i]) ans[x.second] = val[now][x.first];
				d[i].clear();
				if (++fucker >= 100) {
					for (int i = 1; i <= m; i++) Q.push_back(val[now][i]);
					flag = 1;
				}
			} else {
				int k1 = calc(left[i], Q[0]);
				int k2 = calc(k1, Q[1]);
				Q.pop_front();
				Q.pop_back();
				Q.push_front(k2);
				Q.push_front(k1);
				for (auto x : d[i]) ans[x.second] = Q[x.first - 1];
				d[i].clear();
			}
		}
		Q.clear();
		for (int i = 1; i <= q; i++) putchar(ans[i] + '0');
		putchar(10);
	}
	return 0;
}