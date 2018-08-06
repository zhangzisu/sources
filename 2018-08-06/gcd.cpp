#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 100010
#define MAXM 5000100
#define MAXV 350
const int INF = (~0U) >> 1;
int vis[MAXV], pri[MAXV], pnt;
inline void shai() {
    for (int i = 2; i < MAXV; i++) {
        if (!vis[i]) pri[++pnt] = i;
        for (int j = 1; j <= pnt; j++) {
            if (i * pri[j] >= MAXV) break;
            vis[i * pri[j]] = 1;
            if (i % pri[j] == 0) break;
        }
    }
}
int n, m, a[MAXN];
std::vector<int> val[MAXN], tmp;
std::vector<std::pair<int, int> > d;
int root[MAXN], max[MAXM], L[MAXM], R[MAXM], all = 0, rnt = 0;
void insert(int &n, int l, int r, int p, int v) {
    if (!n) n = ++all;
    max[n] = std::max(max[n], v);
    if (l == r) return;
    int mid = (l + r) >> 1;
    p <= mid ? insert(L[n], l, mid, p, v) : insert(R[n], mid + 1, r, p, v);
}
int query(int n, int l, int r, int _l, int _r) {
    if (!n) return -1;
    if (l == _l && r == _r) return max[n];
    int mid = (l + r) >> 1;
    if (_r <= mid) return query(L[n], l, mid, _l, _r);
    if (_l > mid) return query(R[n], mid + 1, r, _l, _r);
    return std::max(query(L[n], l, mid, _l, mid), query(R[n], mid + 1, r, mid + 1, _r));
}
std::map<int, int> M;
int main() {
#ifndef DEBUG
    freopen("gcd.in", "r", stdin);
    freopen("gcd.out", "w", stdout);
#endif
    shai();
    n = $(), m = $();
    for (int i = 1, x; i <= n; i++) {
        x = $();
        a[i] = x;
        d.push_back(std::make_pair(x, i));
        for (int j = 1; j <= pnt && x != 1 && pri[j] * pri[j] <= x; j++) {
            if (x % pri[j]) continue;
            val[i].push_back(pri[j]);
            while (x % pri[j] == 0) x /= pri[j];
        }
        if (x != 1) val[i].push_back(x);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (int)val[i].size(); j++) {
            int &p = M[val[i][j]];
            if (!p) p = ++rnt;
            insert(root[p], 1, n, i, a[i]);
        }
    }
    std::sort(d.begin(), d.end());
    for (int g, l, r, ans; m; m--) {
        g = $(), l = $(), r = $();
        tmp.clear();
        for (int j = 1; j <= pnt && g != 1 && pri[j] * pri[j] <= g; j++) {
            if (g % pri[j]) continue;
            tmp.push_back(pri[j]);
            while (g % pri[j] == 0) g /= pri[j];
        }
        if (g != 1) tmp.push_back(g);
        ans = -1;
        for (int j = 0; j < (int)tmp.size(); j++) {
            if (!M.count(tmp[j])) continue;
            ans = std::max(ans, query(root[M[tmp[j]]], 1, n, l, r));
        }
        if (!~ans) {
            puts("-1 -1");
            continue;
        }
        int count = std::upper_bound(d.begin(), d.end(), std::make_pair(ans, r)) - std::lower_bound(d.begin(), d.end(), std::make_pair(ans, l));
        printf("%d %d\n", ans, count);
    }
    // fprintf(stderr, "RNT: %d, ALL: %d\n", rnt, all);
    return 0;
}