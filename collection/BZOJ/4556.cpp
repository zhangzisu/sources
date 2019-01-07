#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 100010
int sa[MAXN], rank[MAXN], height[MAXN], h[MAXN], tmp[MAXN], n, m, k;
char buf[MAXN];
inline int cmp(int x, int y) {
    if (rank[x] != rank[y]) return rank[x] < rank[y];
    int rx = x + k <= n ? rank[x + k] : -1;
    int ry = y + k <= n ? rank[y + k] : -1;
    return rx < ry;
}
inline void build_sa() {
    for (int i = 1; i <= n; i++) sa[i] = i, rank[i] = buf[i];
    k = 0;
    std::sort(sa + 1, sa + n + 1, cmp);
    tmp[sa[1]] = 1;
    for (int i = 2; i <= n; i++) tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
    for (int i = 1; i <= n; i++) rank[i] = tmp[i];
    for (k = 1; k <= n; k <<= 1) {
        std::sort(sa + 1, sa + n + 1, cmp);
        tmp[sa[1]] = 1;
        for (int i = 2; i <= n; i++) tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        for (int i = 1; i <= n; i++) rank[i] = tmp[i];
    }
    for (int i = 1; i <= n; i++) rank[sa[i]] = i;
    for (int i = 1, j, k = 0; i <= n; h[rank[i++]] = k)
        for (k ? k-- : 0, j = sa[rank[i] - 1]; buf[i + k] == buf[j + k]; k++)
            ;
    for (int i = 1; i <= n; i++) height[i] = h[rank[i]];
}
int _min[MAXN][20], log_2[MAXN];
inline void build_st() {
    log_2[0] = -1;
    for (int i = 1; i <= n; i++) log_2[i] = log_2[i >> 1] + 1;
    for (int i = 1; i <= n; i++) _min[i][0] = h[i];
    for (int d = 1; d < 20; d++) {
        int len = 1 << d;
        for (int i = 1; i <= n; i++) {
            if (i + len - 1 > n) break;
            _min[i][d] = std::min(_min[i][d - 1], _min[i + (1 << (d - 1))][d - 1]);
        }
    }
}
inline int min(int l, int r) {
    int log_2 = ::log_2[r - l + 1];
    int len = 1 << log_2;
    int res = std::min(_min[l][log_2], _min[r - len + 1][log_2]);
    return res;
}
#define MAXS 5000010
int root[MAXN], L[MAXS], R[MAXS], sum[MAXS], tot = 0;
void copy(int &n, int N) {
    n = ++tot;
    L[n] = L[N], R[n] = R[N], sum[n] = sum[N];
}
void insert(int &n, int N, int l, int r, int p) {
    copy(n, N);
    sum[n]++;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (p <= mid) return insert(L[n], L[N], l, mid, p);
    return insert(R[n], R[N], mid + 1, r, p);
}
int query(int n, int N, int l, int r, int _l, int _r) {
    if (l == _l && r == _r) return sum[n] - sum[N];
    int mid = (l + r) >> 1;
    if (_r <= mid) return query(L[n], L[N], l, mid, _l, _r);
    if (_l > mid) return query(R[n], R[N], mid + 1, r, _l, _r);
    return query(L[n], L[N], l, mid, _l, mid) + query(R[n], R[N], mid + 1, r, mid + 1, _r);
}
int a, b, c, d;
inline bool check(int val) {
    int l, r, L = rank[c], R = rank[c];
    l = 1, r = rank[c] - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (min(mid + 1, rank[c]) >= val)
            L = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    l = rank[c] + 1, r = n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (min(rank[c] + 1, mid) >= val)
            R = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    return query(root[b - val + 1], root[a - 1], 1, n, L, R);
}
int main() {
    scanf("%d%d%s", &n, &m, buf + 1);
    build_sa();
    build_st();
    for (int i = 1; i <= n; i++) insert(root[i], root[i - 1], 1, n, rank[i]);
    while (m--) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        int len = std::min(b - a + 1, d - c + 1);
        int l = 1, r = len, ans = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid))
                l = mid + 1, ans = mid;
            else
                r = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}