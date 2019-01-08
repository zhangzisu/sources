#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#define MAXN 200010
int n, p[MAXN], fa[MAXN], c[MAXN][2], d[MAXN];
inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
std::vector<int> next[MAXN];
struct frac_t {
	int a, b;
	inline frac_t(int a, int b) : a(a), b(b) {}
	inline bool friend operator<(const frac_t& a, const frac_t& b) {
		return 1LL * a.a * b.b < 1LL * b.a * a.b;
	}
	inline bool friend operator==(const frac_t& a, const frac_t& b) {
		return a.a == b.a && a.b == b.b;
	}
};
std::set<std::pair<frac_t, int>> S;
long long ans = 0;
int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		scanf("%d", &p[i]);
		d[p[i]]++;
	}
	for (int i = 1, v; i <= n; i++) {
		scanf("%d", &v);
		c[i][v]++;
		fa[i] = i;
	}
	for (int i = 2; i <= n; i++) S.emplace(frac_t(c[i][1], c[i][0]), i);
	for (int i = 2; i <= n; i++) {
		int x = S.begin()->second, y = find(p[x]);
		S.erase(S.begin());
		fa[x] = y;
		ans += 1LL * c[y][1] * c[x][0];
		if (y != 1) S.erase(std::make_pair(frac_t(c[y][1], c[y][0]), y));
		c[y][0] += c[x][0];
		c[y][1] += c[x][1];
		if (y != 1) S.emplace(frac_t(c[y][1], c[y][0]), y);
	}
	printf("%lld\n", ans);
	return 0;
}