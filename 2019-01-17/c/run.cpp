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
std::vector<point_t> p, t, s;
int n, vis[1000000], match[1000000];
inline long long cross(point_t a, point_t b) { return a.x * b.y - a.y * b.x; }
int main() {
	scanf("%d", &n);
	n *= 2;
	for (int i = 1, x, y; i <= n; i++) {
		scanf("%d%d", &x, &y);
		p.push_back((point_t){x, y, i});
	}
	std::sort(p.begin(), p.end(), [](point_t a, point_t b) { return a.x == b.x ? a.y < b.y : a.x < b.x; });
	while (p.size()) {
        // fprintf(stderr, "New round\n");
		s.clear();
		for (int i = 0; i < (int)p.size(); i++) {
			while ((int)s.size() > 1 && cross(p[i] - s.back(), s.back() - s[s.size() - 2]) < 0) {
				s.pop_back();
			}
			s.push_back(p[i]);
		}
		for (int i = 1; i < (int)s.size(); i += 2) {
			vis[match[s[i - 1].id] = s[i].id] = vis[match[s[i].id] = s[i - 1].id] = 1;
			// fprintf(stderr, "SELECT (%d, %d) and (%d, %d)\n", s[i - 1].x, s[i - 1].y, s[i].x, s[i].y);
		}
		t = std::vector<point_t>(p);
		p.resize(std::distance(p.begin(), std::copy_if(t.begin(), t.end(), p.begin(), [](point_t p) { return !vis[p.id]; })));
	}
	for (int i = 1; i <= n; i++) printf("%d\n", match[i]);
	return 0;
}