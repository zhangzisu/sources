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
	register int x = 0;
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 5010
typedef long long lnt;
int n, m, top;
struct data_t {
	int c, f, v;
	inline int friend operator<(const data_t& a, const data_t& b) {
		return a.f == b.f ? a.c > b.c : a.f > b.f;
	}
} data[MAXN];
lnt f[MAXN * 50], ans;
int main() {
	n = $();
	for (int i = 1; i <= n; i++) {
		data[i].c = $();
		data[i].f = $();
		data[i].v = -$();
	}
	m = $();
	for (int i = 1; i <= m; i++) {
		data[n + i].c = -$();
		data[n + i].f = $();
		data[n + i].v = $();
	}
	n += m;
	std::sort(data + 1, data + n + 1);
	memset(f, 0x80, sizeof(f));
	f[0] = 0;
	for (int i = 1; i <= n; i++) {
		top = std::max(top, top + data[i].c);
		if (data[i].c >= 0) {
			for (int j = top; j >= data[i].c; j--) {
				f[j] = std::max(f[j], f[j - data[i].c] + data[i].v);
				ans = std::max(ans, f[j]);
			}
		} else {
			for (int j = 0; j <= top + data[i].c; j++) {
				f[j] = std::max(f[j], f[j - data[i].c] + data[i].v);
				ans = std::max(ans, f[j]);
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}