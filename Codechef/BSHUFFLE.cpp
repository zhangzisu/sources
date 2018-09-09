#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#define MAXN 10
int stack[MAXN], p[MAXN], n;
std::map<std::vector<int>, int> M;
void dfs(int x) {
	if (x > n) {
		for (int i = 1; i <= n; i++) p[i] = i;
		for (int i = 1; i <= n; i++) std::swap(p[i], p[stack[i]]);
		std::vector<int> v;
		for (int i = 1; i <= n; i++) v.push_back(p[i]);
		M[v]++;
		return;
	}
	for (int i = 1; i <= n; i++) {
		stack[x] = i;
		dfs(x + 1);
	}
}
int main() {
	scanf("%d", &n);
	dfs(1);
	int min = 1000000000, max = 0;
	for (auto x : M) {
		min = std::min(min, x.second);
		max = std::max(max, x.second);
	}
	for (auto x : M) {
		for (auto y : x.first) printf("%d ", y);
		printf("%d %s\n", x.second, x.second == max ? "MAX" : x.second == min ? "MIN" : "");
	}
	return 0;
}