#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
typedef long long lnt;
const lnt INF = (~0ULL) >> 2;
lnt x, y;
std::vector<lnt> dx, dy, dz;
inline int compare(const std::vector<lnt> &a, const std::vector<lnt> &b) {
	if (a.size() < b.size()) return -1;
	if (a.size() > b.size()) return 1;
	for (int i = (int)a.size() - 1; ~i; i--) {
		if (a[i] < b[i]) return -1;
		if (a[i] > b[i]) return 1;
	}
	return 0;
}
inline int valid(const std::vector<lnt> &a) {
	for (int i = (int)a.size() - 1; ~i; i--)
		if (a[i] >= 10) return 0;
	return 1;
}
int main() {
	scanf("%lld%lld", &x, &y);
	for (lnt i = y; i; i /= 10) dy.push_back(i % 10);
	for (int t = 1; t <= 1000; t++) {
		dz.clear();
		for (lnt i = t; i; i /= 10) dz.push_back(i % 10);
		lnt l = 10, r = INF;
		while (l <= r) {
			lnt mid = (l + r) >> 1;
			dx.clear();
			for (lnt i = x; i; i /= mid) dx.push_back(i % mid);
			int z = compare(dz, dx);
			if (z < 0) {
				l = mid + 1;
			} else if (z > 0) {
				r = mid - 1;
			} else {
				if (compare(dx, dy) >= 0 && valid(dx)) return printf("%lld\n", mid), 0;
				break;
			}
		}
	}
	for (int d = 1000000; d >= 10; d--) {
		dx.clear();
		for (lnt i = x; i; i /= d) dx.push_back(i % d);
		if (compare(dx, dy) >= 0 && valid(dx)) return printf("%d\n", d), 0;
	}
	puts("ψ(｀∇´)ψ");
	return 0;
}