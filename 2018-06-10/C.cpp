#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 500010
#define MOD 998244353
#define G 3
inline int fuck(int x, int p) {
    int y = 1;
    while (p) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return y;
}
inline void NTT(int *a, int n, int e) {
    for (int i = 1, j = 0; i < n - 1; i++) {
        for (int t = n; ~j & t; j ^= t) t >>= 1;
        if (i < j) std::swap(a[i], a[j]);
    }
    for (int k = 1; k < n; k <<= 1) {
        int t = k << 1, wn = fuck(G, (MOD - 1) / t);
        for (int i = 0; i < n; i += t) {
            for (int j = 0, w = 1; j < k; j++, w = 1LL * w * wn % MOD) {
                int x = a[i + j], y = 1LL * w * a[i + j + k] % MOD;
                a[i + j] = (x + y) % MOD;
                a[i + j + k] = (x - y + MOD) % MOD;
            }
        }
    }
    if (e) {
        std::reverse(a + 1, a + n);
        for (int i = 0, w = fuck(n, MOD - 2); i < n; i++) a[i] = 1LL * a[i] * w % MOD;
    }
}

int A[MAXN], B[MAXN];
inline void mul(int *a, int *b, int len) {
    int t = 1;
    while (t < len * 2) t <<= 1;
    memset(A, 0, sizeof(int) * t);
    memset(B, 0, sizeof(int) * t);
    memcpy(A, a, sizeof(int) * len);
    memcpy(B, b, sizeof(int) * len);
    NTT(A, t, 0);
    NTT(B, t, 0);
    for (int i = 0; i < t; i++) A[i] = 1LL * A[i] * B[i] % MOD;
    NTT(A, t, 1);
    memcpy(a, A, sizeof(int) * len);
}
int n, t0, t1, frc[MAXN], inv[MAXN];
char buf0[MAXN], buf1[MAXN];
int a[MAXN], b[MAXN];
int main() {
    gets(buf0 + 1);
    gets(buf1 + 1);
    n = strlen(buf0 + 1);
    for (int i = 1; i <= n; i++) {
        t0 += buf0[i] == '1' && buf1[i] == '1';
        t1 += buf0[i] == '1' && buf1[i] == '0';
    }
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
    a[0] = 1;
    int p = t1;
    int len = t0 + 1;
    for (int i = 0; i < len; i++) b[i] = inv[i + 1];
    while (p) {
        if (p & 1) mul(a, b, len);
        mul(b, b, len);
        p >>= 1;
    }
    int ans = 0;
    for (int i = 0; i < len; i++) {
        (ans += 1LL * a[i] * frc[t0] % MOD * frc[t1] % MOD * frc[t0 + t1] % MOD) %= MOD;
    }
    (ans += MOD) %= MOD;
    printf("%d\n", ans);
    return 0;
}