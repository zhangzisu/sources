#include <algorithm>
#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline unsigned $() {
	register unsigned x = 0;
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
std::pair<unsigned, unsigned> d[100010];
unsigned long long ans = 0;
unsigned num[100010], digit[32];
int n, m;
inline void calc(bool flag) {
	for (int i = 2; i <= n; i++) num[i] ^= num[i - 1];
	if (flag) {
		for (int i = 1; i <= n; i++) ans += num[i];
		return;
	}
	memset(digit, 0, sizeof(digit));
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 32; j++) digit[j] += (num[i] >> j) & 1;
	}
	for (int i = 0; i < 32; i++) ans += (unsigned long long)std::min(digit[i], n - digit[i] + 1) << i;
}
int main() {
	$();
	m = $();
	for (int i = 1; i <= m; i++) {
		unsigned int $1 = $(), $2 = $();
		d[i] = std::make_pair($1, $2);
	}
	std::sort(d + 1, d + m + 1);
	num[n = 1] = d[1].second;
	bool flag = d[1].first == 1;
	for (int i = 2; i <= m; i++) {
		if (d[i - 1].first + 1 == d[i].first)
			num[++n] = d[i].second;
		else {
			calc(flag);
			flag = 0;
			num[n = 1] = d[i].second;
		}
	}
	calc(flag);
	printf("%llu\n", ans);
	return 0;
}
