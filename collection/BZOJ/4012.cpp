#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 150010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], len[MAXN << 1], tot = 0;
inline void $(int u, int v, long long w) {
    next[tot] = head[u], to[tot] = v, len[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, len[tot] = w, head[v] = tot++;
}
std::pair<int, int> dat[MAXN];
int n, q, s[MAXN], d[MAXN], top[MAXN], dfn[MAXN], v[MAXN], fa[MAXN], tim, cnt;
long long dis[MAXN], pfx[MAXN], sum[MAXN], all, ans;
void $(int x) {
    s[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] != fa[x]) {
            d[to[i]] = d[x] + 1;
            dis[to[i]] = dis[x] + (v[to[i]] = len[i]);
            all += dis[to[i]];
            fa[to[i]] = x;
            $(to[i]);
            s[x] += s[to[i]];
        }
    }
}
void $$(int x) {
    dfn[x] = ++tim;
    if (!top[x]) top[x] = x;
    int huge = 0;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && s[to[i]] > s[huge]) huge = to[i];
    if (huge) top[huge] = top[x], $$(huge);
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && to[i] != huge) $$(to[i]);
}
struct node {
    long long val, sum;
    int l, r;
    inline node() { val = sum = l = r = 0; }
    inline node(const node &o) { val = o.val, sum = o.sum, l = o.l, r = o.r; }
} sg[20000005];
void Insert(int &n, int m, int l, int r, int L, int R) {
    sg[n = ++cnt] = node(sg[m]);
    if (l == L && r == R) return (void)(sg[n].val++);
    sg[n].sum += pfx[R] - pfx[L - 1];
    int mid = (l + r) >> 1;
    if (R <= mid) return Insert(sg[n].l, sg[m].l, l, mid, L, R);
    if (L > mid) return Insert(sg[n].r, sg[m].r, mid + 1, r, L, R);
    Insert(sg[n].l, sg[m].l, l, mid, L, mid), Insert(sg[n].r, sg[m].r, mid + 1, r, mid + 1, R);
}
long long Query(int n, int m, int l, int r, int L, int R) {
    long long retn = sg[n].val * (pfx[R] - pfx[L - 1]);
    long long retm = sg[m].val * (pfx[R] - pfx[L - 1]);
    if (l == L && r == R) return retm + sg[m].sum - retn - sg[n].sum;
    int mid = (l + r) >> 1;
    if (R <= mid) return retm - retn + Query(sg[n].l, sg[m].l, l, mid, L, R);
    if (L > mid) return retm - retn + Query(sg[n].r, sg[m].r, mid + 1, r, L, R);
    return retm - retn + Query(sg[n].l, sg[m].l, l, mid, L, mid) + Query(sg[n].r, sg[m].r, mid + 1, r, mid + 1, R);
}
int root[MAXN], mod;
int main() {
    scanf("%d%d%d", &n, &q, &mod);
    for (int i = 1; i <= n; i++) scanf("%d", &dat[i].first), dat[i].second = i;
    std::sort(dat + 1, dat + n + 1);
    memset(head, -1, sizeof(head));
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        $(u, v, w);
    }
    $(1), $$(1);
    for (int i = 1; i <= n; i++) pfx[dfn[i]] = v[i];
    for (int i = 1; i <= n; i++) pfx[i] += pfx[i - 1], sum[i] = sum[i - 1] + dis[dat[i].second];
    for (int i = 1; i <= n; i++) {
        root[i] = root[i - 1];
        for (int x = dat[i].second; x; x = fa[top[x]]) Insert(root[i], root[i], 1, n, dfn[top[x]], dfn[x]);
    }
    while (q--) {
        int k, l, r;
        scanf("%d%d%d", &k, &l, &r);
        l = (ans + l) % mod;
        r = (ans + r) % mod;
        if (l > r) std::swap(l, r);
        l = (std::lower_bound(dat + 1, dat + n + 1, std::make_pair(l, 0)) - dat) - 1;
        r = (std::upper_bound(dat + 1, dat + n + 1, std::make_pair(r, 0x3F3F3F3F)) - dat) - 1;
        ans = dis[k] * (r - l) + sum[r] - sum[l];
        for (int x = k; x; x = fa[top[x]]) ans -= Query(root[l], root[r], 1, n, dfn[top[x]], dfn[x]) << 1;
        printf("%lld\n", ans);
    }
    return 0;
}