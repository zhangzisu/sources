#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int MOD = 23333;
const int MAX = 100010;
int head[MOD], key[MAX], val[MAX], next[MAX], tot;
inline void add(int k, int v) {
	next[tot] = head[k % MOD];
	key[tot] = k;
	val[tot] = v;
	head[k % MOD] = tot++;
}
const int INF = (~0U) >> 1;
int p, s, b, n;
inline int fuck(int x, int y) {
	int z = 1;
	for (; y; y >>= 1) {
		if (y & 1) z = 1LL * z * x % p;
		x = 1LL * x * x % p;
	}
	return z;
}
int main() {
	while (~scanf("%d%d%d", &p, &b, &n)) {
		memset(head, -1, sizeof(head));
		tot = 0;
		s = (int)sqrt(p);
		int inv = 1;
		for (int i = 0; i < s; i++, inv = 1LL * inv * b % p) add(inv, i);
		inv = fuck(inv, p - 2);
		int ans = INF;
		for (int x = 0, t = n; x <= s; x++, t = 1LL * t * inv % p) {
			for (int i = head[t % MOD]; ~i; i = next[i]) {
				if (key[i] == t) {
					ans = std::min(ans, x * s + val[i]);
				}
			}
		}
		if (ans == INF) {
			puts("no solution");
		} else {
			printf("%d\n", ans);
		}
	}
	return 0;
}