#include <assert.h>
typedef unsigned int u32;
typedef unsigned long long u64;
struct mont {
	static const int l = 32;
	u32 mod, inv, r2;
	// N -> mod, N' -> inv, R^2 -> r2
	mont(u32 n) : mod(n) {
		assert(mod & 1);
		int i;
		for (inv = i = 1; i <= l; ++i) inv = inv * inv * mod;
		r2 = -u64(mod) % mod;
	}
	u32 reduce(u64 x) {
		u32 a = (u64(u32(x) * inv) * mod) >> l;
		u32 b = x >> l;
		return a < b ? a + mod - b : a - b;
	}
	u32 init(u32 x) { return reduce(u64(x) * r2); }
	u32 mul(u32 a, u32 b) { return reduce(u64(a) * b); }
} mod(998244353);
int main() {
	assert(mod.reduce(mod.mul(mod.init(233), mod.init(666))) == 233 * 666);
}
