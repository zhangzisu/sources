#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define MAXN 300010
int n, a[MAXN], b[MAXN], c[MAXN];
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cin >> n;
	for (int i = 1; i <= n; i++) std::cin >> a[i], c[a[i]] = i;
	for (int i = 1; i <= n; i++) b[i] = a[i] == i ? 1 : 2;
	for (int l = 1, r = 1; r <= n;) {
		for (int i = l; i <= r; i++) r = std::max(r, c[i]);
		for (int i = l, x = 0, y = 0; i <= r; i += 2) {
			if (i + 1 <= r && a[i + 1] != i + 1) {
				std::cout << "No" << std::endl;
				return 0;
			}
			if (a[i] > i) {
				if (a[i] > x) {
					x = a[i];
				} else {
					std::cout << "No" << std::endl;
					return 0;
				}
			} else {
				if (a[i] > y) {
					y = a[i];
				} else {
					std::cout << "No" << std::endl;
					return 0;
				}
			}
		}
		l = ++r;
	}
	std::cout << "Yes" << std::endl;
	return 0;
}