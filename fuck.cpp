#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define SQRT 315

struct data {
    int x, y, a, b, id;
} e[MAXN], q[MAXN], tmp[MAXN];
struct opt {
    int *x;
    int y;
    inline opt(int *v = NULL) {
        if (v) {
            this->x = v;
            this->y = *v;
        }
    }
} op[MAXN << 2];
int ans[MAXN], p[MAXN], a[MAXN], b[MAXN], size[MAXN], Q, n, m, tot;
int find(int x) {
    return p[x] == x ? x : find(p[x]);
}
void merge(int x, int y, int A, int B) {
    x = find(x);
    y = find(y);
    if (size[x] > size[y]) std::swap(x, y);
    op[++tot] = opt(a + y);
    op[++tot] = opt(b + y);
    op[++tot] = opt(p + x);
    op[++tot] = opt(size + y);
    if (x == y) {
        a[x] = std::max(a[x], A);
        b[x] = std::max(b[x], B);
        return;
    }
    p[x] = y;
    size[y] += size[x];
    a[y] = std::max(a[y], std::max(a[x], A));
    b[y] = std::max(b[y], std::max(b[x], B));
}
void revert() {
    for (; tot; tot--) {
        (*op[tot].x) = op[tot].y;
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d%d%d%d", &e[i].x, &e[i].y, &e[i].a, &e[i].b), e[i].id = i;
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) scanf("%d%d%d%d", &q[i].x, &q[i].y, &q[i].a, &q[i].b), q[i].id = i;
    std::sort(e + 1, e + 1 + m, [](data a, data b) { return a.a < b.a; });
    std::sort(q + 1, q + 1 + Q, [](data a, data b) { return a.b < b.b; });
    for (int i = 1; i <= m; i += SQRT) {
        int cnt = 0;
        for (int j = 1; j <= Q; j++)
            if (q[j].a >= e[i].a && (i + SQRT > m || q[j].a < e[i + SQRT].a))
                tmp[++cnt] = q[j];
        std::sort(e + 1, e + i, [](data a, data b) { return a.b < b.b; });
        for (int j = 1; j <= n; j++) p[j] = j, size[j] = 1, a[j] = b[j] = -1;
        for (int j = 1, k = 1; j <= cnt; j++) {
            for (; k < i && e[k].b <= tmp[j].b; k++)
                merge(e[k].x, e[k].y, e[k].a, e[k].b);
            tot = 0;
            for (int l = i; l < i + SQRT && l <= m; l++)
                if (e[l].a <= tmp[j].a && e[l].b <= tmp[j].b)
                    merge(e[l].x, e[l].y, e[l].a, e[l].b);
            int x = find(tmp[j].x);
            int y = find(tmp[j].y);
            ans[tmp[j].id] = x == y && a[x] == tmp[j].a && b[x] == tmp[j].b;
            revert();
        }
    }
    for (int i = 1; i <= Q; i++) puts(ans[i] ? "Yes" : "No");
    return 0;
}