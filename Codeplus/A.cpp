#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <set>
#include <vector>

#define MOD 1000000007
#define MAXN 1000010
inline int fuck(int x, int p) {
    int y = 1;
    while (p) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return y;
}

int frc[MAXN], inv[MAXN], n, k;
long double frc_f[MAXN];
inline int C(int n, int m) {
    return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD;
}
inline long double CC(int n, int m) {
    return frc_f[n] / frc_f[m] / frc_f[n - m];
}
std::set<std::pair<int, int>> S;
struct point {
    int x, y, mod_val;
    long double real_val;
    inline friend bool operator<(const point &a, const point &b) {
        return a.real_val > b.real_val;
    }
};
std::priority_queue<point> Q;
int main() {
    scanf("%d%d", &n, &k);
    frc_f[0] = frc[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        frc[i] = 1LL * frc[i - 1] * i % MOD;
        frc_f[i] = frc_f[i - 1] * i;
    }
    inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
    if (k == 1) {
        return printf("%d\n", C(n, n >> 1 | 1)), 0;
    }
    int ans = 0;
    Q.push({n, n >> 1 | 1, C(n, n >> 1 | 1), CC(n, n >> 1 | 1)});
    S.insert({n, n >> 1 | 1});
    for (int i = 1; i < k; i++) {
        auto top = Q.top();
        Q.pop();
        (ans += top.mod_val) %= MOD;
        if (top.x && top.y != top.x) {
            if (!S.count({top.x - 1, top.y})) {
                Q.push({top.x - 1, top.y, C(top.x - 1, top.y), CC(top.x - 1, top.y)});
                S.insert({top.x - 1, top.y});
            }
        }
        if (top.y) {
            if (!S.count({top.x, top.y - 1})) {
                Q.push({top.x, top.y - 1, C(top.x, top.y - 1), CC(top.x, top.y - 1)});
                S.insert({top.x, top.y - 1});
            }
        }
        if (top.y != top.x) {
            if (!S.count({top.y, top.y + 1})) {
                Q.push({top.y, top.y + 1, C(top.x, top.y + 1), CC(top.x, top.y + 1)});
                S.insert({top.y, top.y + 1});
            }
        }
    }
    (ans += Q.top().mod_val) %= MOD;
    printf("%d\n", ans);
    return 0;
}