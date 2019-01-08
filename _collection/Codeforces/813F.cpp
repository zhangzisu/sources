#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define MAXN 100010
int n, q, m, ans[MAXN], r[MAXN];
std::map<std::pair<int, int>, int> M;
std::pair<int, int> e[MAXN];
int p[MAXN], dis[MAXN], size[MAXN], stk[MAXN], top;
inline int find(int x) {
    while (x != p[x]) x = p[x];
    return x;
}
inline int color(int x) {
    int ret = 0;
    while (x != p[x]) ret ^= dis[x], x = p[x];
    return ret;
}
inline void merge(int u, int v, int f) {
    if (size[u] > size[v]) std::swap(u, v);
    if (size[u] == size[v]) size[v]++, stk[++top] = -v;
    p[u] = v, dis[u] = f, stk[++top] = u;
}
inline void revert(int time) {
    for (; top > time; --top)
        if (stk[top] < 0)
            size[-stk[top]]--;
        else
            dis[p[stk[top]] = stk[top]] = 0;
}
struct oper {
    int l, r, x, y;
} op[MAXN];
void slove(int l, int r, int k) {
    int snapshot = top;
    for (int i = 1; i <= k; i++) {
        if (op[i].l <= l && op[i].r >= r) {
            int U = find(op[i].x), V = find(op[i].y);
            if (U != V)
                merge(U, V, color(op[i].x) == color(op[i].y));
            else {
                if (color(op[i].x) == color(op[i].y)) {
                    for (int i = l; i <= r; i++) puts("NO");
                    revert(snapshot);
                    return;
                }
            }
            std::swap(op[k--], op[i--]);
        }
    }
    if (l == r) return puts("YES"), revert(snapshot), void();
    int mid = (l + r) >> 1, i, d;
    for (i = 1, d = 0; i <= k; i++)
        if (op[i].l <= mid) std::swap(op[++d], op[i]);
    slove(l, mid, d);
    for (i = 1, d = 0; i <= k; i++)
        if (op[i].r > mid) std::swap(op[++d], op[i]);
    slove(mid + 1, r, d);
    revert(snapshot);
}
int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 1; i <= q; i++) scanf("%d%d", &e[i].first, &e[i].second);
    for (int i = q; i >= 1; i--) r[i] = M[e[i]], M[e[i]] = i;
    M.clear();
    for (int i = 1; i <= q; i++) {
        if (!r[i]) r[i] = q + 1;
        if (M[e[i]]) {
            M[e[i]] = 0;
            continue;
        }
        M[e[i]] = 1;
        op[++m] = {i, r[i] - 1, e[i].first, e[i].second};
    }
    slove(1, q, m);
    return 0;
}