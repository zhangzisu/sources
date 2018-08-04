#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
const int INF = (~0U) >> 1;
int n, a, b, p, m;
std::vector<std::pair<int, int> > v;
inline void emplace(int l, int r) {
	if (l > r) {
		v.push_back(std::make_pair(l, n - 1));
		v.push_back(std::make_pair(0, r));
	} else {
		v.push_back(std::make_pair(l, r));
	}
}
int main() {
	scanf("%d%d%d%d%d", &n, &a, &b, &p, &m);
	for (int i = 1, x, t = 0; i <= m; i++, t = (t + a) % n) {
		scanf("%1d", &x);
		if (x) {
			// (start + t) % n >= p
			emplace((n - t) % n, (n + p - 1 - t) % n);
		} else {
			// start + t < p
			emplace((n + p - t) % n, (n - 1 - t + n) % n);
		}
	}
	for (int i = n - m + 1; i < n; i++) {
		emplace((1LL * a * i + b) % n, (1LL * a * i + b) % n);
	}
	std::sort(v.begin(), v.end());
	int all = 0, L = 0, R = -1;
	for (int i = 0; i < (int)v.size(); i++) {
		if (v[i].first > R) {
			all += R - L + 1;
			L = v[i].first;
			R = v[i].second;
		} else {
			R = std::max(R, v[i].second);
		}
	}
	all += R - L + 1;
	printf("%d\n", n - all);
	return 0;
}