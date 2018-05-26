#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 200010
int n, m, q, a[MAXN], b[MAXN];
long long min[MAXN << 2], tag[MAXN << 2];
inline void pushDown(int n) {
    if (!tag[n]) return;
    min[n << 1] += tag[n], min[n << 1 | 1] += tag[n];
    tag[n << 1] += tag[n], tag[n << 1 | 1] += tag[n];
    tag[n] = 0;
}
void add(int n, int l, int r, int L, int R, long long v) {
    if (l == L && r == R) return min[n] += v, tag[n] += v, void();
    int mid = (l + r) >> 1;
    pushDown(n);
    if (R <= mid)
        add(n << 1, l, mid, L, R, v);
    else if (L > mid)
        add(n << 1 | 1, mid + 1, r, L, R, v);
    else
        add(n << 1, l, mid, L, mid, v), add(n << 1 | 1, mid + 1, r, mid + 1, R, v);
    min[n] = std::min(min[n << 1], min[n << 1 | 1]);
}
long long query(int n, int l, int r, int L, int R) {
    if (l == L && r == R) return min[n];
    int mid = (l + r) >> 1;
    pushDown(n);
    if (R <= mid) return query(n << 1, l, mid, L, mid);
    if (L > mid) return query(n << 1 | 1, mid + 1, r, mid + 1, R);
    return std::min(query(n << 1, l, mid, L, mid), query(n << 1 | 1, mid + 1, r, mid + 1, R));
}
std::vector<std::pair<int, int>> next[MAXN];
long long ans[MAXN];
int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &a[i], &b[i + 1]);
        add(1, 1, n, i + 1, i + 1, b[i + 1]);
    }
    for (int i = 1, u, v, w; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        next[u].push_back({v, w});
    }
    for (int i = 1; i <= n; i++) {
        for (auto x : next[i]) {
            add(1, 1, n, 1, x.first, x.second);
        }
        ans[i] = a[i] + query(1, 1, n, 1, n);
    }
    memset(tag, 0, sizeof(tag));
    memset(min, 0, sizeof(min));
    for (int i = 1; i <= n; i++) add(1, 1, n, i, i, ans[i]);
    printf("%lld\n", query(1, 1, n, 1, n));
    while (q--) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(1, 1, n, x, x, y - a[x]);
        a[x] = y;
        printf("%lld\n", query(1, 1, n, 1, n));
    }
    return 0;
}