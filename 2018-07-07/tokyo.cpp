#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#define MAXN 100010
const int INF = (~0U) >> 2;

int n, a[MAXN], b[MAXN], c[MAXN], d[MAXN], val[3][2], m;

inline void up(int &x, int y) { x = std::max(x, y); }
inline void down(int &x, int y) { x = std::min(x, y); }

std::pair<int, int> dat[3][MAXN];
struct data {
    int a, b, c, d, f;
} t[MAXN], p[MAXN];

int f[MAXN], root = 0, cnt = 0;
struct node {
    int val[4], max[4], min[4], l, r, f, dat, max_dat;
    inline node(int a = 0, int b = 0, int c = 0, int d = 0, int v = 0) {
        val[0] = max[0] = min[0] = a;
        val[1] = max[1] = min[1] = b;
        val[2] = max[2] = min[2] = c;
        val[3] = max[3] = min[3] = d;
        dat = max_dat = v;
        l = r = f = 0;
    }
    inline void clear() {
        max[0] = min[0] = val[0];
        max[1] = min[1] = val[1];
        max[2] = min[2] = val[2];
        max[3] = min[3] = val[3];
        max_dat = dat;
    }
    inline void reset() {
        clear();
        l = r = f = 0;
    }
    inline void get(const node &b) {
        max[0] = std::max(max[0], b.max[0]);
        min[0] = std::min(min[0], b.min[0]);
        max[1] = std::max(max[1], b.max[1]);
        min[1] = std::min(min[1], b.min[1]);
        max[2] = std::max(max[2], b.max[2]);
        min[2] = std::min(min[2], b.min[2]);
        max[3] = std::max(max[3], b.max[3]);
        min[3] = std::min(min[3], b.min[3]);
        max_dat = std::max(max_dat, b.max_dat);
    }
} tree[MAXN];
inline void insert(int x) {
    register int f = 0, d = 0;
    register int *p = &root;
    while (*p) {
        f = *p;
        if (tree[x].val[d] <= tree[*p].val[d])
            p = &(tree[*p].l);
        else
            p = &(tree[*p].r);
        d = (d + 1) % 4;
    }
    *p = x;
    tree[x].f = f;
    while (f) {
        tree[f].clear();
        if (tree[f].l) tree[f].get(tree[tree[f].l]);
        if (tree[f].r) tree[f].get(tree[tree[f].r]);
        f = tree[f].f;
    }
}
int D;
inline int cmp(const int &a, const int &b) { return tree[a].val[D] < tree[b].val[D]; }
void build(int &n, int l, int r, int d) {
    int mid = (l + r) >> 1;
    ::D = d;
    std::nth_element(f + l, f + mid, f + r, cmp);
    n = f[mid];
    if (l < mid) build(tree[n].l, l, mid - 1, (d + 1) % 4), tree[n].get(tree[tree[n].l]);
    if (r > mid) build(tree[n].r, mid + 1, r, (d + 1) % 4), tree[n].get(tree[tree[n].r]);
    if (tree[n].l) tree[tree[n].l].f = n;
    if (tree[n].r) tree[tree[n].r].f = n;
}
inline void rebuild() {
    for (int i = 1; i <= cnt; i++) f[i] = i, tree[i].reset();
    build(root, 1, cnt, 0);
}
int result;
void query(int n, int a, int b, int c, int d) {
    if (!n) return;
    if (tree[n].max_dat < result) return;
    if (tree[n].min[0] >= a || tree[n].min[1] >= b || tree[n].min[2] >= c || tree[n].min[3] >= d) return;
    if (tree[n].max[0] < a && tree[n].max[1] < b && tree[n].max[2] < c && tree[n].max[3] < d) return up(result, tree[n].max_dat);
    if (tree[n].val[0] < a && tree[n].val[1] < b && tree[n].val[2] < c && tree[n].val[3] < d) up(result, tree[n].dat);
    query(tree[n].l, a, b, c, d);
    query(tree[n].r, a, b, c, d);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), dat[0][i] = std::make_pair(a[i], i);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]), dat[1][i] = std::make_pair(b[i], i);
    for (int i = 1; i <= n; i++) scanf("%d", &c[i]), dat[2][i] = std::make_pair(c[i], i);
    for (int i = 1; i <= n; i++) scanf("%d", &d[i]);
    for (int i = 0; i < 3; i++) std::sort(dat[i] + 1, dat[i] + n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            auto a = std::lower_bound(dat[j] + 1, dat[j] + n + 1, std::make_pair(d[i], 0));
            auto b = a + 1;
            val[j][0] = a->first == d[i] ? a->second : INF;
            val[j][1] = b->first == d[i] ? b->second : INF;
        }
        for (int j = 0; j < 8; j++) {
            if (val[0][j & 1] == INF || val[1][(j >> 1) & 1] == INF || val[2][(j >> 2) & 1] == INF) continue;
            t[++m] = {i, val[0][j & 1], val[1][(j >> 1) & 1], val[2][(j >> 2) & 1], 0};
        }
    }
    // for (int i = 1; i <= m; i++) printf("%d %d %d\n", t[i].b, t[i].c, t[i].d);
    // puts("FINISHED");

    // int start = clock();
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        t[i].f = 1;
        result = 0;
        query(root, t[i].a, t[i].b, t[i].c, t[i].d);
        up(t[i].f, result + 1);
        up(ans, t[i].f);
        tree[++cnt] = node(t[i].a, t[i].b, t[i].c, t[i].d, t[i].f);
        if (!(cnt % 1200))
            rebuild();
        else
            insert(cnt);
    }
    printf("%d\n", ans);
    // printf("%lf\n", 1. * (clock() - start) / CLOCKS_PER_SEC);
    return 0;
}