#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#define MAXN 100010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int n, m;
struct Heap {
    std::priority_queue<int> a, b;
    inline void push(int x) { a.push(x); }
    inline void del(int x) { b.push(x); }
    inline int top() {
        while (b.size() && a.top() == b.top()) a.pop(), b.pop();
        return a.top();
    }
} dat[MAXN << 2];
int size[MAXN], deep[MAXN], fa[MAXN], dfn[MAXN], top[MAXN], tim;
void s(int x) {
    size[x] = 1;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x]) {
            fa[to[i]] = x;
            deep[to[i]] = deep[x] + 1;
            s(to[i]);
            size[x] += size[to[i]];
        }
}
void d(int x) {
    if (!top[x]) top[x] = x;
    dfn[x] = ++tim;
    register int huge = 0;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && size[to[i]] > size[huge]) huge = to[i];
    if (huge) top[huge] = top[x], d(huge);
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && to[i] != huge) d(to[i]);
}
void build(int n, int l, int r) {
    dat[n].push(-1);
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(n << 1, l, mid);
    build(n << 1 | 1, mid + 1, r);
}
void add(int n, int l, int r, int L, int R, int val) {
    if (l == L && r == R) {
        dat[n].push(val);
        return;
    }
    int mid = (l + r) >> 1;
    if (R <= mid)
        add(n << 1, l, mid, L, R, val);
    else if (L > mid)
        add(n << 1 | 1, mid + 1, r, L, R, val);
    else
        add(n << 1, l, mid, L, mid, val),
            add(n << 1 | 1, mid + 1, r, mid + 1, R, val);
}
void del(int n, int l, int r, int L, int R, int val) {
    if (l == L && r == R) {
        dat[n].del(val);
        return;
    }
    int mid = (l + r) >> 1;
    if (R <= mid)
        del(n << 1, l, mid, L, R, val);
    else if (L > mid)
        del(n << 1 | 1, mid + 1, r, L, R, val);
    else
        del(n << 1, l, mid, L, mid, val),
            del(n << 1 | 1, mid + 1, r, mid + 1, R, val);
}
int query(int n, int l, int r, int x) {
    if (l == r) return dat[n].top();
    int mid = (l + r) >> 1;
    if (x <= mid)
        return std::max(dat[n].top(), query(n << 1, l, mid, x));
    else
        return std::max(dat[n].top(), query(n << 1 | 1, mid + 1, r, x));
}
std::vector<std::pair<int, int>> V;
inline void add(int u, int v, int w) {
    V.clear();
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]]) std::swap(u, v);
        V.push_back(std::make_pair(dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if (deep[u] > deep[v]) std::swap(u, v);
    V.push_back(std::make_pair(dfn[u], dfn[v]));
    V.push_back(std::make_pair(0, 0));
    V.push_back(std::make_pair(n + 1, n + 1));
    std::sort(V.begin(), V.end());
    for (unsigned i = 1; i < V.size(); i++)
        if (V[i - 1].second + 1 < V[i].first)
            add(1, 1, n, V[i - 1].second + 1, V[i].first - 1, w);
}
inline void del(int u, int v, int w) {
    V.clear();
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]]) std::swap(u, v);
        V.push_back(std::make_pair(dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if (deep[u] > deep[v]) std::swap(u, v);
    V.push_back(std::make_pair(dfn[u], dfn[v]));
    V.push_back(std::make_pair(0, 0));
    V.push_back(std::make_pair(n + 1, n + 1));
    std::sort(V.begin(), V.end());
    for (unsigned i = 1; i < V.size(); i++)
        if (V[i - 1].second + 1 < V[i].first)
            del(1, 1, n, V[i - 1].second + 1, V[i].first - 1, w);
}
int a[MAXN << 2], b[MAXN << 2], c[MAXN << 2];
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        $(u, v);
    }
    s(1);
    d(1);
    build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        int x;
        scanf("%d", &x);
        if (x == 0) {
            scanf("%d%d%d", &a[i], &b[i], &c[i]);
            add(a[i], b[i], c[i]);
        } else if (x == 2) {
            int x;
            scanf("%d", &x);
            printf("%d\n", query(1, 1, n, dfn[x]));
        } else if (x == 1) {
            int x;
            scanf("%d", &x);
            del(a[x], b[x], c[x]);
        }
    }
    return 0;
}