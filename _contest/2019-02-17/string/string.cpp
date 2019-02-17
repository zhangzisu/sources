#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int MOD = 998244353;
inline void trim(int &x) { x -= MOD, x += (x >> 31) & MOD; }
int n, a[50], b[50], c[50], d, e;
char buf[100];
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", buf);
		for (int j = 0; buf[j]; j++) (buf[j] == '?' ? ++d, c : buf[j] == '0' ? a : b)[j] |= 1 << i;
	}
	for (int d = (1 << n) - 1; d; d--) {
		int ans = 0, all = __builtin_popcount(d), cur = 1, p = 0;
		for (int i = 0; ((a[i] | b[i] | c[i]) & d) == d; i++) {
			if ((a[i] & d) && (b[i] & d)) break;
			int cnt = __builtin_popcount(c[i] & d);
			if (cnt == all) trim(cur += cur);
			//
		}
	}
	return 0;
}
