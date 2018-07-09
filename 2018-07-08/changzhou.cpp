#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int MAXN = 1 << 18;
#define MOD 1000000007

inline int fuck(int x, int p) {
    int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}

const int inv2 = fuck(2, MOD - 2);

inline void FWT(int *a, int n) {
    for (int d = 1; d < n; d <<= 1) {
        for (int i = 0; i < n; i += d << 1) {
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = (x + y) % MOD;
                a[i + j + d] = ((x - y) % MOD + MOD) % MOD;
            }
        }
    }
}

inline void UFWT(int *a, int n) {
    for (int d = 1; d < n; d <<= 1) {
        for (int i = 0; i < n; i += d << 1) {
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = (x + y) % MOD;
                a[i + j + d] = ((x - y) % MOD + MOD) % MOD;
                a[i + j] = 1LL * a[i + j] * inv2 % MOD;
                a[i + j + d] = 1LL * a[i + j + d] * inv2 % MOD;
            }
        }
    }
}

int n, a[MAXN], b[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) scanf("%d", &b[i]);
    FWT(a, n);
    FWT(b, n);
    for (int i = 0; i < n; i++) b[i] = 1LL * b[i] * fuck(a[i], MOD - 2) % MOD;
    UFWT(b, n);
    for (int i = 0; i < n; i++) printf("%d\n", b[i]);
    return 0;
}