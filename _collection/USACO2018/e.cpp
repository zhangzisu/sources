#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 100010
struct cow {
	int i, a, t;
	inline int friend operator<(const cow& a, const cow& b) {
		return a.i > b.i;
	}
} c[MAXN];
std::priority_queue<cow> Q;
int n, ans[MAXN];
int main() {
	freopen("convention2.in", "r", stdin);
	freopen("convention2.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &c[i].a, &c[i].t);
		c[i].i = i;
	}
	std::sort(c + 1, c + n + 1, [](const cow &a, const cow &b) { return a.a < b.a; });
	int last = 0;
	for (int i = 1; i <= n;) {
		while (Q.size()) {
			auto x = Q.top();
			Q.pop();
			ans[x.i] = last - x.a;
			last += x.t;
			for (; i <= n && c[i].a <= last; i++) Q.push(c[i]);
		}
		if (i <= n) {
			last = c[i].a + c[i].t;
			for (i++; i <= n && c[i].a <= last; i++) Q.push(c[i]);
		}
	}
	int max = 0;
	for (int i = 1; i <= n; i++) max = std::max(max, ans[i]);
	printf("%d\n", max);
	return 0;
}