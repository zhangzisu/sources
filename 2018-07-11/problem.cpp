#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#define MAXN 1000010
#define MAXM 50000100
typedef long long lnt;
lnt n, m, k, head[MAXN], to[MAXN << 1], val[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(lnt u, lnt v, lnt w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
lnt fa[MAXN][17], deep[MAXN], len[MAXN][17];
inline lnt lca(lnt u, lnt v) {
    if (deep[u] < deep[v]) std::swap(u, v);
    lnt delta = deep[u] - deep[v];
    for (lnt i = 16; ~i; i--)
        if ((delta >> i) & 1) u = fa[u][i];
    for (lnt i = 16; ~i; i--)
        if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return u == v ? u : fa[u][0];
}
inline lnt mdr(lnt u, lnt v) {
    lnt ret = ~(0u) >> 1;
    for (lnt i = 16; ~i; i--)
        if (deep[fa[u][i]] >= deep[v]) ret = std::min(ret, len[u][i]), u = fa[u][i];
    return ret;
}
lnt root[MAXM], L[MAXM], R[MAXM], size[MAXM], sum[MAXM], cnt = 0;
inline void insert(lnt &n, lnt N, lnt l, lnt r, lnt p, lnt v) {
    n = ++cnt;
    L[n] = L[N], R[n] = R[N], sum[n] = sum[N], size[n] = size[N];
    sum[n] += v;
    size[n]++;
    if (l == r) return;
    lnt mid = (l + r) >> 1;
    if (p <= mid) return insert(L[n], L[N], l, mid, p, v);
    return insert(R[n], R[N], mid + 1, r, p, v);
}

std::vector<lnt> W;
lnt origin, count, max, s, t, q, a, b, sigma;
inline lnt calc(lnt count) {
    return a + std::max(count - 1, 0LL) * std::min(a, b);
}
void solve(lnt n0, lnt n1, lnt n2, lnt l, lnt r) {
    if (l == r) {
        count += size[n0] + size[n1] - 2 * size[n2];
        sigma += sum[n0] + sum[n1] - 2 * sum[n2];
        lnt delta = (count * W[l - 1] - sigma) * b;
        if (delta <= q) {
            max = l;
            return;
        }
        count -= size[n0] + size[n1] - 2 * size[n2];
        sigma -= sum[n0] + sum[n1] - 2 * sum[n2];
        return;
    }
    lnt mid = (l + r) >> 1;
    count += size[L[n0]] + size[L[n1]] - 2 * size[L[n2]];
    sigma += sum[L[n0]] + sum[L[n1]] - 2 * sum[L[n2]];
    lnt delta = (count * W[mid - 1] - sigma) * b;
    if (delta <= q) {
        max = mid;
        return solve(R[n0], R[n1], R[n2], mid + 1, r);
    }
    count -= size[L[n0]] + size[L[n1]] - 2 * size[L[n2]];
    sigma -= sum[L[n0]] + sum[L[n1]] - 2 * sum[L[n2]];
    solve(L[n0], L[n1], L[n2], l, mid);
}

void build(lnt x) {
    if (x != 1) insert(
        root[x],                                                            // This root
        root[fa[x][0]],                                                     // Pre root
        1,                                                                  // Left bound
        k,                                                                  // Right bound
        (std::lower_bound(W.begin(), W.end(), len[x][0]) - W.begin()) + 1,  // Position
        len[x][0]);                                                         // Value

    for (lnt i = 1; i < 17; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
        len[x][i] = std::min(len[x][i - 1], len[fa[x][i - 1]][i - 1]);
    }
    for (lnt i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x][0]) continue;
        fa[to[i]][0] = x;
        len[to[i]][0] = val[i];
        deep[to[i]] = deep[x] + 1;
        build(to[i]);
    }
}
int main() {
    memset(head, -1, sizeof(head));

    scanf("%lld%lld", &n, &m);

    for (lnt i = 1, u, v, w; i < n; i++) {
        scanf("%lld%lld%lld", &u, &v, &w);
        $(u, v, w);
        W.push_back(w);
    }
    std::sort(W.begin(), W.end());
    W.erase(std::unique(W.begin(), W.end()), W.end());
    k = W.size();
    deep[1] = 1;
    build(1);
    while (m--) {
        scanf("%lld%lld%lld%lld%lld", &s, &t, &q, &a, &b);

        lnt lca = ::lca(s, t);
        origin = std::min(::mdr(s, lca), ::mdr(t, lca));
        lnt countWithA = q >= a ? origin + 1 + (q - a) / std::min(a, b) : 0;

        count = sigma = max = 0;
        solve(root[s], root[t], root[lca], 1, k);
        lnt delta = (count * W[max - 1] - sigma) * b;
        lnt rest = q - delta;
        lnt countWithB = W[max - 1] + rest / (count * b);

        printf("%lld\n", std::max(countWithA, countWithB));
    }
    return 0;
}
