#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <set>
#include <vector>
#define MAXN 100010
typedef long long lnt;
int n, m, a[MAXN], l[MAXN], r[MAXN], op[MAXN], val[MAXN];
lnt BIT[MAXN];
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int y) {
    for (; x <= n; x += lowbit(x)) BIT[x] += y;
}
inline lnt qry(int x) {
    register lnt y = 0;
    for (; x; x -= lowbit(x)) y += BIT[x];
    return y;
}
std::set<int> v[1000010];
bool vis[1000010];
int tmp[8000010], t, k;
std::pair<int, int> b[8000010];
int main() {
    int start = clock();
    scanf("%d%d", &n, &m);
    for (register int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        add(i, a[i]);
    }
    for (register int i = 1; i <= m; i++) {
        scanf("%d%d%d", &op[i], &l[i], &r[i]);
        if (op[i] == 1) scanf("%d", &val[i]), vis[val[i]] = 1;
    }
    for (register int i = 1; i <= n; i++) {
        for (register int j = 1; j * j <= a[i]; j++) {
            if (a[i] % j == 0 && (vis[j] || vis[a[i] / j])) {
                if (vis[j]) {
                    b[++k] = std::make_pair(j, i);
                }
                if (j * j != a[i] && vis[a[i] / j]) {
                    b[++k] = std::make_pair(a[i] / j, i);
                }
            }
        }
    }
    std::sort(b + 1, b + k + 1);
    for (register int i = 1; i <= k; i++) {
        tmp[++t] = b[i].second;
        if (i == k || b[i].first != b[i + 1].first) {
            std::set<int> &pos = v[b[i].first];
            for (int i = 0; i <= t; i++) pos.insert(tmp[i]);
            t = 0;
        }
    }
    for (register int i = 1; i <= m; i++) {
        if (op[i] == 1) {
            if (val[i] == 1) continue;
            for (std::set<int>::iterator it = v[val[i]].lower_bound(l[i]); it != v[val[i]].end() && *it <= r[i];) {
                int pos = *it;
                if (a[pos] % val[i] == 0) {
                    add(pos, -a[pos]);
                    add(pos, a[pos] /= val[i]);
                }
                if (a[pos] % val[i])
                    v[val[i]].erase(it++);
                else
                    it++;
            }
        } else {
            printf("%lld\n", qry(r[i]) - qry(l[i] - 1));
        }
    }
    fprintf(stderr, "Time spent: %lf\n", 1. * (clock() - start) / CLOCKS_PER_SEC);
    return 0;
}