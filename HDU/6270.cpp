#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MOD 998244353
#define MAXN 1000010
const int G = 3;
int frc[MAXN], inv[MAXN];
inline int fuck(int x, int p) {
    register int y = 1;
    while (p) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return y;
}
inline int C(int n, int m) {
    return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD;
}
inline void NTT(int *a, int N, int e) {
    for (int i = 1, j = 0; i < N - 1; i++) {
        for (int t = N; ~j & t; j ^= t) t >>= 1;
        if (i < j) std::swap(a[i], a[j]);
    }
    for (int i = 1; i < N; i <<= 1) {
        int t = i << 1, wn = fuck(G, (MOD - 1) / t);
        for (int j = 0; j < N; j += t) {
            for (int k = 0, w = 1; k < i; k++, w = 1LL * w * wn % MOD) {
                int x = a[j + k], y = 1LL * w * a[j + k + i] % MOD;
                a[j + k] = (x + y) % MOD;
                a[j + k + i] = (x - y + MOD) % MOD;
            }
        }
    }
    if (e) {
        std::reverse(a + 1, a + N);
        for (int i = 0, j = fuck(N, MOD - 2); i < N; i++) a[i] = 1LL * a[i] * j % MOD;
    }
}
int A[MAXN], B[MAXN], cur = 0;
inline void FUCK(int *a, int *b, int aL, int bL) {
    int len = 1;
    while (len < (aL + bL)) len <<= 1;
    std::fill(A, A + len, 0);
    std::fill(B, B + len, 0);
    for (int i = 0; i < aL; i++) A[i] = a[i];
    for (int i = 0; i < bL; i++) B[i] = b[i];
    NTT(A, len, 0), NTT(B, len, 0);
    for (int i = 0; i < len; i++) A[i] = 1LL * A[i] * B[i] % MOD;
    NTT(A, len, 1);
    for (int i = 0; i < aL + bL; i++) a[i] = A[i];
}
int n, a[MAXN], b[MAXN], c[MAXN], V[MAXN];
std::pair<int, int> boom(int l, int r) {
    if (l == r) {
        int ret = cur;
        for (int i = 0; i <= c[l]; i++)
            V[cur++] = 1LL * C(a[l], i) * C(b[l], i) % MOD * frc[i] % MOD;
        return {ret, c[l] + 1};
    }
    int mid = (l + r) >> 1;
    auto L = boom(l, mid);
    auto R = boom(mid + 1, r);
    FUCK(V + L.first, V + R.first, L.second, R.second);
    return {L.first, L.second + R.second};
}
int t, g, ans = 0;
int main() {
    scanf("%d", &t);
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
    while (t--) {
        scanf("%d", &n);
        g = ans = cur = 0;
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(c, 0, sizeof(c));
        memset(V, 0, sizeof(V));
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &a[i], &b[i]);
            c[i] = std::min(a[i], b[i]);
            g += a[i];
        }
        auto pos = boom(1, n);
        for (int i = 0; i < pos.second; i++)
            ans = (ans + (i & 1 ? -1LL : 1LL) * (V + pos.first)[i] % MOD * frc[g - i] % MOD) % MOD;
        printf("%d\n", (ans + MOD) % MOD);
    }
    return 0;
}