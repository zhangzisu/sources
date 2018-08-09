#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 400010
#define MAXM 5000010
int n, m, q, val[MAXN], all;
int min[2][MAXN << 2];
inline void modify(int id, int n, int l, int r, int p, int v) {
    if (l == r) return min[id][n] = v, void();
    int mid = (l + r) >> 1;
    p <= mid ? modify(id, n << 1, l, mid, p, v) : modify(id, n << 1 | 1, mid + 1, r, p, v);
    min[id][n] = std::min(min[id][n << 1], min[id][n << 1 | 1]);
}
inline int query(int id, int n, int l, int r, int L, int R) {
    if (l == L && r == R) return min[id][n];
    int mid = (l + r) >> 1;
    if (R <= mid) return query(id, n << 1, l, mid, L, R);
    if (L > mid) return query(id, n << 1 | 1, mid + 1, r, L, R);
    return std::min(query(id, n << 1, l, mid, L, mid), query(id, n << 1 | 1, mid + 1, r, mid + 1, R));
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &val[i]), modify(1, 1, 1, n, i, val[i]);
    for (int i = 1; i < n; i++) scanf("%*d%*d");
    for (int op, x, y; q; q--) {
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) {
            modify(1, 1, 1, n, x, y);
        } else {
            if (x > y) std::swap(x, y);
            printf("%d\n", query(1, 1, 1, n, x, y));
        }
    }
    return 0;
}