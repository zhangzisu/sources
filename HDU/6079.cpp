#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline int $() {
	register int x = 0;
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 100010
#define SQRT 320
inline int belong(int x) { return (x + SQRT - 1) / SQRT; }
inline int left(int b) { return (b - 1) * SQRT + 1; }
inline int right(int b) { return b * SQRT; }
inline int lowbit(int x) { return x & -x; }
struct BinaryIndexedTree_t {
	int val[SQRT];
	inline void add(int x, int y) {
		for (; x <= SQRT; x += lowbit(x)) val[x] += y;
	}
	inline int get(int x) {
		register int y = 0;
		for (; x; x -= lowbit(x)) y += val[x];
		return y;
	}
	inline void clear() {
		memset(val, 0, sizeof(val));
	}
};
BinaryIndexedTree_t g[SQRT], f[MAXN];
inline void add(int val, int pos) {
	g[belong(val)].add(belong(pos), 1);
	f[val].add(belong(pos), 1);
}
inline void del(int val, int pos) {
	g[belong(val)].add(belong(pos), -1);
	f[val].add(belong(pos), -1);
}
int n, m, a[MAXN], id[SQRT][MAXN], val[SQRT][MAXN];
inline int find(int x, int *p) { return x == p[x] ? x : p[x] = find(p[x], p); }
inline void bomb(int b) {
	fprintf(stderr, "PASS %d\n", __LINE__);
	for (int i = left(b); i <= right(b); i++) {
		int x = a[i];
		int y = find(x, p[b]);
		if (x == y) continue;
		del(x, i);
		add(y, i);
	}
}
inline void modify() {
	fprintf(stderr, "PASS %d\n", __LINE__);
	int l = $(), r = $(), x = $(), y = $();
	int L = belong(l), R = belong(r);
	if (L == R) {
		bomb(L);
		for (int i = l; i <= r; i++)
			if (a[i] == x) {
				del(a[i], i);
				add(a[i] = y, i);
			}
		return;
	}
	bomb(L);
	bomb(R);
	for (int i = l; i <= right(L); i++)
		if (a[i] == x) {
			del(a[i], i);
			add(a[i] = y, i);
		}
	for (int i = left(R); i <= r; i++)
		if (a[i] == x) {
			del(a[i], i);
			add(a[i] = y, i);
		}
	for (int i = L + 1; i < R; i++) {
		int count = f[x].get(i) - f[x].get(i - 1);
		if (!count) continue;
		val[i][id[i][x]] = y;
		id[i][y] = id[i][x];
		g[belong(x)].add(belong(i), -count);
		f[x].add(belong(i), -count);
		g[belong(y)].add(belong(i), count);
		f[y].add(belong(i), count);
	}
}
int tg[SQRT], tf[MAXN];
inline void query() {
	fprintf(stderr, "PASS %d\n", __LINE__);
	int l = $(), r = $(), k = $();
	int L = belong(l), R = belong(r);
	if (L == R) {
		bomb(L);
		int t = 0;
		for (int i = l; i <= r; i++) tg[++t] = a[i];
		std::sort(tg + 1, tg + t + 1);
		printf("%d\n", tg[k]);
		for (int i = 1; i <= t; i++) tg[i] = 0;
		return;
	}
	bomb(L);
	bomb(R);
	for (int i = l; i <= right(L); i++) tg[belong(a[i])]++, tf[a[i]]++;
	for (int i = left(R); i <= r; i++) tg[belong(a[i])]++, tf[a[i]]++;
	for (int i = 1; i <= SQRT; i++) {
		int count = g[i].get(R - 1) - g[i].get(L) + tg[i];
		if (count >= k) {
			for (int j = left(i); j <= right(i); j++) {
				int count = f[j].get(R - 1) - f[j].get(L) + tf[j];
				if (count >= k) {
					printf("%d\n", j);
					break;
				} else {
					k -= count;
				}
			}
			break;
		} else {
			k -= count;
		}
	}
	for (int i = l; i <= right(L); i++) tg[belong(a[i])]--, tf[a[i]]--;
}
int main() {
	freopen("in", "r", stdin);
	for (int t = $(); t; t--) {
		n = $(), m = $();
		for (int i = 1; left(i) <= n; i++) g[i].clear(), memset(p[i], 0, sizeof(p[i]));
		for (int i = 1; i <= n; i++) f[i].clear();
		for (int i = 1; i <= n; i++) add(a[i] = $(), i), p[belong(i)][a[i]] = a[i];
		for (int i = 1; i <= m; i++) $() == 1 ? modify() : query();
	}
	return 0;
}