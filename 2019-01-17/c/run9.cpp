#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>
const double PI = acos(-1);
struct point_t {
	double x, y;
	int id;
};
std::vector<point_t> p, t, l, r;
int n, vis[1000000], match[1000000];
double sumx = 0;
int main() {
	srand(time(NULL));
	scanf("%d", &n);
	n *= 2;
	for (int i = 1; i <= n; i++) {
		double x, y;
		scanf("%lf%lf", &x, &y);
		double dis = sqrt(x * x + y * y);
		double angle = atan2(y, x);
		p.push_back((point_t){dis, angle, i});
	}
	for (int T = 1; T; T--) {
		double delta = 1. * rand() / 360 - 180;
		double delta = 0;
		t.resize(n);
		std::transform(p.begin(), p.end(), t.begin(), [delta](point_t p) {
			double x = p.x * cos(p.y + delta);
			double y = p.x * sin(p.y + delta);
			return point_t{x, y, p.id};
		});
		std::sort(t.begin(), t.end(), [](point_t a, point_t b) { return a.x == b.x ? a.y < b.y : a.x < b.x; });
		l.resize(n / 2);
		r.resize(n / 2);
		std::copy(t.begin(), t.begin() + (n / 2), l.begin());
		std::copy(t.begin() + (n / 2), t.end(), r.begin());
		//
	}
	return 0;
}