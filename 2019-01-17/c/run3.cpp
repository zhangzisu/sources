#include <algorithm>
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
std::vector<point_t> p, l, r;
int n, vis[1000000], match[1000000];
inline long long cross(point_t a, point_t b) { return a.x * b.y - a.y * b.x; }
double sumx = 0;
int main() {
	scanf("%d", &n);
	n *= 2;
	for (int i = 1, x, y; i <= n; i++) {
		scanf("%d%d", &x, &y);
		p.push_back((point_t){x, y, i});
		sumx += x;
	}
	sumx /= n;
	for (int i = 0; i < n; i++) {
		if (p[i].x < sumx) {
			l.push_back(p[i]);
		} else {
			r.push_back(p[i]);
		}
	}
	fprintf(stderr, "%d === %d\n", n, (int)(l.size() + r.size()));
	int g = std::min(l.size(), r.size());
	fprintf(stderr, "%d\n", g);
	std::sort(l.begin(), l.end(), [](point_t a, point_t b) { return a.y < b.y; });
	std::sort(r.begin(), r.end(), [](point_t a, point_t b) { return a.y < b.y; });
	for (int i = 0; i < g; i++) {
		match[l[i].id] = r[i].id;
		match[r[i].id] = l[i].id;
	}
	for (int i = g + 1; i < (int)l.size(); i += 2) {
		match[l[i - 1].id] = l[i].id;
		match[l[i].id] = l[i - 1].id;
	}
	for (int i = g + 1; i < (int)r.size(); i += 2) {
		match[r[i - 1].id] = r[i].id;
		match[r[i].id] = r[i - 1].id;
	}
	for (int i = 1; i <= n; i++) printf("%d\n", match[i]);
	return 0;
}