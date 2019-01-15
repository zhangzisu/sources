#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include "guess.h"
const int N = 1000;
int ans[N][N];
inline int wq(int l, int r) {
	assert(l <= r);
	if (~ans[l][r]) return ans[l][r];
	return ans[l][r] = query(l, r);
}
const double q1 = 10, q2 = 1;
std::string guess() {
	memset(ans, -1, sizeof(ans));
	std::string ans;
	for (int i = 0; i < N; i++) {
		double c0 = 0, c1 = 0;
		for (int j = 0; j <= i - 100; j++) {
			int result = wq(j, i) - wq(j, i - 1);
			if (result >= 0 && result <= 1) {
				(result == 0 ? c0 : c1) += q1;
			} else {
				(result < 0 ? c0 : c1) += q2;
			}
		}
		for (int j = N - 1; j >= i + 100; j--) {
			int result = wq(i, j) - wq(i + 1, j);
			if (result >= 0 && result <= 1) {
				(result == 0 ? c0 : c1) += q1;
			} else {
				(result < 0 ? c0 : c1) += q2;
			}
		}
		ans.push_back(c1 > c0 ? '1' : '0');
	}
	return ans;
}
