#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}

int val[MAXN << 2], max[MAXN << 2], L[MAXN << 2], R[MAXN << 2], root, cnt;
int n = $(), m = $(), p = $(), h[MAXN];
int get(int n, int l, int r, int v) {
    if (l == r) return l + std::max(max[n], v);
    int mid = (l + r) >> 1;
    if (max[R[n]] >= v)
        return std::min(val[n], get(R[n], mid + 1, r, v));
    else
        return std::min(get(L[n], l, mid, v), mid + 1 + v);
}
inline void pushUp(int n, int l, int r, int mid) {
    val[n] = get(L[n], l, mid, max[R[n]]);
    max[n] = std::max(max[L[n]], max[R[n]]);
}
void build(int &n, int l, int r) {
    n = ++cnt;
    if (l == r) {
        val[n] = h[l];
        max[n] = h[l] - l;
        return;
    }
    int mid = (l + r) >> 1;
    build(L[n], l, mid);
    build(R[n], mid + 1, r);
    pushUp(n, l, r, mid);
}
void modify(int n, int l, int r, int p, int v) {
    if (l == r) return max[n] = v, val[n] = v + l, void();
    int mid = (l + r) >> 1;
    if (p <= mid)
        modify(L[n], l, mid, p, v);
    else
        modify(R[n], mid + 1, r, p, v);
    pushUp(n, l, r, mid);
}
int main() {
    for (int i = 1; i <= n; i++) h[i] = h[i + n] = $();
    build(root, 1, n << 1);
    int lastans = val[root] + n - 1;
    printf("%d\n", lastans);
    while (m--) {
        int x = $() ^ (lastans * p), y = $() ^ (lastans * p);
        modify(root, 1, n << 1, x, y - x);
        modify(root, 1, n << 1, x + n, y - n - x);
        printf("%d\n", lastans = val[root] + n - 1);
    }
    return 0;
}