#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 5000010
#define MAXM 5000010
int n, m, p, all = 0, head[MAXN], to[MAXM], val[MAXM], next[MAXM], tot = 0;
inline void $(int u, int v, int w) {
	next[tot] = head[u], val[tot] = w, to[tot] = v, head[u] = tot++;
}
int point[MAXN][2];
void build(int n, int l, int r) {
	point[n][0] = ++all;
	point[n][1] = ++all;
	if (l == r) return $(point[n][0], point[n][1], 0);
	int mid = (l + r) >> 1;
	build(n << 1, l, mid);
	build(n << 1 | 1, mid + 1, r);
	$(point[n << 1][0], point[n][0], 0);
	$(point[n][1], point[n << 1 | 1][1], 0);
}
int points[MAXN][2], count[2];
void query(int n, int l, int r, int L, int R, int v) {
	if (l == L && r == R) return void(points[++count[v]][v] = point[n][v]);
	int mid = (l + r) >> 1;
	if (R <= mid) return query(n << 1, l, mid, L, R, v);
	if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R, v);
	query(n << 1, l, mid, L, mid, v);
	query(n << 1 | 1, mid + 1, r, mid + 1, R, v);
}
int dis[MAXN];
std::priority_queue<std::pair<int, int>> Q;
inline void bfs() {
	//
}
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d%d%d", &n, &m, &p);
	//
	return 0;
}