#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 1000010
int n, k, a[MAXN];
std::vector<int> v;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= 2 * n * k; i++) scanf("%d", a + i);
	std::sort(a + 1, a + 2 * n * k + 1);
	int l = 0, r = 0x3F3F3F3F;
	while (l <= r) {
		int mid = (l + r) >> 1;
		v.clear();
		for (int i = 1, last = 0; i <= 2 * n * k; i++) {
			if (last && a[i] - a[last] <= mid) {
				v.push_back(last);
				v.push_back(i);
				last = 0;
				if (2 * n == (int)v.size()) break;
			} else {
				last = i;
			}
		}
		if (2 * n != (int)v.size()) {
			l = mid + 1;
		} else {
			int rest = 0;
			v.push_back(2 * n * k + 1);
			for (int i = 2 * n - 1; ~i; i--) {
				rest += v[i + 1] - v[i] - k;
				if (rest < 0) break;
			}
			if (rest < 0) {
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
	}
	printf("%d\n", r + 1);
	return 0;
}