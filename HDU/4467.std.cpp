#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;
const int maxn = 100050;

struct Edge {
	int u, v;
	LL w;
	Edge(int u = 0, int v = 0, LL w = 0) : u(u), v(v), w(w) {}
	bool operator<(const Edge& rhs) const {
		if (u == rhs.u) return v < rhs.v;
		return u < rhs.u;
	}
} e[maxn];

int du[maxn];
bool sp[maxn], type[maxn];
LL ans[3];

int head[maxn][2], v[maxn << 2], nxt[maxn << 2], tot;
LL w[maxn << 2];

void initGraph() {
	memset(head, 0, sizeof head);
	tot = 0;
}

inline void add(int t, int _u, int _v, LL _w) {
	v[++tot] = _v;
	w[tot] = _w;
	nxt[tot] = head[_u][t];
	head[_u][t] = tot;
}

LL sum[maxn][2];

int main() {
	//    freopen("data.in","r", stdin) ;
	int cas = 1, n, m;
	while (scanf("%d%d", &n, &m) == 2) {
		for (int i = 1, x; i <= n; i++) {
			scanf("%d", &x);
			type[i] = x;
		}

		for (int i = 0; i < m; i++) {
			scanf("%d%d%I64d", &e[i].u, &e[i].v, &e[i].w);
			if (e[i].u > e[i].v) swap(e[i].u, e[i].v);
		}
		sort(e, e + m);  //unique
		int cnt = 0;
		for (int i = 0, j; i < m; i = j) {
			for (j = i + 1; j < m && e[i].u == e[j].u && e[i].v == e[j].v; j++) {
				e[i].w += e[j].w;
			}
			e[cnt++] = e[i];
		}

		//build graph
		memset(du, 0, sizeof du);
		for (int i = 0; i < cnt; i++) {
			du[e[i].u]++;
			du[e[i].v]++;
		}
		int lim = sqrt(cnt << 1);
		for (int i = 1; i <= n; i++) {
			sp[i] = (du[i] >= lim);
		}
		initGraph();
		for (int i = 0; i < cnt; i++) {
			int x = e[i].u, y = e[i].v;
			LL w = e[i].w;
			// 用add1 来访问重点
			// 用add0 来访问所有点
			if (sp[y]) {  //重点需要被访问
				add(1, x, y, w);
			} else {  //轻点需要访问所有点
				add(0, y, x, w);
			}
			if (sp[x]) {  //重点需要被访问
				add(1, y, x, w);
			} else {  //轻点需要访问所有点
				add(0, x, y, w);
			}
		}

		ans[0] = ans[1] = ans[2] = 0;
		memset(sum, 0, sizeof sum);
		for (int i = 0; i < cnt; i++) {
			int x = e[i].u, y = e[i].v;
			LL w = e[i].w;
			if (sp[x]) {
				sum[x][type[y]] += w;
			}
			if (sp[y]) {
				sum[y][type[x]] += w;
			}
			ans[type[x] + type[y]] += w;
		}

		printf("Case %d:\n", cas++);
		int Q, a, b, x;
		scanf("%d", &Q);
		char s[12];
		while (Q--) {
			scanf("%s", s);
			if (s[0] == 'A') {
				scanf("%d%d", &a, &b);
				printf("%I64d\n", ans[a + b]);
			} else {
				scanf("%d", &x);
				type[x] ^= 1;
				if (sp[x]) {
					for (int i = 0; i < 2; i++) {
						ans[(type[x] ^ 1) + i] -= sum[x][i];
						ans[type[x] + i] += sum[x][i];
					}
				} else {
					for (int i = head[x][0]; i; i = nxt[i]) {
						ans[(type[x] ^ 1) + type[v[i]]] -= w[i];
						ans[type[x] + type[v[i]]] += w[i];
					}
				}

				for (int i = head[x][1]; i; i = nxt[i]) {
					sum[v[i]][type[x] ^ 1] -= w[i];
					sum[v[i]][type[x]] += w[i];
				}
			}
		}
	}
	return 0;
}