#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
struct point_t {
	int x, y, id;
	inline point_t friend operator-(point_t a, point_t b) {
		return point_t{a.x - b.x, a.y - b.y, 0};
	}
};
std::vector<point_t> p, l, r, all;
int n, vis[1000000], match[1000000];
double sumx = 0;
double dis(point_t a, point_t b) { return sqrt(1. * (a.x - b.x) * (a.x - b.x) + 1. * (a.y - b.y) * (a.y - b.y)); }
int main() {
	scanf("%d", &n);
	n *= 2;
	for (int i = 1, x, y; i <= n; i++) {
		scanf("%d%d", &x, &y);
		p.push_back((point_t){x, y, i});
	}
	std::sort(p.begin(), p.end(), [](point_t a, point_t b) { return a.y == b.y ? a.x < b.x : a.y < b.y; });
	double vmid = 0, vcnt = 0, hmid = 0, hcnt = 0;
	for (auto x : p) {
		if (x.y != p[0].y) break;
		vmid += x.x;
		vcnt++;
	}
	vmid /= vcnt;
	for (auto x : p) {
		hmid += x.y;
		hcnt++;
		if (x.x <= vmid) {
			l.push_back(x);
		} else {
			r.push_back(x);
		}
	}
	hmid /= hcnt;
	fprintf(stderr, "%d === %d\n", n, (int)(l.size() + r.size()));
	std::sort(l.begin(), l.end(), [hmid](point_t a, point_t b) { return a.y == b.y ? ((a.y < hmid) ? (a.x > b.x) : (a.x < b.x)) : a.y < b.y; });
	std::sort(r.begin(), r.end(), [hmid](point_t a, point_t b) { return a.y == b.y ? ((a.y < hmid) ? (a.x < b.x) : (a.x > b.x)) : a.y < b.y; });
	all.resize(n);
	std::copy(l.begin(), l.end(), all.begin());
	std::copy(r.rbegin(), r.rend(), all.begin() + l.size());
	double best = 0;
	int pos = 0;
	for (int i = 0; i < n; i++) {
		int l = i, r = (i + 1) % n;
		double tmp = 0;
		for (;; l = (l - 1 + n) % n, r = (r + 1) % n) {
			tmp += dis(all[l], all[r]);
			if ((l - 1 + n) % n == r || (r + 1) % n == l) break;
		}
		if (tmp > best) {
			best = tmp;
			pos = i;
		}
	}
	fprintf(stderr, "BEST = %lf\n", best);
	int l = pos, r = (pos + 1) % n;
	for (;; l = (l - 1 + n) % n, r = (r + 1) % n) {
		match[all[l].id] = all[r].id;
		match[all[r].id] = all[l].id;
		if ((l - 1 + n) % n == r || (r + 1) % n == l) break;
	}
	for (int i = 1; i <= n; i++) printf("%d\n", match[i]);
	return 0;
}