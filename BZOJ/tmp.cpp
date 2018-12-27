#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
#define G 3
inline void trim(int &x) { (x >= MOD) && (x -= MOD); }
inline void up(int &x, int y) { trim(x += y); }
inline int fuck(int x, int y) {
	int z = 1;
	for (; y; y >>= 1) {
		if (y & 1) z = 1LL * z * x % MOD;
		x = 1LL * x * x % MOD;
	}
	return z;
}
inline void NTT(int *a, int n) {
	for (int i = 1, j = 0; i < n - 1; i++) {
		for (int t = n; ~j & t; j ^= t) t >>= 1;
		if (i < j) std::swap(a[i], a[j]);
	}
	for (int i = 1; i < n; i <<= 1) {
		int t = i << 1, wn = fuck(G, (MOD - 1) / t);
		for (int j = 0; j < n; j += t) {
			for (int k = 0, w = 1; k < i; k++, w = 1LL * w * wn % MOD) {
				int x = a[j + k], y = 1LL * w * a[j + k + i] % MOD;
				trim(a[j + k] = x + y);
				trim(a[j + k + i] = x - y + MOD);
			}
		}
	}
}
const int N = 1 << 23;
int f[N], g[N];
int main() {
	f[0]=f[1]=g[0]=g[1]=1;
    // fprintf(stderr, "Input done\n");
	NTT(f, N);
    // fprintf(stderr, "NTT #1 done\n");
	NTT(g, N);
    // fprintf(stderr, "NTT #2 done\n");
	for (int i = 0; i < N; i++) f[i] = 1LL * f[i] * g[i] % MOD;
	NTT(f, N);
    // fprintf(stderr, "NTT #3 done\n");
	std::reverse(f + 1, f + N);
	for (int i = 0, inv = fuck(N, MOD - 2); i < N; i++) f[i] = 1LL * f[i] * inv % MOD;
	for (int i = 0; i <= 20; i++) printf("%d ", f[i]);
	puts("");
	return 0;
}