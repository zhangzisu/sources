#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 50010
#define MAXM 100010
const int INF = (~0U) >> 1;
struct edge {
	int u, v, w;
	inline int friend operator<(const edge &a, const edge &b) {
		return a.w < b.w;
	}
} b[MAXM], w[MAXM];
int n, v, vb, vw, k, p[MAXN], ans = INF;
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int main() {
	scanf("%d%d%d", &n, &v, &k);
	for (int i = 1, x; i <= v; i++) {
		edge e;
		scanf("%d%d%d%d", &e.u, &e.v, &e.w, &x);
		(x ? b[++vb] : w[++vw]) = e;
	}
	std::sort(b + 1, b + vb + 1);
	std::sort(w + 1, w + vw + 1);
	b[vb + 1].w = w[vw + 1].w = INF;
	int l = -100, r = 100;
	while (l <= r) {
		int mid = (l + r) / 2, cnt = 0, sum = 0;
		for (int i = 0; i < n; i++) p[i] = i;
		for (int ib = 1, iw = 1; ib <= vb || iw <= vw;) {
			if (w[iw].w + mid <= b[ib].w) {
				int u = find(w[iw].u), v = find(w[iw].v);
				if (u != v) {
					cnt++, sum += w[iw].w;
					p[u] = v;
				}
				iw++;
			} else {
				int u = find(b[ib].u), v = find(b[ib].v);
				if (u != v) {
					sum += b[ib].w;
					p[u] = v;
				}
				ib++;
			}
		}
		if (cnt >= k) {
			ans = std::min(ans, sum);
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}