#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
int n, m, x, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int s[MAXN], fa[MAXN], top[MAXN], down[MAXN], dfn[MAXN], pos[MAXN], deep[MAXN], tim;
long long ss[MAXN], f[MAXN], w[MAXN], y;
void $(int x) {
    s[x] = 1, f[x] = w[x];
    long long sum = 0;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x]) continue;
        deep[to[i]] = deep[x] + 1;
        fa[to[i]] = x;
        $(to[i]);
        s[x] += s[to[i]];
        sum += f[to[i]];
    }
    if (s[x] != 1) f[x] = std::min(f[x], sum);
}
void _(int x) {
    if (!top[x]) top[x] = x;
    int y = 0;
    pos[dfn[x] = ++tim] = x;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && s[to[i]] > s[y]) y = to[i];
    if (y) top[y] = top[x], _(y);
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && to[i] != y) _(to[i]), ss[x] += f[to[i]];
}
void d(int x) {
    down[top[x]] = x;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x]) d(to[i]);
}
struct trans {
    long long a, b;
    inline trans(long long a = 0, long long b = 0) : a(a), b(b) {}
    inline friend trans operator+(trans a, trans b) {
        return trans(std::min(a.a, a.b + b.a), a.b + b.b);
    }
    inline long long operator()(long long x) {
        return std::min(a, b + x);
    }
} val[MAXN << 2];
void Build(int n, int l, int r) {
    if (l == r) {
        val[n] = trans(w[pos[l]], ss[pos[l]]);
        return;
    }
    int mid = (l + r) >> 1;
    Build(n << 1, l, mid);
    Build(n << 1 | 1, mid + 1, r);
    val[n] = val[n << 1] + val[n << 1 | 1];
}
trans Query(int n, int l, int r, int L, int R) {
    if (l == L && r == R) return val[n];
    int mid = (l + r) >> 1;
    if (R <= mid)
        return Query(n << 1, l, mid, L, R);
    else if (L > mid)
        return Query(n << 1 | 1, mid + 1, r, L, R);
    else
        return Query(n << 1, l, mid, L, mid) + Query(n << 1 | 1, mid + 1, r, mid + 1, R);
}
void Modify(int n, int l, int r, int p, trans v) {
    if (l == r) {
        val[n] = v;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
        Modify(n << 1, l, mid, p, v);
    else
        Modify(n << 1 | 1, mid + 1, r, p, v);
    val[n] = val[n << 1] + val[n << 1 | 1];
}
long long F(int x) {
    return Query(1, 1, n, dfn[x], dfn[down[top[x]]])(0x3F3F3F3F);
}
inline void Modify(int x, long long y) {
    w[x] += y;
    while (x) {
        long long fx = F(top[x]);
        Modify(1, 1, n, dfn[x], trans(w[x], ss[x]));
        long long fy = F(top[x]);
        ss[fa[top[x]]] -= fx - fy;
        x = fa[top[x]];
    }
}
char buf[5];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &w[i]);
    memset(head, -1, sizeof(head));
    for (int i = 1; i < n; i++) {
        int fr, to;
        scanf("%d%d", &fr, &to);
        $(fr, to);
    }
    $(1), _(1), d(1);
    Build(1, 1, n);
    scanf("%d", &m);
    while (m--) {
        scanf("%s", buf);
        if (buf[0] == 'Q') {
            scanf("%d", &x);
            printf("%lld\n", F(x));
        } else {
            scanf("%d%lld", &x, &y);
            Modify(x, y);
        }
    }
    return 0;
}