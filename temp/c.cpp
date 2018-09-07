#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline int $() {
	register int x = 0, f = 0;
	register char ch = gc();
	while (!isdigit(ch) && (ch ^ 45)) ch = gc();
	if (!(ch ^ 45)) f = 1, ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return f ? -x : x;
}
#define MAXN 1000010
int n, m, near[MAXN], p, ans;
int main() {
	n = $(), m = $();
	for (int i = 1; i <= n; i++) near[i] = 0;
	for (int i = 1, l, r; i <= m; i++) {
		l = $(), r = $();
		if (l > r) std::swap(l, r);
		near[r] = std::max(near[r], l);
	}
	for (int i = 1; i <= n; i++) {
		if (p < near[i]) ans++, p = i - 1;
	}
	printf("%d\n", ans);
	return 0;
}