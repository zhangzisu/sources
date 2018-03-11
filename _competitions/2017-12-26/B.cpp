#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 50010
#define BLOCK 256
#include <ext/hash_set>
int a[MAXN], ans[MAXN], f[MAXN], g[MAXN], n, m;
struct Query {
    int l, r, k, p;
    inline friend bool operator<(const Query &a, const Query &b) {
        return a.l / BLOCK == b.l / BLOCK ? a.r < b.r
                                          : a.l / BLOCK < b.l / BLOCK;
    }
} q[MAXN];
__gnu_cxx::hash_set<int> set;
inline void Del(int x) {
    if (!--g[f[x]]) set.erase(f[x]);
    if (!g[--f[x]]++) set.insert(f[x]);
}
inline void Add(int x) {
    if (!--g[f[x]]) set.erase(f[x]);
    if (!g[++f[x]]++) set.insert(f[x]);
}
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].k), q[i].p = i;
    std::sort(q + 1, q + m + 1);
    register int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        while (l < q[i].l) {
            Del(a[l++]);
        }
        while (l > q[i].l) {
            Add(a[--l]);
        }
        while (r < q[i].r) {
            Add(a[++r]);
        }
        while (r > q[i].r) {
            Del(a[r--]);
        }
        for (auto it : set)
            if (gcd(it, q[i].k) == 1) ans[q[i].p] += g[it];
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}