#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
bool vis[3389];
std::vector<int> ans;
int main() {
	int a = 1;
	while (!vis[a]) {
		vis[a] = 1;
		ans.push_back(a);
		a = (1234 * a + 5678) % 3389;
	}
	for (auto v : ans) printf("%d,", v);
}