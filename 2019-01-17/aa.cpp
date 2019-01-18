#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int n;
long long ans = 0;
int main() {
	for (n = 1; n <= 100; n++) {
        ans = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				long long lcm = 1LL * i * j / gcd(i, j);
				long long sub = (long long)sqrt(lcm);
				if (sub * sub == lcm) ans++;
			}
		}
		printf("%d = %lld\n", n, ans);
	}
	return 0;
}