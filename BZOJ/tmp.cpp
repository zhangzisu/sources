#include <algorithm>
#include <cctype>
#include <cstdio>
#define lc (x << 1)
#define rc (x << 1 | 1)
#define eps 1e-8
using namespace std;
const int N = 500050;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}
struct node {
    int mn, tag;
} tree[N << 2];
inline void update(int x) { tree[x].mn = min(tree[lc].mn, tree[rc].mn); }
inline void build(int x, int l, int r) {
    if (l == r) {
        tree[x].mn = l;
        return;
    }
    int mid = l + r >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    update(x);
}
inline void pushdown(int x) {
    if (!tree[x].tag) return;
    static int tag;
    tag = tree[x].tag;
    tree[x].tag = 0;
    tree[lc].mn += tag;
    tree[lc].tag += tag;
    tree[rc].mn += tag;
    tree[rc].tag += tag;
}
inline void modify(int x, int l, int r, int l1, int r1, int v) {
    if (l1 <= l && r1 >= r) {
        tree[x].mn += v;
        tree[x].tag += v;
        return;
    }
    int mid = l + r >> 1;
    pushdown(x);
    if (l1 <= mid) modify(lc, l, mid, l1, r1, v);
    if (r1 > mid) modify(rc, mid + 1, r, l1, r1, v);
    update(x);
}
inline int query(int x, int l, int r, int p) {
    if (l == r) return tree[x].mn >= p ? l : l + 1;
    int mid = l + r >> 1;
    pushdown(x);
    if (p <= tree[rc].mn)
        return query(lc, l, mid, p);
    else
        return query(rc, mid + 1, r, p);
}
inline bool cmp(const int &a, const int &b) { return a > b; }
int n, d[N], size[N], cnt[N], fa[N], ans[N];
double k;
int main() {
    n = read();
    scanf("%lf", &k);
    for (int i = n; i; --i) d[i] = read(), fa[i] = i / k + eps, ++size[i], size[fa[i]] += size[i];
    sort(d + 1, d + n + 1, cmp);
    build(1, 1, n);
    for (int i = n - 1; i; --i)
        if (d[i] == d[i + 1]) cnt[i] = cnt[i + 1] + 1;
    for (int i = 1; i <= n; ++i) {
        if (fa[i] && fa[i - 1] != fa[i]) {
            modify(1, 1, n, ans[fa[i]], n, size[fa[i]] - 1);
            printf("MDF %d %d %d\n", ans[fa[i]], n, size[fa[i]] - 1);
        }
        int x = query(1, 1, n, size[i]);
        printf("D! %d\n", x);
        x += cnt[x];
        ++cnt[x];
        x -= (cnt[x] - 1);
        ans[i] = x;
        modify(1, 1, n, x, n, -size[i]);
        printf("MDF %d %d %d\n", x, n, -size[i]);
    }
    for (int i = 1; i <= n; ++i) printf("%d ", d[ans[i]]);
    return 0;
}