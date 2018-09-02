#include <algorithm>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 65536
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline void pc(char c) {
	if (_4 == _2 + BUF) fwrite(_2, 1, BUF, stdout), _4 = _2;
	*_4++ = c;
}
inline void rt() { fwrite(_2, 1, _4 - _2, stdout), exit(0); }
inline void pi(int x) {
	static int _5[32];
	if (!x) {
		pc('0');
		return;
	}
	if (x < 0) {
		pc(45);
		x = -x;
	}
	register int _6;
	for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
	while (_6) pc(_5[_6--] ^ 48);
}
inline int $() {
	register int x = 0;
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 100001
#define SQRT 320
#define BLOCK 30001
int n, m, k, a[MAXN], b[MAXN], v[MAXN], id[BLOCK][3], ans[BLOCK];
std::bitset<MAXN> val[BLOCK], tmp;
struct query_t {
	int l, r, id;
	inline query_t(int l = 0, int r = 0, int id = 0) : l(l), r(r), id(id) {}
} query[BLOCK * 3];
inline int cmp(const query_t& a, const query_t& b) {
	return a.l / SQRT == b.l / SQRT ? a.r < b.r : a.l < b.l;
}
inline void solve(int m) {
	k = 0;
	for (int i = 1; i <= m; i++) {
		ans[i] = 0;
		val[i].reset();
		val[i] = ~val[i];
		for (int j = 0; j < 3; j++) {
			id[i][j] = ++k;
			query[k].l = $();
			query[k].r = $();
			ans[i] += query[k].r - query[k].l + 1;
			query[k].id = i;
		}
	}
	std::sort(query + 1, query + k + 1, cmp);
	tmp.reset();
	memset(b, 0, sizeof(b));
	for (int i = 1, l = 1, r = 0; i <= k; i++) {
		const query_t& q = query[i];
		while (r < q.r) ++r, tmp.set(a[r] + b[a[r]]++);
		while (l > q.l) --l, tmp.set(a[l] + b[a[l]]++);
		while (r > q.r) tmp.reset(a[r] + --b[a[r]]), --r;
		while (l < q.l) tmp.reset(a[l] + --b[a[l]]), ++l;
		val[q.id] &= tmp;
	}
	for (int i = 1; i <= m; i++) {
		pi(ans[i] - 3 * (int)val[i].count());
		pc(10);
	}
}
int main() {
	n = $(), m = $();
	for (int i = 1; i <= n; i++) a[i] = $();
	memcpy(v, a, sizeof(v));
	std::sort(v + 1, v + n + 1);
	for (int i = 1; i <= n; i++) a[i] = std::lower_bound(v + 1, v + n + 1, a[i]) - v;
	for (; m > 30000; m -= 30000) solve(30000);
	solve(m);
	rt();
}
