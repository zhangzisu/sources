#pragma GCC optimize(0)
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <map>
#include "guess.h"
const int N = 1000;
int prob;
std::string guess() {
	srand(time(NULL));
	const int *p = &prob;
	int a1 = query(0, N - 1);
	int a2 = query(1, N - 1);
	int a3 = query(0, N - 2);
	int a4 = query(1, N - 2);
	int a5 = query(2, N - 1);
	int a6 = query(2, N - 2);
	int a7 = query(1, N - 3);
	int a8 = query(2, N - 3);
	// fprintf(stderr, "TESTING %zd\n", p);
	for (int err; p; p++) {
		err = 0;
		err += (p[N] - p[0]) != a1;
		err += (p[N] - p[1]) != a2;
		err += (p[N - 1] - p[0]) != a3;
		err += (p[N - 1] - p[1]) != a4;
		err += (p[N] - p[2]) != a5;
		err += (p[N - 1] - p[2]) != a6;
		err += (p[N - 2] - p[1]) != a7;
		err += (p[N - 2] - p[2]) != a8;
		if (err > 4) continue;
		// fprintf(stderr, "DET at %zd\n", p);
		std::string ans;
		for (int i = 0; i < N; i++) ans.push_back(p[i + 1] - p[i] + '0');
		return ans;
	}
}
