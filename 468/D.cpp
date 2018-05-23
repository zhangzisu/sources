#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#define MAXN 200010
#define INF 0x3F3F3F3F
int n, head[MAXN], to[MAXN << 1], next[MAXN << 1], val[MAXN << 1], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int size[MAXN], fn[MAXN], bel[MAXN], l[MAXN], r[MAXN], rt = 0, dfsclk = 0;
void slg(int x, int f) {
    size[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == f) continue;
        slg(to[i], x);
        size[x] += size[to[i]];
        fn[x] = std::max(fn[x], size[to[i]]);
    }
    fn[x] = std::max(fn[x], n - size[x]);
    if (fn[x] < fn[rt]) rt = x;
}
long long ans = 0, deep[MAXN];
void reb(int x, int f, int b) {
    size[x] = 1, bel[x] = b, ans += deep[x], l[x] = ++dfsclk;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == f) continue;
        deep[to[i]] = deep[x] + val[i];
        reb(to[i], x, b);
        size[x] += size[to[i]];
    }
    r[x] = dfsclk;
}
int min[MAXN << 2];
void modify(int n, int l, int r, int p, int v) {
    if (l == r) return min[n] = v, void();
    int mid = (l + r) >> 1;
    if (p <= mid)
        modify(n << 1, l, mid, p, v);
    else
        modify(n << 1 | 1, mid + 1, r, p, v);
    min[n] = std::min(min[n << 1], min[n << 1 | 1]);
}
int query(int n, int l, int r, int L, int R) {
    if (l == L && r == R) return min[n];
    int mid = (l + r) >> 1;
    if (R <= mid) return query(n << 1, l, mid, L, R);
    if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R);
    return std::min(query(n << 1, l, mid, L, mid), query(n << 1 | 1, mid + 1, r, mid + 1, R));
}
inline int in(int tr) {
    return query(1, 1, n, l[tr], r[tr]);
}
inline int out(int tr) {
    int ret = INF;
    if (l[tr] - 1 >= 1) ret = std::min(ret, query(1, 1, n, 1, l[tr] - 1));
    if (r[tr] + 1 <= n) ret = std::min(ret, query(1, 1, n, r[tr] + 1, n));
    return ret;
}
std::set<int> pos[MAXN << 1];
std::vector<int> g;
int main() {
    fn[0] = INF;
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    for (int i = 1, x, y, z; i < n; i++) {
        scanf("%d%d%d", &x, &y, &z);
        $(x, y, z);
    }
    slg(1, 0);
    l[rt] = ++dfsclk;
    for (int i = head[rt]; ~i; i = next[i]) {
        deep[to[i]] = val[i];
        reb(to[i], rt, to[i]);
        pos[size[to[i]] <<= 1].insert(to[i]);
    }
    r[rt] = dfsclk;
    memset(min, 0x3F, sizeof(min));
    for (int i = 1; i <= n; i++) modify(1, 1, n, l[i], i);
    printf("%lld\n", ans * 2);
    for (int i = 1; i <= n; i++) {
        int rest = n - i + 1;
        g.clear();
        for (auto x : pos[rest]) g.push_back(x);
        int p;
        if (g.size() == 2) {
            p = g[0] == bel[i] ? in(g[1]) : in(g[0]);
        } else if (g.size() == 1) {
            p = g[0] == bel[i] ? out(bel[i]) : in(g[0]);
        } else {
            p = i == rt ? query(1, 1, n, 1, n) : out(bel[i]);
        }
        // printf("node %d match %d.\n", i, p);
        // printf("place %d upgraded\n", l[p]);
        modify(1, 1, n, l[p], INF);
        if (i != rt) {
            pos[size[bel[i]]].erase(bel[i]);
            pos[--size[bel[i]]].insert(bel[i]);
        }
        if (p != rt) {
            pos[size[bel[p]]].erase(bel[p]);
            pos[--size[bel[p]]].insert(bel[p]);
        }
        printf("%d ", p);
    }
    return puts(""), 0;
}