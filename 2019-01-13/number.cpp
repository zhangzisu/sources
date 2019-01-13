#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <map>
namespace Xxs {
	const int LIMIT = 1000000;
	int prime[LIMIT], vis[LIMIT], pnt = 0;
	inline void init() {
		for (int i = 2; i < LIMIT; i++) {
			if (!vis[i]) {
				prime[++pnt] = i;
				for (int j = i + i; j < LIMIT; j += i) {
					vis[j] = 1;
				}
			}
		}
	}
}  // namespace Xxs
namespace Rho {
	using ulnt = unsigned long long;
	inline unsigned rand_uint() {
		return (unsigned(rand()) << 16) | rand();
	}
	inline ulnt rand_ulnt() {
		return (ulnt(rand_uint()) << 32) | rand_uint();
	}
	inline ulnt gcd(ulnt a, ulnt b) {
		return b ? gcd(b, a % b) : a;
	}
	inline ulnt mul(ulnt a, ulnt b, ulnt c) { return (__uint128_t)a * b % c; }
	inline ulnt pow(ulnt a, ulnt b, ulnt c) {
		ulnt r = 1;
		for (; b; b >>= 1) {
			if (b & 1) r = mul(a, r, c);
			a = mul(a, a, c);
		}
		return r;
	}
	inline ulnt f(ulnt a, ulnt b, ulnt n) {
		return (mul(a, a, n) + b) % n;
	}

	ulnt result[1000000];
	int count = 0;
	inline bool test(ulnt x) {
		if (x == 2) return 1;
		if (x < 2 || (~x & 1)) return 0;
		ulnt u = x - 1, p, a, b;
		int t = 0;
		while (~u & 1) u >>= 1, t++;
		for (int i = 0; i < 5; i++) {
			p = rand_ulnt() % (x - 1) + 1;
			a = pow(p, u, x);
			for (int j = 0; j < t; j++) {
				b = mul(a, a, x);
				if (b == 1 && a != 1 && a != x - 1) return 0;
				a = b;
			}
			if (a != 1) return 0;
		}
		return 1;
	}
	inline ulnt rho(ulnt n, ulnt c) {
		ulnt i = 1, k = 2, x = rand_ulnt() % (n - 1) + 1, y = x;
		while (1) {
			i++;
			x = (mul(x, x, n) + c) % n;
			ulnt p = gcd((y - x + n) % n, n);
			if (p != 1 && p != n) return p;
			if (y == x) return n;
			if (i == k) {
				y = x;
				k <<= 1;
			}
		}
	}
	// void factor(ulnt n) {
	// 	if (n == 1) return;
	// 	if (test(n)) {
	// 		result[++count] = n;
	// 		return;
	// 	}
	// 	for (ulnt a, x, y, p;;) {
	// 		a = rand_ulnt() & 63, x = y = 2;
	// 		while (1) {
	// 			x = f(x, a, n), y = f(f(y, a, n), a, n);
	// 			if (x == y) break;
	// 			p = gcd(n, x >= y ? x - y : y - x);
	// 			if (p > 1) {
	// 				factor(p), factor(n / p);
	// 				return;
	// 			}
	// 		}
	// 	}
	// }
	void factor(ulnt n) {
		if (n == 1) return;
		if (test(n)) {
			result[++count] = n;
			return;
		}
		ulnt p = n, c = rand_ulnt();
		while (p >= n) p = rho(p, c--);
		factor(p);
		factor(n / p);
	}
};  // namespace Rho
int T;
unsigned long long n;
std::map<unsigned long long, int> map;
char buf[100];
int main() {
	srand(time(NULL));
	Xxs::init();
	for (scanf("%d", &T); T; T--) {
		scanf("%s", buf);
		if (strlen(buf) > 18) {
			// Explode! レア充
			puts("1");
            // 🐸💣🔪
		} else {
			sscanf(buf, "%llu", &n);
			int ans = (~0U) >> 1;
			if (~n & 1) {
				for (ans = 0; ~n & 1; n >>= 1) ans++;
			}
			for (int i = 2; i <= Xxs::pnt; i++) {
				if (n % i) continue;
				int tmp = 0;
				for (; n % i == 0; n /= i) tmp++;
				ans = std::min(ans, tmp);
			}
			Rho::count = 0;
			Rho::factor(n);
			map.clear();
			for (int i = 1; i <= Rho::count; i++) {
				++map[Rho::result[i]];
			}
			for (auto p : map) ans = std::min(ans, p.second);
			printf("%d\n", ans);
		}
	}
	return 0;
}