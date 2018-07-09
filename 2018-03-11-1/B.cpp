#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#define MAXN 500010
#define BLOCK 2000
struct Query {
    int l, r, t;
    long long *p;
    inline friend bool operator<(const Query &a, const Query &b) {
        if (a.l / BLOCK == b.l / BLOCK) {
            return a.r / BLOCK == b.r / BLOCK ? a.t < b.t : a.r < b.r;
        } else
            return a.l < b.l;
    }
} qry[MAXN];
struct Modify {
    int x, y;
} mdf[MAXN];
int qs, ms, rq;
int ch[MAXN][2], pos[MAXN], dd[MAXN], cnt = 1;
inline void insert(int g) {
    register char c = getchar();
    while (!isalpha(c)) c = getchar();
    int p = 1, d;
    for (; isalpha(c); c = getchar()) {
        if (!ch[p][d = c - 'a']) ch[p][d] = ++cnt;
        p = ch[p][d];
    }
    dd[pos[g] = p] = 1;
}
int first[MAXN], last[MAXN], dfsclk = 0;
inline void dfs(int x) {
    first[x] = 0x3F3F3F3F, last[x] = 0;
    if (dd[x]) first[x] = last[x] = ++dfsclk;
    if (ch[x][0]) {
        dfs(ch[x][0]);
        last[x] = std::max(last[x], last[ch[x][0]]);
        first[x] = std::min(first[x], first[ch[x][0]]);
    }
    if (ch[x][1]) {
        dfs(ch[x][1]);
        last[x] = std::max(last[x], last[ch[x][1]]);
        first[x] = std::min(first[x], first[ch[x][1]]);
    }
}
int n, m, q, type[MAXN], sum[MAXN];
long long val[MAXN], W[MAXN], *w = W + 1, ans[MAXN];

std::vector<int> his[MAXN];

inline int _() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}

int main() {
    n = _(), m = _(), q = _();
    for (int i = 1; i <= n; i++) {
        insert(i);
    }
    dfs(1);
    for (int i = 1; i <= n; i++) {
        type[first[pos[i]]] = _();
        his[first[pos[i]]].push_back(type[first[pos[i]]]);
    }
    for (int i = 1; i <= m; i++) val[i] = _();
    for (int i = 1; i <= n; i++) w[i] = _();

    int x, y;
    while (q--) {
        x = _();
        if (x == 1) {
            rq++, qs++;
            int p = 1;
            register char c = getchar();
            while (!isalpha(c)) c = getchar();
            for (; isalpha(c); c = getchar()) p = ch[p][c - 'a'];
            if (!p) {
                qs--, ans[rq] = 0;
            } else {
                qry[qs] = {first[p], last[p], ms, ans + rq};
            }
        } else {
            x = _();
            his[x = first[pos[x]]].push_back(y = _());
            mdf[++ms] = {x, (int)his[x].size() - 1};
        }
    }

    std::sort(qry + 1, qry + qs + 1);
    int l = 1, r = 0, t = 0;
    long long res = 0;
    for (int i = 1; i <= qs; i++) {
        while (t < qry[i].t) {
            ++t;
            int x = mdf[t].x, y = his[x][mdf[t].y];
            if (l <= x && x <= r) {
                sum[type[x]]--;
                res -= (w[sum[type[x]] + 1] - w[sum[type[x]]]) * val[type[x]];
                sum[y]++;
                res += (w[sum[y]] - w[sum[y] - 1]) * val[y];
            }
            type[x] = y;
        }
        while (t > qry[i].t) {
            int x = mdf[t].x, y = his[x][mdf[t].y - 1];
            if (l <= x && x <= r) {
                sum[type[x]]--;
                res -= (w[sum[type[x]] + 1] - w[sum[type[x]]]) * val[type[x]];
                sum[y]++;
                res += (w[sum[y]] - w[sum[y] - 1]) * val[y];
            }
            type[x] = y;
            t--;
        }
        while (l > qry[i].l) {
            sum[type[--l]]++;
            res += (w[sum[type[l]]] - w[sum[type[l]] - 1]) * val[type[l]];
        }
        while (r < qry[i].r) {
            sum[type[++r]]++;
            res += (w[sum[type[r]]] - w[sum[type[r]] - 1]) * val[type[r]];
        }
        while (l < qry[i].l) {
            res -= (w[sum[type[l]]] - w[sum[type[l]] - 1]) * val[type[l]];
            sum[type[l++]]--;
        }
        while (r > qry[i].r) {
            res -= (w[sum[type[r]]] - w[sum[type[r]] - 1]) * val[type[r]];
            sum[type[r--]]--;
        }
        *qry[i].p = res;
    }
    for (int i = 1; i <= rq; i++) printf("%lld\n", ans[i]);
    return 0;
}