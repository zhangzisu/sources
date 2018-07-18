#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define D 65536
char _1[D], _2[D], *_3 = _1 + D, *_4 = _2;
inline char _getchar() {
	if (_3 == _1 + D) fread(_1, 1, D, stdin), _3 = _1;
	return *_3++;
}
inline int getInt() {
	register int __ = 0;
	register char _ = _getchar();
	while (!isdigit(_)) _ = _getchar();
	for (; isdigit(_); _ = _getchar()) __ = ((__ << 3) + (__ << 1)) + (_ ^ 48);
	return __;
}
inline void _putchar(char c) {
	if (_4 == _2 + D) fwrite(_2, 1, D, stdout), _4 = _2;
	*_4++ = c;
}
int _5[32];
inline void putInt(int x) {
	if (x == 0) {
		_putchar('0');
		return;
	}
	register int _6;
	for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
	while (_6) _putchar(_5[_6--] ^ 48);
}
inline void flush() { fwrite(_2, 1, _4 - _2, stdout); }
#define MAXN 200010
#define MAXM 400010
#define MAXK 5000010
int n, m;
struct edge {
	int u, v, l, a;
} e[MAXM];
int head[MAXN], next[MAXM << 1], val[MAXM << 1], to[MAXM << 1], tot;
inline void $(int u, int v, int w) {
	next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
std::priority_queue<std::pair<int, int>> Q;
int dis[MAXN];
inline void d(int s) {
	memset(dis, 0x3F, sizeof(dis));
	Q.emplace(-(dis[s] = 0), s);
	while (Q.size()) {
		auto t = Q.top();
		Q.pop();
		if (-t.first != dis[t.second]) continue;
		for (int x = t.second, i = head[t.second]; ~i; i = next[i]) {
			if (dis[to[i]] > dis[x] + val[i]) {
				Q.emplace(-(dis[to[i]] = dis[x] + val[i]), to[i]);
			}
		}
	}
}
int root[MAXM], L[MAXK], R[MAXK], all = 0;
struct t {
	int v, s, m;
	inline t(int v = 0, int s = 0, int m = 0) : v(v), s(s), m(m) {}
} dat[MAXK];
inline void copy(int &n, int N) {
	int g = ++all;
	dat[g] = dat[N];
	L[g] = L[N];
	R[g] = R[N];
	n = g;
}
inline void build(int &n, int l, int r) {
	n = ++all;
	if (l == r) return dat[n] = t(l, 1, dis[l]), void();
	int mid = (l + r) >> 1;
	build(L[n], l, mid);
	build(R[n], mid + 1, r);
}
inline t get(int n, int l, int r, int p) {
	if (l == r) return dat[n];
	int mid = (l + r) >> 1;
	if (p <= mid) return get(L[n], l, mid, p);
	return get(R[n], mid + 1, r, p);
}
inline void set(int &n, int N, int l, int r, int p, t v) {
	copy(n, N);
	if (l == r) return dat[n] = v, void();
	int mid = (l + r) >> 1;
	if (p <= mid) return set(L[n], L[N], l, mid, p, v);
	return set(R[n], R[N], mid + 1, r, p, v);
}
inline int find(int x, int tsp) {
	// for (int y = get(root[tsp], 1, n, x).v; x != y; y = get(root[tsp], 1, n, x).v) x = y;
	for (int y = get(root[tsp], 1, n, x).v; x != y;) {
		x = y;
		y = get(root[tsp], 1, n, x).v;
	}
	return x;
}
inline void reset() {
	memset(head, -1, sizeof(head));
	tot = all = 0;
}
int q, k, s, lans, _;
int main() {
	freopen("C:\\Users\\admin\\Desktop\\data\\return10.in", "r", stdin);
	_ = getInt();
	while (_--) {
		reset();
		n = getInt();
		m = getInt();
		for (int i = 1; i <= m; i++) {
			e[i].u = getInt();
			e[i].v = getInt();
			e[i].l = getInt();
			e[i].a = getInt();
		}
		for (int i = 1; i <= m; i++) $(e[i].u, e[i].v, e[i].l);
		d(1);

		std::sort(e + 1, e + m + 1, [](const edge &a, const edge &b) { return a.a > b.a; });
		build(root[0], 1, n);

		for (int i = 1; i <= m; i++) {
			int u = e[i].u, v = e[i].v;
			int U = find(u, i - 1);
			int V = find(v, i - 1);
			assert(U);
			assert(V);
			if (U == V) {
				root[i] = root[i - 1];
			} else {
				t uu = get(root[i - 1], 1, n, U);
				t vv = get(root[i - 1], 1, n, V);
				if (uu.s < vv.s) {
					std::swap(uu, vv);
					std::swap(U, V);
				}
				vv.v = U;
				uu.s += vv.s;
				uu.m = std::min(uu.m, vv.m);
				set(root[i], root[i - 1], 1, n, V, vv);
				set(root[i], root[i], 1, n, U, uu);
			}
		}

		q = getInt();
		k = getInt();
		s = getInt();
		while (q--) {
			int v0 = getInt(), p0 = getInt();
			int v = (v0 + k * lans - 1) % n + 1;
			int p = (p0 + k * lans) % (s + 1);
			printf("%d %d\n", v, p);
			int l = 1, r = m, ans = 0;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (e[mid].a > p) {
					ans = mid, l = mid + 1;
				} else {
					r = mid - 1;
				}
			}
			printf("%d\n", ans);
			int V = find(v, ans);
			printf("%d\n", V);
			t vv = get(root[ans], 1, n, V);
			// putInt(lans = vv.m);
			// _putchar(10);
			// flush();
			printf("%d\n", lans = vv.m);
		}
	}
	flush();
	return 0;
}