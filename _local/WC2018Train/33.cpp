#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
struct MathUtils {
	int MOD;
	inline MathUtils(int MOD) : MOD(MOD) {}
	inline void trim(int &x) const {
		if (x >= MOD) x -= MOD;
	}
	inline void up(int &x, int y) const { trim(x += y); }
	inline int pow(int x, int y) const {
		int z = 1;
		for (; y; y >>= 1) {
			if (y & 1) z = 1LL * z * x % MOD;
			x = 1LL * x * x % MOD;
		}
		return z;
	}
};
struct PolyUtils : public MathUtils {
	int G;
	inline PolyUtils(int MOD, int G) : MathUtils(MOD), G(G) {}
	inline void NTT(int *a, int n) const {
		for (int i = 1, j = 0; i < n - 1; i++) {
			for (int t = n; ~j & t; j ^= t) t >>= 1;
			if (i < j) std::swap(a[i], a[j]);
		}
		for (int i = 1; i < n; i <<= 1) {
			int t = i << 1, wn = pow(G, (MOD - 1) / t);
			for (int j = 0; j < n; j += t) {
				for (int k = 0, w = 1; k < i; k++, w = 1LL * w * wn % MOD) {
					int x = a[j + k], y = 1LL * w * a[j + k + i] % MOD;
					trim(a[j + k] = x + y);
					trim(a[j + k + i] = x - y + MOD);
				}
			}
		}
	}
	inline void IDFT(int *a, int n) const {
		NTT(a, n);
		std::reverse(a + 1, a + n);
		for (int i = 0, inv = pow(n, MOD - 2); i < n; i++) a[i] = 1LL * a[i] * inv % MOD;
	}
} common(1004535809, 3);
inline int getG(int p) {
	MathUtils math(p);
	if (p == 2) return 1;
	std::vector<int> fac;
	for (int i = 2; i < p - 1; i++) {
		if ((p - 1) % i) continue;
		fac.push_back(i);
	}
	for (int i = 2;; i++) {
		if (std::all_of(fac.begin(), fac.end(), [i, p, math](int v) { return math.pow(i, v) != 1; })) return i;
	}
}
const int N = 14;
const int len = 1 << N;
int n, m, x, s, a[len], id[len], f[len], h[len];
int main() {
	scanf("%d%d%d%d", &n, &m, &x, &s);
	for (int g = getG(m), i = 0, v = 1; i < m - 1; i++, v = 1LL * v * g % m) id[v] = i;
	for (int x; s; s--) scanf("%d", &x) && x && (f[id[x]] = 1);
	memcpy(h, f, sizeof(h));
	for (m--, n--; n; n >>= 1) {
		common.NTT(f, len);
		if (n & 1) {
			common.NTT(h, len);
			for (int i = 0; i < len; i++) h[i] = 1LL * h[i] * f[i] % common.MOD;
			common.IDFT(h, len);
			for (int i = m; i < m + m; i++) common.up(h[i - m], h[i]), h[i] = 0;
		}
		for (int i = 0; i < len; i++) f[i] = 1LL * f[i] * f[i] % common.MOD;
		common.IDFT(f, len);
		for (int i = m; i < m + m; i++) common.up(f[i - m], f[i]), f[i] = 0;
	}
	printf("%d\n", h[id[x]]);
	return 0;
}
