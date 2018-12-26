#include<bits/stdc++.h>
#define MAXN 100010
const int N = 100000;
int n, k, a[MAXN], level[MAXN], pre[MAXN], suf[MAXN], id[MAXN];
inline int lowbit(int x) { return x & -x; }
inline void mdf(int v, int val) {
    for (int x = v; x <= N; x += lowbit(x)) pre[x] = std::max(pre[x], val);
    for (int x = v; x >= 1; x -= lowbit(x)) suf[x] = std::max(suf[x], val);
}
inline int qry(int v) {
    int ret = 0;
    for (int x = v + k + 1; x <= N; x += lowbit(x)) ret = std::max(ret, suf[x]);
    for (int x = v - k - 1; x >= 1; x -= lowbit(x)) ret = std::max(ret, pre[x]);
    return ret;
}
int main() {
    n = io.getint(), k = io.getint();
    for (int i = 1; i <= n; i++) mdf(a[i], level[i] = qry(a[id[i] = i] = io.getint()) + 1);
    std::sort(id + 1, id + n + 1, [](int x, int y) { return level[x] != level[y] ? level[x] < level[y] : a[x] < a[y]; });
    for (int i = 1; i <= n; i++) io.putint(a[id[i]]), io.putchar(i == n ? 10 : 32);
    return 0;
}