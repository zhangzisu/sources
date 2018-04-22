#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 500010
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
int n = $(), a = $(), b = $(), c = $();
struct node {
    int a, b, c;
} d[MAXN];
long long ans = 0;
int mxb[MAXN], mxc[MAXN], ltb, ltc;
long long sum[MAXN << 2], max[MAXN << 2], tag[MAXN << 2];
inline void pushUp(int n) {
    sum[n] = sum[n << 1] + sum[n << 1 | 1];
    max[n] = std::max(max[n << 1], max[n << 1 | 1]);
}
inline void pushDown(int n, int l, int r) {
    int mid = (l + r) >> 1;
    if (!tag[n]) return;
    tag[n << 1] = tag[n << 1 | 1] = max[n << 1] = max[n << 1 | 1] = tag[n];
    sum[n << 1] = 1LL * (mid - l + 1) * tag[n];
    sum[n << 1 | 1] = 1LL * (r - mid) * tag[n];
    tag[n] = 0;
}
int qmax(int n, int l, int r, int p) {
    if (l == r) return max[n];
    int mid = (l + r) >> 1;
    pushDown(n, l, r);
    if (p <= mid)
        return qmax(n << 1, l, mid, p);
    else
        return qmax(n << 1 | 1, mid + 1, r, p);
}
int qsum(int n, int l, int r, int L, int R) {
    if (l == L && r == R) return sum[n];
    int mid = (l + r) >> 1;
    pushDown(n, l, r);
    if (R <= mid) return qsum(n << 1, l, mid, L, R);
    if (L > mid) return qsum(n << 1 | 1, mid + 1, r, L, R);
    return qsum(n << 1, l, mid, L, mid) + qsum(n << 1 | 1, mid + 1, r, mid + 1, R);
}
void set(int n, int l, int r, int L, int R, int v) {
    if (l == L && r == R) {
        sum[n] = 1LL * (r - l + 1) * v;
        max[n] = tag[n] = v;
        return;
    }
    int mid = (l + r) >> 1;
    pushDown(n, l, r);
    if (R <= mid)
        set(n << 1, l, mid, L, R, v);
    else if (L > mid)
        set(n << 1 | 1, mid + 1, r, L, R, v);
    else
        set(n << 1, l, mid, L, mid, v), set(n << 1 | 1, mid + 1, r, mid + 1, R, v);
    pushUp(n);
}
int find(int n, int l, int r, int v) {
    if (max[n] < v) return 0;
    if (l == r) return r;
    int mid = (l + r) >> 1;
    pushDown(n, l, r);
    if (max[n << 1 | 1] >= v) return find(n << 1 | 1, mid + 1, r, v);
    return find(n << 1, l, mid, v);
}
inline void add(int x) {
    int val = qmax(1, 1, b, d[x].b);
    if (val >= d[x].c) return;
    int left = find(1, 1, b, d[x].c);
    if (!left) left = 1;
    set(1, 1, b, left, d[x].b, d[x].c);
    // printf("SETVAL %d - %d : %d\n", left, d[x].b, d[x].c);
}
inline long long calc() {
    long long val = qmax(1, 1, b, ltb);
    long long all = (b - ltb + 1) * (c - ltc + 1);
    if (val < ltc) return all;
    int right = find(1, 1, b, ltc);
    return all - qsum(1, 1, b, ltb, right) + 1LL * (right - ltb + 1) * (ltc - 1);
}
int main() {
    for (int i = 1; i <= n; i++) d[i].a = $(), d[i].b = $(), d[i].c = $();
    std::sort(d + 1, d + n + 1, [](node a, node b) { return a.a < b.a; });
    for (int i = a; i >= 1; i--) {
        mxb[i] = std::max(mxb[i + 1], d[i].b);
        mxc[i] = std::max(mxc[i + 1], d[i].c);
    }

    for (int i = 1, j = 1; i <= a; i++) {
        while (j <= n && d[j].a < i) add(j++);
        ltb = mxb[j] + 1;
        ltc = mxc[j] + 1;
        printf("Fixed a = %d, lmt b %d, lmt c %d\n", i, ltb, ltc);
        ans += calc();
        printf("%lld\n", ans);
    }
    printf("%lld\n", ans);
    return 0;
}