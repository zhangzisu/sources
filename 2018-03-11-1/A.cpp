#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 50010
#define MOD 998244353

int n, m, q, l, r, v;
long long sum[MAXN], k;
std::vector<std::pair<int, int>> V;
int c1[MAXN], id[MAXN];
inline int lowbit(int x) { return x & -x; }
inline void add(int *x, int p, int v) {
    for (; p <= n; p += lowbit(p)) x[p] += v;
}
inline int qry(int *x, int p) {
    int ret = 0;
    for (; p; p -= lowbit(p)) ret += x[p];
    return ret;
}

long long frc[MAXN], inv[MAXN];
inline long long fuck(long long x, int p) {
    long long ret = 1;
    x %= MOD;
    while (p) {
        if (p & 1) ret = ret * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return ret;
}
inline long long C(int n, int m) {
    if (n < m) return 0;
    if (m < 0) return 0;
    return frc[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int main() {
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = inv[i] * i % MOD;

    scanf("%d%d%lld%d", &m, &n, &k, &q);
    for (int i = 2, t; 1LL * i * i <= k && k != 1; i++) {
        if (k % i) continue;
        t = 0;
        while (!(k % i)) t++, k /= i;
        V.push_back({i, t});
    }
    if (k != 1) V.push_back({k, 1});
    assert(m == 1);
    for (int i = 2, x; i <= n; i++) {
        scanf("%d", &x);
        sum[i] = sum[i - 1] + x;
    }
    while (q--) {
        scanf("%d", &l);
        if (l == 1) {
            scanf("%*d%d%*d%d%d", &l, &r, &v);
            if (l > r) std::swap(l, r);
            printf("%lld\n", sum[r] - sum[l]);
            if (v == 1) {
                add(c1, l, 1), add(c1, r + 1, -1);
            } else if (v == 2) {
                add(c1, l, -1), add(c1, r + 1, 1);
            } else if (v == 3) {
                add(id, l, 1), add(id, r + 1, -1);
            } else {
                add(id, l, 1), add(id, r + 1, -1);
                add(c1, l, -1), add(c1, r + 1, 1);
            }
        } else {
            scanf("%*d%d", &l);
            int _c1 = qry(c1, l), _id = qry(id, l);
            long long ret = 1;
            for (auto i : V) {
                long long tmp = 0;
                if (_id) {
                    for (int x = 0; x <= i.second; x++) {
                        if (_c1 <= 0) {
                            (tmp += C(-_c1, x) * C(i.second - x + _id - 1, _id - 1) % MOD * fuck(i.first, i.second - x) * (x & 1 ? -1 : 1) % MOD) %= MOD;
                            (tmp += MOD) %= MOD;
                        } else {
                            (tmp += C(x + _c1 - 1, _c1 - 1) * C(i.second - x + _id - 1, _id - 1) % MOD * fuck(i.first, i.second - x) % MOD) %= MOD;
                        }
                    }
                } else {
                    if (_c1 <= 0) {
                        tmp = C(-_c1, i.second) * (i.second & 1 ? -1 : 1);
                        (tmp += MOD) %= MOD;
                    } else {
                        tmp = C(i.second + _c1 - 1, _c1 - 1) % MOD;
                    }
                }
                ret = ret * tmp % MOD;
            }
            printf("%lld\n", ret);
        }
    }
}