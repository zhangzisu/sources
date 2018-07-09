#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n = $(), m = $(), a[MAXN], pre[MAXN], next[MAXN], tmp[MAXN], f[MAXN], root;


int ans, l, r, x, y;
void Query(int n) {
    if (!n) return;
    if (p[n].max[0] < l || p[n].min[0] > r) return;
    if (p[n].dat[2] < ans || p[n].min[1] >= l || p[n].max[2] <= r) return;
    if (p[n].val[0] >= l && p[n].val[0] <= r &&
        p[n].val[1] < l && p[n].val[2] > r) ans = std::max(ans, p[n].dat[0]);
    Query(p[n].l);
    Query(p[n].r);
}

int main() {
    for (int i = 1; i <= n; i++) p[i] = node(l[i], r[i]), f[i] = i;
    Build(root, 1, n, 0);
    //print();
    while (m--) {
        x = $(), y = $();
        l = std::min((x + ans) % n + 1, (y + ans) % n + 1);
        r = std::max((x + ans) % n + 1, (y + ans) % n + 1);
        ans = 0;
        Query(root);
        printf("%d\n", ans);
    }
    return 0;
}