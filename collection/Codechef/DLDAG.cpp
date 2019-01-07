#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <queue>
#include <string>
#include <vector>
#define MAXN 1000010
const int INF = 0x3F3F3F3F;
int head[MAXN], to[MAXN], next[MAXN], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
int n, m, in[MAXN], out[MAXN], Q[MAXN], H, T;
inline void remove(int x) {
	for (int i = head[x]; ~i; i = next[i]) {
		if (!--in[to[i]]) {
			Q[++T] = to[i];
		}
	}
}
std::vector<std::pair<int, int>> ans;
int tmp[MAXN], id[MAXN];
double score[MAXN];
inline void rebuild() {
	// fprintf(stderr, "rebuild\n");
	int m = 0;
	for (int i = H; i <= T; i++) tmp[++m] = Q[i];
	// fprintf(stderr, "total: %d\n", m);
	for (int x = 1; x <= m; x++) {
		score[x] = 0;
		id[x] = x;
		for (int i = head[tmp[x]]; ~i; i = next[i]) {
			score[x] += 1. / in[to[i]] / in[to[i]];
		}
	}
	std::sort(id + 1, id + m + 1, [](int a, int b) { return score[a] > score[b]; });
	for (int i = 1; i <= m; i++) Q[H + i - 1] = tmp[id[i]];
}
int main() {
	srand(time(NULL));
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		$(v, u), in[u]++, out[v]++;
	}
	H = 1;
	T = 0;
	for (int i = 1; i <= n; i++) {
		if (!in[i]) Q[++T] = i;
	}
	int clk = 0, last = -INF;
	while (H <= T) {
		++clk;
		if (clk - last > 2000) {
			rebuild();
			last = clk;
		}
		if (H < T) {
			ans.emplace_back(Q[H], Q[H + 1]);
			remove(Q[H++]);
			remove(Q[H++]);
		} else {
			ans.emplace_back(Q[H], 0);
			remove(Q[H++]);
		}
	}
	printf("%llu\n", ans.size());
	for (auto s : ans) {
		if (s.second) {
			printf("2 %d %d\n", s.first, s.second);
		} else {
			printf("1 %d\n", s.first);
		}
	}
	return 0;
}