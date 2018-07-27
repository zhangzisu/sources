#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 100010
typedef long long lnt;
int n, m, a[MAXN];
std::vector<std::pair<int, int>> fields[MAXN];
lnt max[MAXN], tag[MAXN];
inline void pushDown(int n) {
    if (tag[n]) {
        tag[n << 1] += tag[n];
        tag[n << 1 | 1] += tag[n];
        max[n << 1] += tag[n];
        max[n << 1 | 1] += tag[n];
        tag[n] = 0;
    }
}
void _modify(int n, int l, int r, int p, lnt v) {
    if (l == r) return max[n] = v, void();
    int mid = (l + r) >> 1;
    pushDown(n);
    p <= mid ? _modify(n << 1, l, mid, p, v) : _modify(n << 1 | 1, mid + 1, r, p, v);
    max[n] = std::max(max[n << 1], max[n << 1 | 1]);
}
lnt _query(int n, int l, int r, int p) {
    if (l == r) return max[p];
    int mid = (l + r) >> 1;
    pushDown(n);
    return p <= mid ? _query(n << 1, l, mid, p) : _query(n << 1 | 1, mid + 1, r, p);
}
void _add(int n, int l, int r, int L, int R, lnt v) {
    if (l == L && r == R) return max[n] += v, tag[n] += v, void();
    int mid = (l + r) >> 1;
    if (R <= mid)
        _add(n << 1, l, mid, L, R, v);
    else if (L > mid)
        _add(n << 1 | 1, mid + 1, r, L, R, v);
    else
        _add(n << 1, l, mid, L, mid, v), _add(n << 1 | 1, mid + 1, r, mid + 1, R, v);
    max[n] = std::max(max[n << 1], max[n << 1 | 1]);
}
int offset = 1;
inline void modify(int p, lnt v) {
    // printf("MODIFY %d %lld\n", p, v);
    return _modify(1, 1, n + offset, p + offset, v);
}
inline lnt query(int p) {
    // printf("QUERY %d\n", p);
    return _query(1, 1, n + offset, p + offset);
}
inline void add(int l, int r, lnt v) {
    // printf("ADD %d %d %lld\n", l, r, v);
    return _add(1, 1, n + offset, l + offset, r + offset, v);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1, l, r, p; i <= m; i++) {
        scanf("%d%d%d", &l, &r, &p);
        fields[r].emplace_back(l, p);
    }
    for (int i = 0; i < n; i++) {
        lnt prv = max[1];
        add(0, n, -a[i + 1]);
        for (auto field : fields[i + 1]) {
            add(0, field.first - 1, field.second);
        }
        lnt val = query(i + 1);
        if (val < prv) modify(i + 1, prv);
        for (int i = 0; i <= n; i++) printf("%lld ", query(i));
        puts("");
    }
    printf("%lld\n", max[1]);
    return 0;
}