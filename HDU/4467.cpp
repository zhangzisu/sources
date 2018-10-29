#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 100010
typedef long long lnt;
int _, n, m, p, q, SQRT, c[MAXN], d[MAXN], id[MAXN];
int head[MAXN], to[MAXN << 1], next[MAXN << 1], val[MAXN << 1], tot;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int HEAD[MAXN], TO[MAXN << 1], NEXT[MAXN << 1], VAL[MAXN << 1], TOT;
inline void $(int u, int v, int w) {
	NEXT[TOT] = HEAD[u], TO[TOT] = v, VAL[TOT] = w, HEAD[u] = TOT++;
	NEXT[TOT] = HEAD[v], TO[TOT] = u, VAL[TOT] = w, HEAD[v] = TOT++;
}
lnt sum1[MAXN][2], sum2[MAXN][2], ans[3];
std::vector<int> by[MAXN];
char buf[20];
int main() {
	while (scanf("%d%d", &n, &m) == 2) {
		printf("Case %d:\n", ++_);
		for (int i = 1; i <= n; i++) scanf("%d", c + i);
		memset(head + 1, -1, sizeof(int) * n);
		memset(d + 1, 0, sizeof(int) * n);
		tot = p = 0;
		SQRT = sqrt(m >> 1);
		for (int i = 1, u, v, w; i <= m; i++) {
			scanf("%d%d%d", &u, &v, &w);
			$(u, v, w);
			d[u]++, d[v]++;
		}
		for (int i = 1; i <= n; i++) by[i].clear();
		memset(ans, 0, sizeof(ans));
		for (int x = 1; x <= n; x++) {
			if (d[x] >= SQRT) {
				id[x] = ++p;
				sum1[p][0] = sum1[p][1] = sum2[p][0] = sum2[p][1] = 0;
				for (int i = head[x]; ~i; i = next[i]) {
					if (d[to[i]] >= SQRT) {
						by[x].push_back(i);
					}
				}
			} else {
				id[x] = 0;
			}
		}
		for (int x = 1; x <= n; x++) {
			if (id[x]) {
				for (auto i : by[x]) {
					sum2[id[to[i]]][c[x]] += val[i];
				}
			} else {
				for (int i = head[x]; ~i; i = next[i]) {
					if (id[to[i]]) {
						sum1[id[to[i]]][c[x]] += val[i];
					} else {
						ans[c[x] + c[to[i]]] += val[i];
					}
				}
			}
		}
		scanf("%d", &q);
		for (int x, y; q; q--) {
			scanf("%s", buf);
			if (buf[0] == 'A') {
				scanf("%d%d", &x, &y);
				lnt tmp = ans[x + y];
				for (int i = 1; i <= p; i++) {
					if ((x && y && !c[i]) || (!x && !y && c[i])) continue;
					tmp += sum1[i][x + y - c[i]] * 2;
					tmp += sum2[i][x + y - c[i]];
				}
				printf("%lld\n", tmp / 2);
			} else if (buf[0] == 'C') {
				scanf("%d", &x);
				if (id[x]) {
					for (auto i : by[x]) {
						sum2[id[to[i]]][c[x]] -= val[i];
					}
					c[x] ^= 1;
					for (auto i : by[x]) {
						sum2[id[to[i]]][c[x]] += val[i];
					}
				} else {
					for (int i = head[x]; ~i; i = next[i]) {
						if (id[to[i]]) {
							sum1[id[to[i]]][c[x]] -= val[i];
						} else {
							ans[c[x] + c[to[i]]] -= val[i] * 2LL;
						}
					}
					c[x] ^= 1;
					for (int i = head[x]; ~i; i = next[i]) {
						if (id[to[i]]) {
							sum1[id[to[i]]][c[x]] += val[i];
						} else {
							ans[c[x] + c[to[i]]] += val[i] * 2LL;
						}
					}
				}
			}
		}
	}
	return 0;
}