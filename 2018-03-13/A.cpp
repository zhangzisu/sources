#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 5000010
#define FUCK 500

int n, q, l[MAXN], r[MAXN], id[MAXN];

int m, d[MAXN];
int L[MAXN], R[MAXN], sum[MAXN], root[MAXN], cnt;
inline void insert(int &n, int m, int l, int r, int v) {
    n = ++cnt;
    L[n] = L[m], R[n] = R[m], sum[n] = sum[m] + 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (v <= mid)
        insert(L[n], L[m], l, mid, v);
    else
        insert(R[n], R[m], mid + 1, r, v);
}
inline int query(int n, int l, int r, int _l, int _r) {
    if (!n || _l > _r) return 0;
    if (l == _l && r == _r) return sum[n];
    int mid = (l + r) >> 1;
    if (_r <= mid) return query(L[n], l, mid, _l, _r);
    if (_l > mid) return query(R[n], mid + 1, r, _l, _r);
    return query(L[n], l, mid, _l, mid) + query(R[n], mid + 1, r, mid + 1, _r);
}
std::vector<std::pair<int, int>> V;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &l[i], &r[i]), id[i] = i;
    scanf("%d", &q);
    std::sort(id + 1, id + n + 1, [](int a, int b) { return l[a] < l[b]; });
    V.push_back({0, 0});
    for (int i = 1; i <= n; i++) {
        insert(root[i], root[i - 1], 1, n, r[id[i]]);
        V.push_back({l[id[i]], i});
    }
    std::sort(V.begin(), V.end());
    while (q--) {
        scanf("%d", &m);
        if (m > FUCK) {
            memset(d, 0, sizeof(d));
            for (int i = 1, x; i <= m; i++) scanf("%d", &x), d[x]++;
            for (int i = 1; i <= n; i++) d[i] += d[i - 1];
            int ans = 0;
            for (int i = 1; i <= n; i++) {
                ans += (d[r[i]] - d[l[i] - 1]) & 1;
            }
            printf("%d\n", ans);
        } else {
            for (int i = 1; i <= m; i++) scanf("%d", &d[i]);
            std::sort(d + 1, d + m + 1);
            d[0] = 0, d[m + 1] = n + 1;
            int ans = 0;
            for (int i = 1; i <= m; i++) {
                for (int j = i; j <= m; j += 2) {
                    int l0 = d[i - 1] + 1, l1 = d[i];
                    int r0 = d[j], r1 = d[j + 1] - 1;
                    int pos0 = (--std::lower_bound(V.begin(), V.end(), std::make_pair(l0, 0)))->second;
                    int pos1 = (--std::upper_bound(V.begin(), V.end(), std::make_pair(l1, 0x3F3F3F3F)))->second;
                    ans += query(root[pos1], 1, n, r0, r1) - query(root[pos0], 1, n, r0, r1);
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}