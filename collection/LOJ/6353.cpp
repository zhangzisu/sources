#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <set>
#define MAXN 1000010
#define MOD 1000000007
struct data {
    int x, y;
    double val;
    inline friend bool operator<(const data &a, const data &b) {
        return a.val < b.val;
    }
};
std::priority_queue<data> Q;
std::set<std::pair<int, int>> S;
int frc[MAXN], inv[MAXN], n, k, ans;
double lg[MAXN];
inline int C(int n, int m) { return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD; }
inline double D(int n, int m) { return lg[n] - lg[m] - lg[n - m]; }
inline int fuck(int x, int p) {
    register int y = 1;
    while (p) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return y;
}
inline void prepare() {
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
    for (int i = 1; i < MAXN; i++) lg[i] = lg[i - 1] + log(i);
}
inline void insert(int x, int y) {
    if (x < 0 || x > n) return;
    if (y < 0 || y > x) return;
    if (S.count({x, y})) return;
    S.insert({x, y});
    Q.push({x, y, D(x, y)});
}
int main() {
    prepare();
    scanf("%d%d", &n, &k);
    insert(n, n >> 1);
    while (k--) {
        auto t = Q.top();
        Q.pop();
        (ans += C(t.x, t.y)) %= MOD;
        insert(t.x, t.y + 1);
        insert(t.x, t.y - 1);
        insert(t.x - 1, t.y);
    }
    printf("%d\n", ans);
    return 0;
}