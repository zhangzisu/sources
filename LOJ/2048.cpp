#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 500010
#define SQRT 315
#define INF 0x3F3F3F3F

int n, m, q;
struct data {
    int u, v, a, b, id;
} e[MAXN], Q[MAXN], tmp[MAXN];

int p[MAXN], size[MAXN], a[MAXN], b[MAXN], ans[MAXN], top;
struct oper {
    int *x, v;
    inline oper(int *x = NULL, int v = 0) {
        this->x = x;
        this->v = v;
    }
} stk[MAXN];
inline int find(int x) {
    while (x != p[x]) x = p[x];
    return x;
}
inline void merge(int x, int y, int A, int B) {
    x = find(x), y = find(y);
    stk[++top] = oper(a + x, a[x]);
    stk[++top] = oper(b + x, b[x]);
    if (x == y) return a[x] = std::max(a[x], A), b[x] = std::max(b[x], B), void();
    if (size[x] < size[y]) std::swap(x, y);
    stk[++top] = oper(size + x, size[x]);
    stk[++top] = oper(p + y, p[y]);
    size[x] += size[y];
    p[y] = x;
    a[x] = std::max(a[x], std::max(a[y], A));
    b[x] = std::max(b[x], std::max(b[y], B));
}
inline void revert(int stamp) {
    for (; top > stamp; top--) {
        *stk[top].x = stk[top].v;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].a, &e[i].b);
        e[i].id = i;
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d%d%d%d", &Q[i].u, &Q[i].v, &Q[i].a, &Q[i].b);
        Q[i].id = i;
    }

    std::sort(e + 1, e + m + 1, [](data a, data b) { return a.a < b.a; });
    std::sort(Q + 1, Q + q + 1, [](data a, data b) { return a.b < b.b; });
    e[m + 1].a = INF;

    for (int l = 1; l <= m; l += SQRT) {
        int r = std::min(l + SQRT - 1, m);
        int cnt = 0;
        for (int i = 1; i <= q; i++)
            if (Q[i].a >= e[l].a && Q[i].a < e[r + 1].a)
                tmp[++cnt] = Q[i];
        std::sort(e + 1, e + l, [](data a, data b) { return a.b < b.b; });
        for (int i = 1; i <= n; i++) p[i] = i, size[i] = 1, a[i] = b[i] = -1;
        for (int i = 1, cur = 1; i <= cnt; i++) {
            while (cur < l && e[cur].b <= Q[i].b)
                merge(e[cur].u, e[cur].v, e[cur].a, e[cur].b), cur++;
            int stamp = top;
            for (int j = l; j <= r; j++) {
                if (e[j].a <= Q[i].a && e[j].b <= Q[i].b) {
                    // printf("MERGE %d %d => (%d %d)\n", e[j].u, e[j].v, e[j].a, e[j].b);
                    merge(e[j].u, e[j].v, e[j].a, e[j].b);
                }
            }
            // puts("");
            int x = find(Q[i].u), y = find(Q[i].v);
            ans[Q[i].id] = x == y && a[x] == Q[i].a && b[x] == Q[i].b;
            revert(stamp);
        }
    }
    for (int i = 1; i <= q; i++) puts(ans[i] ? "Yes" : "No");
    return 0;
}