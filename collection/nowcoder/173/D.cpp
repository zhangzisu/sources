#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#define MAXN 1025
inline int $() {
	register char ch = getchar();
	register int x = 0;
	while (!isdigit(ch)) ch = getchar();
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
int n, m, k, a[MAXN], b[MAXN], can[MAXN];
inline bool judge(int x) {
	if (__builtin_popcount(x) != k) return 0;
	for (int i = 1; i < (1 << n); i++) can[i] = (x >> (i - 1)) & 1;
	for (int i = 1; i <= m; i++)
		if (!can[a[i]]) return 0;
	for (int i = 1; i < (1 << n); i++)
		for (int j = 1; j < (1 << n); j++)
			if (!can[i | j] && can[i] && can[j]) return 0;
	for (int i = 0; i < (1 << n); i++) can[i] = !can[i];
	for (int i = 1; i < (1 << n); i++)
		for (int j = 1; j < (1 << n); j++)
			if (!can[i | j] && can[i] && can[j]) return 0;
	return 1;
}
int main() {
	n = $(), m = $(), k = $();
	for (int i = 1; i <= m; i++) a[i] = $();
	for (int d = 0, in = (1 << n) - 1, st = (1 << in); d < st; d++) {
		if (judge(d)) {
			for (int i = 0; i < in; i++) printf("%d", (d >> i) & 1);
			puts("");
			return 0;
		}
	}
	puts("-1");
	return 0;
}