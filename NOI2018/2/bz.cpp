#include <cstdio>
#include <iostream>
using namespace std;
const long long N = 100005;
long long n, r[N], m[N];
void exgcd(long long a, long long b, long long &d, long long &x, long long &y) {
	if (b == 0) {
		d = a, x = 1, y = 0;
		return;
	}
	exgcd(b, a % b, d, y, x);
	y -= a / b * x;
}
long long excrt() {
	long long M = m[1], R = r[1], x, y, d;
	for (long long i = 2; i <= n; i++) {
		exgcd(M, m[i], d, x, y);
		if ((r[i] - R) % d)
			return -1;
		x = (r[i] - R) / d * x % (m[i] / d);
		R = R + x * M;
		M = M / d * m[i];
		R %= M;
	}
	return R > 0 ? R : R + M;
}
int main() {
	while (~scanf("%lld", &n)) {
		for (long long i = 1; i <= n; i++)
			scanf("%lld%lld", &m[i], &r[i]);
		printf("%lld\n", excrt());
	}
	return 0;
}