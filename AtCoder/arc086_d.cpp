#include <algorithm>
#include <cstdlib>
#include <iostream>
#define MOD 1000000007
int n, m, q = 0;
long long k, a[210], b[210], c[210];
inline int minpopcount(long long l, long long r) {
    register int ret = 0;
    for (int i = 60; i >= 0; i--)
        if (((l >> i) & 1) == ((r >> i) & 1))
            ret += (l >> i) & 1;
        else {
            ret++;
            break;
        }
    return ret;
}
struct ans {
    long long d[210], r;
    inline friend bool operator<(const ans& a, const ans& b) {
        for (int i = 1; i < n; i++) {
            if (a.d[i] < b.d[i]) return 1;
            if (a.d[i] > b.d[i]) return 0;
        }
        return 0;
    }
    inline friend bool operator==(const ans& a, const ans& b) {
        for (int i = 1; i < n; i++)
            if (a.d[i] != b.d[i]) return 0;
        return 1;
    }
    inline friend bool operator!=(const ans& a, const ans& b) {
        return !(a == b);
    }
} dt[210 * 210];
std::pair<long long, long long> Q[210 * 210];
long long ans = 0;
long long calc() {
    std::sort(Q + 1, Q + q + 1);
    long long ret = 0, l = 0, r = -1;
    for (int i = 1; i <= q; i++) {
        if (Q[i].first > r) {
            ret += r - l + 1;
            l = Q[i].first;
        }
        r = Q[i].second;
    }
    return ret + r - l + 1;
}
int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    for (int k = 0; k <= 60; k++) {
        for (int i = 1; i <= n; i++) b[i] = a[i] & ((1LL << k) - 1);
        std::sort(b + 1, b + n + 1);
        int N = std::unique(b + 1, b + n + 1) - b - 1;
        for (int i = 1; i <= N; i++) {
            if (a[1] < b[i]) continue;
            int P = i == 1 ? 0 : minpopcount(b[i - 1], b[i]);
            for (int j = 1; j <= n; j++) c[j] = (a[j] - b[i]) >> k;
            dt[++m].r = k + P;
            c[0] = 0;
            for (int j = 0; j < n; j++) dt[m].d[j] = c[j + 1] - c[j];
        }
    }
    std::sort(dt + 1, dt + m + 1);
    for (int i = 1; i <= m; i++) {
        if (i != 1 && dt[i] != dt[i - 1]) {
            (ans += calc()) %= MOD;
            q = 0;
        }
        if (dt[i].r <= k) {
            Q[++q] = std::make_pair(std::max(dt[i].d[0] - k + dt[i].r, 0LL),
                                    dt[i].d[0]);
        }
    }
    (ans += calc()) %= MOD;
    std::cout << ans << std::endl;
    return 0;
}