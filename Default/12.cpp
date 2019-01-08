#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 100010
#define SQRT 320
#define INF 0x3F3F3F3F
int n, m, q;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
int best[MAXN][SQRT][2], cnt[MAXN], vis[MAXN], clk = 0;
inline void p(int x) {
	static int tmp[SQRT][2];
	auto &now = best[x];
	auto &cnow = cnt[x];
	now[0][0] = x;
	now[0][1] = 0;
	cnow = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		const auto &pre = best[to[i]];
		const auto &cpre = cnt[to[i]];
		int l = 0, r = 0, cur = 0;
		++clk;
		for (; (l < cpre || r < cnow) && cur < SQRT; cur++) {
			while (l < cpre && vis[pre[l][0]] == clk) l++;
			while (r < cnow && vis[now[r][0]] == clk) r++;
			if (l >= cpre && r >= cnow) break;
			if (r >= cnow || (l < cpre && pre[l][1] >= now[r][1])) {
                vis[tmp[cur][0] = pre[l][0]] = clk;
				tmp[cur][1] = pre[l][1] + 1;
				++l;
			} else {
				vis[tmp[cur][0] = now[r][0]] = clk;
				tmp[cur][1] = now[r][1];
				++r;
			}
		}
		memcpy(now, tmp, sizeof(int[2]) * cur);
		cnt[x] = cur;
	}
}
int f[MAXN];
int main(int argc, char const *argv[]) {
	scanf("%d%d%d", &n, &m, &q);
	memset(head, -1, sizeof(head));
	for (int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v);
		$(v, u);
	}
	for (int x = 1; x <= n; x++) p(x);
	for (int t, y; q; q--) {
		scanf("%d%d", &t, &y);
		++clk;
		for (int i = 1, x; i <= y; i++) scanf("%d", &x), vis[x] = clk;
		int ans = -1;
		if (y < SQRT) {
			for (int i = 0; i < cnt[t]; i++) {
				if (vis[best[t][i][0]] != clk) {
					ans = best[t][i][1];
					break;
				}
			}
		} else {
			for (int x = 1; x <= t; x++) {
				f[x] = vis[x] == clk ? -INF : 0;
				for (int i = head[x]; ~i; i = next[i]) {
					f[x] = std::max(f[x], f[to[i]] + 1);
				}
			}
			ans = std::max(ans, f[t]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
