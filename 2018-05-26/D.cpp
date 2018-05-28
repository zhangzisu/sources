#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 100010

int n, m, a[MAXN], b[MAXN], c[MAXN], p[MAXN];
struct edge {
    int u, v, w;
    inline friend bool operator<(const edge &a, const edge &b) {
        return a.w < b.w;
    }
} e[MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
std::vector<int> next[MAXN];
long long sum[MAXN];

long long dp(int x) {
    long long ret = c[x];
    sum[x] = b[x];
    for (int y : next[x]) {
        long long res = dp(y);
        ret = std::min(ret, std::max(0LL + c[x], res) - sum[y]);
        sum[x] += sum[y];
    }
    return ret + sum[x];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i], &b[i]);
        a[i] = std::max(a[i], b[i]);
        c[i] = a[i] - b[i];
        p[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &e[i].u, &e[i].v);
        e[i].w = std::max(c[e[i].u], c[e[i].v]);
    }
    std::sort(e + 1, e + m + 1);
    for (int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v;
        if (find(u) == find(v)) continue;
        if (c[u] < c[v]) std::swap(u, v);
        next[find(u)].push_back(find(v));
        p[find(v)] = find(u);
    }
    printf("%lld\n", dp(find(1)));
    return 0;
}