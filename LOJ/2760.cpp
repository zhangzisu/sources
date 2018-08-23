#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#define MAXN 100010
typedef long long lnt;
int n, m, q, color;
struct line_t {
	int x0, y0, x1, y1;
} lines[MAXN];
std::vector<int> vx, vy;
inline void getIndex(int& x, const std::vector<int>& v) { x = std::lower_bound(v.begin(), v.end(), x) - v.begin(); }
std::vector<std::pair<int, int>> hz[MAXN];
std::vector<int> ad[MAXN], dl[MAXN];
std::set<int> S;
int BIT[MAXN];
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int v) {
	for (; x <= m; x += lowbit(x)) BIT[x] += v;
}
inline int qry(int x) {
	register int v = 0;
	for (; x; x -= lowbit(x)) v += BIT[x];
	return v;
}
int tag[MAXN << 2];
void pushDown(int n) {
	if (tag[n]) {
		tag[n << 1] = tag[n << 1 | 1] = 1;
		tag[n] = 0;
	}
}
void reset(int n, int l, int r, int L, int R) {
	if (l == L && r == R) return tag[n] = 1, void();
	if (tag[n]) return;
	int mid = (l + r) >> 1;
	if (R <= mid) return reset(n << 1, l, mid, L, R);
	if (L > mid) return reset(n << 1 | 1, mid + 1, r, L, R);
	reset(n << 1, l, mid, L, mid);
	reset(n << 1 | 1, mid + 1, r, mid + 1, R);
}
int& dead(int n, int l, int r, int p) {
	if (l == r) return tag[n];
	int mid = (l + r) >> 1;
	pushDown(n);
	return p <= mid ? dead(n << 1, l, mid, p) : dead(n << 1 | 1, mid + 1, r, p);
}
int p[MAXN << 2], id[MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
inline int merge(int x, int y) {
	int X = find(x), Y = find(y);
	if (X == Y) return 0;
	p[X] = Y;
	return 1;
}
inline void declare(int x) {
	int& val = dead(1, 0, m - 2, x);
	if (val) {
		val = 0;
		++color;
		p[id[x] = color] = color;
	}
	// fprintf(stderr, "! DECLARE %d -> %d\n", x, id[x]);
}
int ans = 0;
int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= q; i++) {
		scanf("%d%d%d%d", &lines[i].x0, &lines[i].y0, &lines[i].x1, &lines[i].y1);
		if (lines[i].x0 > lines[i].x1) std::swap(lines[i].x0, lines[i].x1);
		if (lines[i].y0 > lines[i].y1) std::swap(lines[i].y0, lines[i].y1);
		vx.push_back(lines[i].x0);
		vx.push_back(lines[i].x1);
		vy.push_back(lines[i].y0);
		vy.push_back(lines[i].y1);
	}
	vx.push_back(0);
	vx.push_back(-1);
	vx.push_back(n);
	vx.push_back(n + 1);
	vy.push_back(0);
	vy.push_back(-1);
	vy.push_back(m);
	vy.push_back(m + 1);
	std::sort(vx.begin(), vx.end());
	vx.erase(std::unique(vx.begin(), vx.end()), vx.end());
	std::sort(vy.begin(), vy.end());
	vy.erase(std::unique(vy.begin(), vy.end()), vy.end());
	++q;
	lines[q].x0 = lines[q].x1 = 0;
	lines[q].y0 = 0;
	lines[q].y1 = m;
	++q;
	lines[q].x0 = lines[q].x1 = n;
	lines[q].y0 = 0;
	lines[q].y1 = m;
	++q;
	lines[q].y0 = lines[q].y1 = 0;
	lines[q].x0 = 0;
	lines[q].x1 = n;
	++q;
	lines[q].y0 = lines[q].y1 = m;
	lines[q].x0 = 0;
	lines[q].x1 = n;
	n = (int)vx.size();
	m = (int)vy.size();
	for (int i = 1; i <= q; i++) {
		getIndex(lines[i].x0, vx);
		getIndex(lines[i].x1, vx);
		getIndex(lines[i].y0, vy);
		getIndex(lines[i].y1, vy);
		if (lines[i].x0 == lines[i].x1) {
			hz[lines[i].x0].emplace_back(lines[i].y0, lines[i].y1);
			// fprintf(stderr, "Horizontal %d - %d at x = %d\n", lines[i].y0, lines[i].y1, lines[i].x0);
		} else if (lines[i].y0 == lines[i].y1) {
			ad[lines[i].x0].push_back(lines[i].y0);
			// fprintf(stderr, "Vertical add %d at x = %d\n", lines[i].y0, lines[i].x0);
			dl[lines[i].x1].push_back(lines[i].y0);
			// fprintf(stderr, "Vertical del %d at x = %d\n", lines[i].y0, lines[i].x1 + 1);
		} else {
			return puts("cgc ak la!!!"), 0;
		}
	}
	for (int i = 0; i < n; i++) {
		// fprintf(stderr, "# PROCESS %d\n", i);
		for (auto v : ad[i]) {
			add(v, 1);
			S.insert(v);
			int left = *--S.lower_bound(v);
			declare(left);
			declare(v);
			merge(id[left], id[v]);
		}
		for (auto h : hz[i]) {
			int l = h.first, r = h.second;
			int L = *S.lower_bound(l);
			int R = *--S.upper_bound(r);
			if (L < R) {
				int count = qry(R - 1) - qry(L);
				ans += count + 1;
				fprintf(stderr, "$ ans = %d\n", ans);
				// fprintf(stderr, "RESET %d - %d\n", L, R - 1);
				reset(1, 0, m - 2, L, R - 1);
			}
		}
		for (auto v : dl[i]) {
			int left = *--S.lower_bound(v);
			declare(left);
			declare(v);
			ans -= merge(id[left], id[v]);
			fprintf(stderr, "$ ans = %d\n", ans);
			add(v, -1);
			S.erase(v);
		}
	}
	printf("%d\n", ans);
	return 0;
}