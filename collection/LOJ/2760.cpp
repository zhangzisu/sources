#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#define MAXN 500010
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
int sum[MAXN << 2];
inline void add(int n, int l, int r, int p, int v) {
	if (l == r) return sum[n] += v, void();
	int mid = (l + r) >> 1;
	p <= mid ? add(n << 1, l, mid, p, v) : add(n << 1 | 1, mid + 1, r, p, v);
	sum[n] = sum[n << 1] + sum[n << 1 | 1];
}
inline int query(int n, int l, int r, int L, int R) {
	if (l == L && r == R) return sum[n];
	int mid = (l + r) >> 1;
	if (R <= mid) return query(n << 1, l, mid, L, R);
	if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R);
	return query(n << 1, l, mid, L, mid) + query(n << 1 | 1, mid + 1, r, mid + 1, R);
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
int p[MAXN << 2], id[MAXN << 2];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
inline int merge(int x, int y) {
	int X = find(x), Y = find(y);
	if (X == Y) return 0;
	p[X] = Y;
	return 1;
}
inline void declare(int x) {
	int& val = dead(1, 0, m, x);
	if (val) {
		val = 0;
		++color;
		p[id[x] = color] = color;
	}
	// fprintf(stderr, "! DECLARE %d -> %d\n", x, id[x]);
}
lnt ans = 0;
int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= q; i++) scanf("%d%d%d%d", &lines[i].x0, &lines[i].y0, &lines[i].x1, &lines[i].y1);
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
	for (int i = 1; i <= q; i++) {
		if (lines[i].x0 > lines[i].x1) std::swap(lines[i].x0, lines[i].x1);
		if (lines[i].y0 > lines[i].y1) std::swap(lines[i].y0, lines[i].y1);
		vx.push_back(lines[i].x0);
		vx.push_back(lines[i].x1);
		vy.push_back(lines[i].y0);
		vy.push_back(lines[i].y1);
	}
	vy.push_back(-1);
	std::sort(vx.begin(), vx.end());
	vx.erase(std::unique(vx.begin(), vx.end()), vx.end());
	std::sort(vy.begin(), vy.end());
	vy.erase(std::unique(vy.begin(), vy.end()), vy.end());
	n = (int)vx.size();
	m = (int)vy.size();
	S.insert(0);
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
			// fprintf(stderr, "> ADD %d: %d\n", v, 1);
			add(1, 0, m, v, 1);
			S.insert(v);
			int left = *--S.lower_bound(v);
			declare(left);
			declare(v);
			merge(id[left], id[v]);
		}
		for (auto h : hz[i]) {
			int l = h.first, r = h.second;
			int count = query(1, 0, m, l, r);
			if (count >= 2) {
				int L = *S.lower_bound(l);
				int R = *--S.upper_bound(r);
				ans += count - 1;
				reset(1, 0, m, L, R - 1);
			}
		}
		for (auto v : dl[i]) {
			// fprintf(stderr, "> ADD %d: %d\n", v, -1);
			int left = *--S.lower_bound(v);
			declare(left);
			declare(v);
			ans -= merge(id[left], id[v]);
			// fprintf(stderr, "$ ans = %d\n", ans);
			add(1, 0, m, v, -1);
			S.erase(v);
		}
	}
	printf("%lld\n", ans);
	// fprintf(stderr, "%d %lu %lu\n", color, vx.size(), vy.size());
	return 0;
}