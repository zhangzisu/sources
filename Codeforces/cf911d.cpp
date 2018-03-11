#include <iostream>
#define MAXN 1501
int n, m, ans, a[MAXN], bit[MAXN];
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int v) {
    for (; x <= n; x += lowbit(x)) bit[x] += v;
}
inline int qry(int x) {
    register int ret = 0;
    for (; x; x -= lowbit(x)) ret += bit[x];
    return ret;
}
int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        ans += qry(n) - qry(a[i]);
        add(a[i], 1);
    }
    std::cin >> m;
    ans = ans & 1;
    while (m--) {
        int l, r;
        std::cin >> l >> r;
        if (((r - l + 1) >> 1) & 1) ans = !ans;
        puts(ans ? "odd" : "even");
    }
    return 0;
}