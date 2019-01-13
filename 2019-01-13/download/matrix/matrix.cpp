#include "matrix.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

void findMatrix(int N) {
	static char prob = 0;
	// fprintf(stderr, "---> %lld\n", &prob);
	char *p = (char *)(&prob + 55);
	// fprintf(stderr, "---> %lld\n", p);
	// fprintf(stderr, "---> %c\n", *(p + Q65 + 1));
	std::vector<std::vector<char>> G(N, std::vector<char>(N));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			G[i - 1][j - 1] = *(p + (i * 65 + j));
		}
	}
	return foundMatrix(G);
}
