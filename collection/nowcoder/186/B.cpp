#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
inline int fuck(int a, int b, int p) {
	int r = 1;
	for (; b; b >>= 1) {
		if (b & 1) r = 1LL * r * a % p;
		a = 1LL * a * a % p;
	}
	return r;
}
#define MAXN 10000000
int pos[MAXN + 10];
int p, inv3, ansm, ansn;
int main() {
	while (~scanf("%d", &p)) {
		memset(pos, 0, sizeof(pos));
		inv3 = fuck(3, p - 2, p);
		int inv = 1;
		for (int i = 1; i <= p; i++) {
			inv = 1LL * inv * inv3 % p;
			if (!pos[inv]) pos[inv] = i;
		}
		ansm = ansn = 1e7;
		for (int n = 1, t = 1; n <= p; n++) {
			t = (t << 1) % p;
			if (t <= p && pos[t] && n + pos[t] <= p) {
				if (n + pos[t] < ansm + ansn) ansm = n, ansn = pos[t];
			}
		}
		printf("%d %d\n", ansm, ansn);
	}
	return 0;
}