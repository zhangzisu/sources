#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline long long $() {
    register long long x = 0, f = 0;
    register char ch = gc();
    while (!isdigit(ch) && (ch ^ 45)) ch = gc();
    if (!(ch ^ 45)) ch = gc(), f = 1;
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return f ? -x : x;
}
#define G 3
#define MOD 998244353
#define MAXN 4000010
inline int fuck(register int x, register int p) {
    register int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline void down(int &x, int y) {
    if ((x -= y) < 0) x += MOD;
}
int rinv[MAXN], fuckers[MAXN];
inline void NTT(int *a, int n, int e) {
    for (register int i = 1, j = 0; i < n - 1; i++) {
        for (register int t = n; ~j & t; j ^= t) t >>= 1;
        if (i < j) std::swap(a[i], a[j]);
    }
    for (register int k = 1, p = 0; k < n; k <<= 1) {
        register int t = k << 1, fucker = fuckers[p++];
        for (register int i = 0; i < n; i += t) {
            for (register int j = 0, fucked = 1; j < k; j++, fucked = 1LL * fucked * fucker % MOD) {
                register int x = a[i + j], y = 1LL * fucked * a[i + j + k] % MOD;
                a[i + j] = (x + y) % MOD;
                a[i + j + k] = (x - y + MOD) % MOD;
            }
        }
    }
    if (e) {
        std::reverse(a + 1, a + n);
        for (register int i = 0, fucker = rinv[n]; i < n; i++)
            a[i] = 1LL * a[i] * fucker % MOD;
    }
}
int pool[MAXN], pnt = 0, s[MAXN], e[MAXN], tmp1[MAXN], tmp2[MAXN];
int n, m, k, c, ans, a[MAXN], b[MAXN], frc[MAXN], inv[MAXN];
inline int C(int n, int m) { return n >= m ? 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD : 0; }
inline int NTT(int *a, int n, int *b, int m) {
    int len = n + m - 1, N = 1;
    while (N <= len) N <<= 1;
    memset(tmp1, 0, sizeof(int) * N);
    memcpy(tmp1, a, sizeof(int) * n);
    memset(tmp2, 0, sizeof(int) * N);
    memcpy(tmp2, b, sizeof(int) * m);
    NTT(tmp1, N, 0);
    NTT(tmp2, N, 0);
    for (int i = 0; i < N; i++) tmp1[i] = 1LL * tmp1[i] * tmp2[i] % MOD;
    NTT(tmp1, N, 1);
    return len;
}
std::pair<int, int> NTT(int l, int r) {
    if (l == r) return std::make_pair(s[l], e[l]);
    int mid = (l + r) >> 1;
    auto L = NTT(l, mid);
    auto R = NTT(mid + 1, r);
    int len = NTT(pool + L.first, L.second - L.first + 1, pool + R.first, R.second - R.first + 1);
    memcpy(pool + L.first, tmp1, sizeof(int) * len);
    return std::make_pair(L.first, L.first + len - 1);
}
inline void init() {
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
    rinv[1] = 1;
    for (int i = 2; i < MAXN; i++) rinv[i] = (MOD - (MOD / i)) * rinv[MOD % i] % MOD;
    for (int i = 0; (1 << i) <= MAXN; i++) fuckers[i] = fuck(G, (MOD - 1) / (1 << (i + 1)));
}
int main() {
    freopen("box.in", "r", stdin);
    freopen("box.out", "w", stdout);
    init();
    n = $(), m = $(), k = $();
    for (int i = 1; i <= n; i++) a[i] = $();
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) b[c += a[i] != a[i - 1]]++;
    for (int i = 1; i <= c; i++) {
        s[i] = pnt;
        for (int j = 0; j <= b[i]; j++) pool[pnt++] = 1LL * C(b[i], j) * (j + 1) % MOD;
        e[i] = pnt - 1;
    }
    auto ret = NTT(1, c);
    for (int p = 0; p <= m && p <= k; p++)
        up(ans, 1LL * C(n - p, m - p) * C(n - m, k - p) % MOD * pool[ret.first + p] % MOD);
    printf("%d\n", ans);
    return 0;
}