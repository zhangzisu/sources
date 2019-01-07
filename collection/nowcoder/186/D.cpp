#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MOD 998244353
#define MAXN 2048
#define G 3
#define fucker 10001
#define len 32768
inline int fuck(int x, int p) {
	int y = 1;
	while (p) {
		if (p & 1) y = 1LL * y * x % MOD;
		x = 1LL * x * x % MOD;
		p >>= 1;
	}
	return y;
}
int _t[len], _w[len], _in;
inline void pre() {
	for (int i = 1, j = 0; i < len - 1; i++) {
		for (int t = len; ~j & t; j ^= t) t >>= 1;
		_t[i] = j;
	}
	for (int i = 1; i < len; i <<= 1) {
		int t = i << 1, wn = fuck(G, (MOD - 1) / t);
		_w[i] = wn;
	}
	_in = fuck(len, MOD - 2);
}
inline int add(int x, int y) {
	return x + y >= MOD ? x + y - MOD : x + y;
}
int A[len], B[len], cur = 0;
int m, q, f[fucker], g[fucker], a, b;
int main() {
	scanf("%d", &m);
	pre();
	scanf("%d%d", &a, &b);
	for (int i = 0; i < fucker; i++)
		f[i] = (1LL * a * i % MOD * i % MOD + 1LL * b * i % MOD + 1) % MOD;
	for (int x = 2; x <= m; x++) {
		scanf("%d%d", &a, &b);
		for (int i = 0; i < fucker; i++)
			g[i] = (1LL * a * i % MOD * i % MOD + 1LL * b * i % MOD + 1) % MOD;
		memcpy(A, f, sizeof(int) * fucker);
		memcpy(B, g, sizeof(int) * fucker);
		memset(A + fucker, 0, sizeof(int) * 22767);
		memset(B + fucker, 0, sizeof(int) * 22767);
		for (int i = 1; i < len - 1; i++)
			if (i < _t[i]) std::swap(A[i], A[_t[i]]), std::swap(B[i], B[_t[i]]);
		for (int i = 1; i < len; i <<= 1) {
			register int t = i << 1, wn = _w[i];
			for (register int j = 0; j < len; j += t) {
				for (register int k = 0, w = 1, x, y; k < i; k++, w = 1LL * w * wn % MOD) {
					x = A[j + k], y = 1LL * w * A[j + k + i] % MOD;
					A[j + k] = add(x, y);
					A[j + k + i] = add(x, MOD - y);
					x = B[j + k], y = 1LL * w * B[j + k + i] % MOD;
					B[j + k] = add(x, y);
					B[j + k + i] = add(x, MOD - y);
				}
			}
		}
		for (int i = 0; i < len; i++) A[i] = 1LL * A[i] * B[i] % MOD;
		for (int i = 1; i < len - 1; i++)
			if (i < _t[i]) std::swap(A[i], A[_t[i]]);
		for (int i = 1; i < len; i <<= 1) {
			register int t = i << 1, wn = _w[i];
			for (register int j = 0; j < len; j += t) {
				for (register int k = 0, w = 1; k < i; k++, w = 1LL * w * wn % MOD) {
					int x = A[j + k], y = 1LL * w * A[j + k + i] % MOD;
					A[j + k] = add(x, y);
					A[j + k + i] = add(x, MOD - y);
				}
			}
		}
		std::reverse(A + 1, A + len);
		for (int i = 0; i < fucker; i++) f[i] = 1LL * A[i] * _in % MOD;
	}
	scanf("%d", &q);
	for (int n; q; q--) {
		scanf("%d", &n);
		printf("%d\n", f[n]);
	}
	return 0;
}