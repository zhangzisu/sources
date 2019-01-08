#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define MAXN 100010
int n, m, p[MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
struct segment_t {
	int l, r, id;
	inline segment_t(int l = 0, int r = 0, int id = 0) : l(l), r(r), id(id) {}
	inline int friend operator<(const segment_t &a, const segment_t &b) {
		return a.r < b.r;
	}
};
std::set<segment_t> s;
int main() {
	scanf("%d", &m);
	for (int op, l, r; m; m--) {
		scanf("%d%d%d", &op, &l, &r);
		if (op == 2) {
			puts(find(l) == find(r) ? "YES" : "NO");
		} else {
            ++n;
			p[n] = n;
			auto t = s.upper_bound(segment_t(0, l, 0));
			while (t != s.end()) {
				if ((l < t->l && t->l < r) || (l < t->r && t->r < r)) {
					p[find(t->id)] = n;
					l = std::min(l, t->l);
					r = std::max(r, t->r);
					s.erase(t++);
				} else {
					break;
				}
			}
			s.insert(segment_t(l, r, n));
		}
	}
	return 0;
}