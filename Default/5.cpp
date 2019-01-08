#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MAXV 30010
#define SQRT 320
typedef unsigned long long ulnt;
const int mask = (1 << 16) - 1;
int b_pre[1 << 16], b_nxt[1 << 16];
unsigned b_val[1 << 16][31], b_pow[MAXV][31];
inline void init() {
	for (int i = 1; i < MAXV; i++) {
		b_pow[i][0] = 1;
		for (int j = 1; j < 31; j++) {
			b_pow[i][j] = b_pow[i][j - 1] * (unsigned)i;
		}
	}
	for (int i = 0; i < (1 << 16); i++) {
		b_pre[i] = b_nxt[i] = 16;
		for (int j = 0; j < 16; j++) {
			if ((~i >> j) & 1) {
				b_pre[i] = j;
				break;
			}
		}
		for (int j = 0; j < 16; j++) {
			if ((~i >> (15 - j)) & 1) {
				b_nxt[i] = j;
				break;
			}
		}
		int p = 0;
		for (int j = b_pre[i]; j < 16 - b_nxt[i]; j++) {
			if ((i >> j) & 1) {
				p++;
			} else {
				for (int k = 0; k < 31; k++) {
					b_val[i][k] += b_pow[p][k];
				}
				p = 0;
			}
		}
		for (int k = 0; k < 31; k++) {
			b_val[i][k] += b_pow[p][k];
		}
	}
}
struct bitset {
	ulnt val[470];
	inline void clear() {
		memset(val, 0, sizeof(val));
	}
	inline void set(int x) {
		val[x >> 6] |= 1ULL << (x & 63);
	}
	inline void Or(const bitset &y) {
		for (int i = 0; i < 470; i++) {
			val[i] |= y.val[i];
		}
	}
	inline unsigned calc(int k) {
		unsigned ret = 0;
		int last = 0;
		for (int i = 0, chunk; i < 470; i++) {
			chunk = val[i] & mask;
			if (chunk == mask) {
				last += 16;
			} else {
				last += b_pre[chunk];
				ret += b_pow[last][k];
				ret += b_val[chunk][k];
				last = b_nxt[chunk];
			}
			chunk = (val[i] >> 16) & mask;
			if (chunk == mask) {
				last += 16;
			} else {
				last += b_pre[chunk];
				ret += b_pow[last][k];
				ret += b_val[chunk][k];
				last = b_nxt[chunk];
			}
			chunk = (val[i] >> 32) & mask;
			if (chunk == mask) {
				last += 16;
			} else {
				last += b_pre[chunk];
				ret += b_pow[last][k];
				ret += b_val[chunk][k];
				last = b_nxt[chunk];
			}
			chunk = (val[i] >> 48) & mask;
			if (chunk == mask) {
				last += 16;
			} else {
				last += b_pre[chunk];
				ret += b_pow[last][k];
				ret += b_val[chunk][k];
				last = b_nxt[chunk];
			}
		}
		return ret;
	}
	inline bitset() {
		clear();
	}
} data[SQRT][SQRT], tmp;
int n, m, a[MAXN], fa[MAXN][18], deep[MAXN];
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int bp[MAXN], pa[MAXN], pnt = 0;
int pre(int x) {
	for (int i = 1; i < 18; i++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
	int max = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x][0]) continue;
		fa[to[i]][0] = x;
		deep[to[i]] = deep[x] + 1;
		max = std::max(max, pre(to[i]) + 1);
	}
	if (max >= SQRT) bp[x] = ++pnt, max = 0;
	return max;
}
void build(int x, int last) {
	if (bp[x]) {
		pa[x] = last;
		last = x;
		for (int y = x; y != pa[x]; y = fa[y][0]) {
			data[bp[x]][bp[x]].set(a[y]);
		}
		for (int y = pa[x]; y; y = pa[y]) {
			data[bp[x]][bp[y]].Or(data[bp[x]][bp[x]]);
			data[bp[x]][bp[y]].Or(data[bp[pa[x]]][bp[y]]);
		}
	}
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x][0]) continue;
		build(to[i], last);
	}
}
inline int lca(int u, int v) {
	if (deep[u] < deep[v]) std::swap(u, v);
	for (int i = 17; ~i; i--)
		if (deep[fa[u][i]] >= deep[v]) u = fa[u][i];
	for (int i = 17; ~i; i--)
		if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return u == v ? u : fa[u][0];
}
unsigned lans = 0;
int main() {
	init();
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
	deep[1] = 1, pre(1), build(1, 0);
	for (int x, k; m; m--) {
		scanf("%d", &x);
		tmp.clear();
		for (int u, v; x; x--) {
			unsigned U, V;
			scanf("%u%u", &U, &V);
			u = U ^ lans;
			v = V ^ lans;
			int l = lca(u, v);
			for (; !bp[u] && u != l; u = fa[u][0]) tmp.set(a[u]);
			for (; !bp[v] && v != l; v = fa[v][0]) tmp.set(a[v]);
			if (bp[u] && deep[pa[u]] >= deep[l]) {
				int d = u;
				while (pa[u] && deep[pa[pa[u]]] >= deep[l]) u = pa[u];
				tmp.Or(data[bp[d]][bp[u]]);
				u = pa[u];
			}
			if (bp[v] && deep[pa[v]] >= deep[l]) {
				int d = v;
				while (pa[v] && deep[pa[pa[v]]] >= deep[l]) v = pa[v];
				tmp.Or(data[bp[d]][bp[v]]);
				v = pa[v];
			}
			for (; u != l; u = fa[u][0]) tmp.set(a[u]);
			for (; v != l; v = fa[v][0]) tmp.set(a[v]);
			tmp.set(a[l]);
		}
		scanf("%d", &k);
		printf("%u\n", lans = tmp.calc(k));
	}
	return 0;
}