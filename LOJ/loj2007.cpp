#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
int n, m, k, next[MAXN << 2][19], ans[MAXN];
struct node {
    int l, r, id;
    inline node(int l = 0, int r = 0, int id = 0) : l(l), r(r), id(id) {}
    inline friend bool operator<(const node &a, const node &b) {
        if (a.l == b.l) return a.r < b.r;
        return a.l < b.l;
    }
} data[MAXN << 2];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        if (r < l) r += m;
        data[++k] = node(l, r, i);
        data[++k] = node(l + m, r + m, i);
    }
    std::sort(data + 1, data + k + 1);
    for (int i = 1; i <= k; i++) {
        auto ind = node(data[i].r, 0x7FFFFFFF);
        next[i][0] = (std::upper_bound(data + 1, data + 1 + k, ind) - data) - 1;
        if (next[i][0] == i) next[i][0] = 0;
    }
    for (int d = 1; d <= 18; d++) {
        for (int i = 1; i <= k; i++) {
            next[i][d] = next[next[i][d - 1]][d - 1];
        }
    }
    for (int i = 1; i <= n; i++) {
        int p = i;
        for (int d = 18; d >= 0; d--) {
            if (next[p][d] && data[next[p][d]].r < data[i].l + m) {
                ans[data[i].id] += 1 << d;
                p = next[p][d];
            }
        }
    }
    for (int i = 1; i <= n; i++) printf("%d ", ans[i] + 2);
    puts("");
    return 0;
}