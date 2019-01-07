#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
int can[2010];
void dfs(int d, std::vector<int> left, std::vector<int> right, int lsum) {
	if (!d) {
		can[lsum] = 1;
		return;
	}
	if (left.size() == right.size()) {
		for (int i = 0; i < (int)left.size(); i++) {
			int cur = left[i];
			std::vector<int> L(left), R(right);
			R.push_back(cur);
			L.erase(L.begin() + i);
			dfs(d - 1, L, R, lsum - cur);
		}
	} else {
		for (int i = 0; i < (int)right.size(); i++) {
			int cur = right[i];
			std::vector<int> L(left), R(right);
			L.push_back(cur);
			R.erase(R.begin() + i);
			dfs(d - 1, L, R, lsum + cur);
		}
	}
}
std::vector<int> l, r;
int main() {
    freopen("backforth.in", "r", stdin);
	freopen("backforth.out", "w", stdout);
	for (int i = 0, x; i < 10; i++) scanf("%d", &x), l.push_back(x);
	for (int i = 0, x; i < 10; i++) scanf("%d", &x), r.push_back(x);
	dfs(4, l, r, 1000);
	int ans = 0;
	for (int i = 0; i <= 2000; i++) ans += can[i];
	printf("%d\n", ans);
	return 0;
}