#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#define MAXN 10010
int n, m;
struct data {
	std::string name;
	int year;
	inline data(std::string name, int year) : name(name), year(year) {}
	inline int friend operator<(const data& a, const data& b) {
		return a.year < b.year;
	}
};
std::vector<data> d[10000];
int main() {
	std::ios::sync_with_stdio(0);
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		std::string name;
		int birth;
		std::cin >> name >> birth;
		d[birth % 10000].emplace_back(name, birth / 10000);
	}
	for (int i = 0; i < 10000; i++) std::sort(d[i].begin(), d[i].end());
	for (int a, b; m; m--) {
		std::cin >> a >> b;
		std::cout << d[b][a - 1].name << std::endl;
	}
	return 0;
}