#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
long long n1, n2, n, BIT[MAXN], pos, ans;
std::pair<long long, long long> a[MAXN];
inline long long lowbit(long long x) { return x & -x; }
inline void add(long long p, long long x) {
    for (; p <= n; p += lowbit(p)) BIT[p] += x;
}
inline long long qry(long long p) {
    long long ret = 0;
    for (; p; p -= lowbit(p)) ret += BIT[p];
    return ret;
}
inline long long qry(long long l, long long r) {
    if (l > r) std::swap(l, r);
    return qry(r) - qry(l - 1);
}
inline long long cmp(const std::pair<long long, long long> &a,
                     const std::pair<long long, long long> &b) {
    return a.first > b.first;
}
int main() {
    scanf("%lld%lld", &n1, &n2);
    n = n1 + n2 + 1;
    for (int i = 1; i <= n1; i++) scanf("%lld", &a[n1 - i + 1].first);
    for (int i = 1; i <= n2; i++) scanf("%lld", &a[n1 + i + 1].first);
    a[pos = n1 + 1].first = 0x3F3F3F3F;
    for (int i = 1; i <= n; i++)
        if (i != pos) add(a[i].second = i, 1);
    std::sort(a + 1, a + n + 2, cmp);
    for (int i = 2; i <= n; i++) {
        ans += qry(pos, a[i].second) - 1;
        add(a[i].second, -1);
        pos = a[i].second;
    }
    printf("%lld\n", ans);
    return 0;
}