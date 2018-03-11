#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <vector>
#define MAXN 500010

int p[MAXN], n, m, l[MAXN], r[MAXN], bel[MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
std::vector<int> id[MAXN << 2];
inline void fuck(int n, int pid) {
    int x = find(n), y = find(pid);
    if (x == y) return;
    p[x] = y;
    l[y] = std::min(l[y], l[x]);
    r[y] = std::max(r[y], r[x]);
}
void fuck(int n, int l, int r, int p, int pid) {
    for (auto i : id[n]) fuck(i, pid);
    if (id[n].size()) {
        id[n].clear();
        id[n].push_back(find(pid));
    }
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (p <= mid)
        fuck(n << 1, l, mid, p, pid);
    else
        fuck(n << 1 | 1, mid + 1, r, p, pid);
}
void fuck(int n, int l, int r, int L, int R, int pid) {
    if (l == L && r == R) return id[n].push_back(pid);
    int mid = (l + r) >> 1;
    if (R <= mid) return fuck(n << 1, l, mid, L, R, pid);
    if (L > mid) return fuck(n << 1 | 1, mid + 1, r, L, R, pid);
    fuck(n << 1, l, mid, L, mid, pid);
    fuck(n << 1 | 1, mid + 1, r, mid + 1, R, pid);
}
struct Query {
    int t, x, y;
} Q[MAXN];
std::map<int, int> M;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &Q[i].t, &Q[i].x, &Q[i].y);
        if (Q[i].t == 1) M[Q[i].x] = M[Q[i].y] = 1;
    }
    int now = 0;
    for (auto &i : M) i.second = ++now;
    for (int i = 1; i <= n; i++) {
        int t = Q[i].t, x = Q[i].x, y = Q[i].y;
        if (t == 1) {
            x = M[x], y = M[y];
            bel[++m] = i;
            p[i] = i;
            fuck(1, 1, now, x, i);
            fuck(1, 1, now, y, i);
            if (x + 1 <= y - 1) fuck(1, 1, now, x + 1, y - 1, i);
        } else {
            int X = find(bel[x]), Y = find(bel[y]);
            if (X == Y) {
                puts("YES");
                continue;
            }
            if (l[Y] < l[X] && l[X] < r[Y]) {
                puts("YES");
                continue;
            }
            if (l[Y] < r[X] && r[X] < r[Y]) {
                puts("YES");
                continue;
            }
            puts("NO");
        }
    }
}