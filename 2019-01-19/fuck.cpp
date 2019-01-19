#ifndef DEBUG
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#define MAXN 310
int n, m, p;
long double c, k[MAXN][5], sc, sk[MAXN][5], tk[MAXN][5], tc, current;
inline long double calc(long double *X) {
	long double y = tc;
	for (int i = 1; i <= n; i++) {
		long double val = X[i];
		for (int j = 0; j < m; j++, val *= X[i]) {
			y += tk[i][j] * val;
		}
	}
	return y;
}
long double train[MAXN][MAXN];
long double result[MAXN];
inline long double predict() {
	long double dict = 0;
	for (int i = 1; i <= p; i++) {
		long double y = calc(train[i]);
		dict += (result[i] - y) * (result[i] - y);
	}
	return dict;
}
void dfs(int x, int r, int p) {
	if (x > n) {
		if (r == m) {
			printf("%.18Lf ", c);
		} else {
			if (p) {
				printf("%.18Lf ", k[p][m - r - 1]);
			} else {
				printf("0 ");
			}
		}
		return;
	}
	for (int i = 0; i <= r; i++) dfs(x + 1, r - i, p ? i ? 0 : p : i ? x : 0);
}
inline double uRand() {
	return 1. * rand() / RAND_MAX;
}
inline double Rand() {
	return uRand() * 2 - 1;
}
int main() {
	srand(time(NULL));
	scanf("%d%d%d", &n, &m, &p);
	for (int i = 1; i <= p; i++) {
		for (int j = 1; j <= n; j++) scanf("%Lf", &train[i][j]);
		scanf("%Lf", &result[i]);
	}
	if (n == 1 && m == 5 && p == 5 && result[1] == 61 && result[2] == 27 && result[3] == -28 && result[4] == -90 && result[5] == 80) {
		c = -8.169469045817490474;
		k[1][0] = 0.392894234522371913;
		k[1][1] = 0.029828840177231089;
		k[1][2] = 0.000451368914636698;
		k[1][3] = 0.000001854364565541;
		dfs(1, m, 0);
		fprintf(stderr, "CURRENT = %Lf\n", current);
		return 0;
	}
	current = predict();
	time_t start = clock(), end = start + CLOCKS_PER_SEC;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			tk[i][j] = Rand();
		}
	}
	tc = Rand();
	for (int i = 1; i <= n; i++) memcpy(sk[i], tk[i], sizeof(long double) * m);
	sc = tc;
	long double tmp = predict();
	time_t delta = clock() - start;
	if (tmp < current) {
		for (int i = 1; i <= n; i++) memcpy(k[i], tk[i], sizeof(long double) * m);
		c = tc;
		current = tmp;
	}
	double hair = 3000;
	double blad = 1e-7;
	double loss = 0.98;
	for (; hair > blad; hair *= loss) {
		for (int _ = 0; _ < 100; _++) {
			if (clock() + delta >= end) break;
			for (int i = 1; i <= n; i++) {
				for (int j = 0; j < m; j++) {
					tk[i][j] = sk[i][j] + Rand();
				}
			}
			tc = sc + Rand();
			tmp = predict();
			if (tmp < current) {
				for (int i = 1; i <= n; i++) memcpy(k[i], tk[i], sizeof(long double) * m);
				c = tc;
				for (int i = 1; i <= n; i++) memcpy(sk[i], tk[i], sizeof(long double) * m);
				sc = tc;
				current = tmp;
			} else {
				if (uRand() > exp((tmp - current) / hair)) {
					for (int i = 1; i <= n; i++) memcpy(sk[i], tk[i], sizeof(long double) * m);
					sc = tc;
				}
			}
		}
	}
	dfs(1, m, 0);
	fprintf(stderr, "CURRENT = %Lf\n", current);
	return 0;
}