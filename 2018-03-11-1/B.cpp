#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#define MAXN 500010
#define BLOCK 6300
struct Query {
    int l, r, t, *p;
    inline friend bool operator<(const Query &a, const Query &b) {
        if (a.l / BLOCK == b.l / BLOCK) {
            return a.r == b.r ? a.t < b.t : a.r < b.r;
        } else
            return a.l < b.l;
    }
} qry[MAXN];
struct Modify {
    int x, y;
} mdf[MAXN];
int qs, ms, rq;
int ch[MAXN][2], fuck[MAXN], cnt = 1;
inline void insert(std::string &s, int pos) {
    int p = 1, d;
    for (int i = 0; i < (int)s.length(); i++) {
        if (!ch[p][d = s[i] ^ 'a']) ch[p][d] = ++cnt;
        p = ch[p][d];
    }
    fuck[pos] = p;
}
int first[MAXN], last[MAXN], dfsclk = 0;
inline void dfs(int x) {
    first[x] = last[x] = ++dfsclk;
    if (ch[x][0]) dfs(ch[x][0]), last[x] = std::max(last[x], last[ch[x][0]]);
    if (ch[x][1]) dfs(ch[x][1]), last[x] = std::max(last[x], last[ch[x][1]]);
}
int n, m, q, type[MAXN], val[MAXN], ddd[MAXN], w[MAXN], ans[MAXN];
std::string s;
std::vector<int> his[MAXN];
int main() {
    std::cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> s;
        insert(s, i);
        printf("FUCK[%d]=%d\n", i, fuck[i]);
    }
    for (int i = 1; i <= n; i++) std::cin >> type[first[fuck[i]]], his[i].push_back(i);
    for (int i = 1; i <= m; i++) std::cin >> val[i];
    for (int i = 1; i <= n; i++) std::cin >> w[i];
    dfs(1);
    dfsclk = 0;
    int x, y;
    while (q--) {
        std::cin >> x;
        if (x == 1) {
            std::cin >> s;
            rq++, qs++;
            int p = 1;
            for (int i = 0; i < (int)s.length(); i++) p = ch[p][s[i] ^ 'a'];
            if (!p) {
                qs--,
                    ans[rq] = 0;
            } else {
                qry[qs] = {first[p], last[p], dfsclk, ans + rq};
                std::cerr << "FUCK::" << s << "_DF_" << first[p] << "_DS_" << last[p] << "_DB_" << dfsclk << std::endl;
            }
        } else {
            std::cin >> x >> y;
            mdf[++ms] = {x, (his[x].push_back(y), (int)his[x].size() - 1)};
            ++dfsclk;
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
                res -= (w[ddd[type[x]]] - w[ddd[type[x]] - 1]) * val[type[x]];
                res += (w[ddd[type[y]]] - w[ddd[type[y]] - 1]) * val[type[y]];
                ddd[type[x]]--;
                ddd[type[y]]++;
            }
            type[x] = y;
        }
        while (t > qry[i].t) {
            int x = mdf[t].x, y = his[x][mdf[t].y - 1];
            if (l <= x && x <= r) {
                res -= (w[ddd[type[x]]] - w[ddd[type[x]] - 1]) * val[type[x]];
                res += (w[ddd[type[y]]] - w[ddd[type[y]] - 1]) * val[type[y]];
                ddd[type[x]]--;
                ddd[type[y]]++;
            }
            type[x] = y;
            t--;
        }
        while (l < qry[i].l) {
            res -= (w[ddd[type[l]]] - w[ddd[type[l]] - 1]) * val[type[l]];
            ddd[type[l++]]--;
        }
        while (l > qry[i].l) {
            ddd[type[--l]]++;
            res += (w[ddd[type[l]]] - w[ddd[type[l]] - 1]) * val[type[l]];
        }
        while (r < qry[i].r) {
            ddd[type[++r]]++;
            res += (w[ddd[type[r]]] - w[ddd[type[r]] - 1]) * val[type[r]];
        }
        while (r > qry[i].r) {
            res -= (w[ddd[type[r]]] - w[ddd[type[r]] - 1]) * val[type[r]];
            ddd[type[r--]]--;
        }
        *qry[i].p = res;
    }
    for (int i = 1; i <= rq; i++) printf("%d\n", ans[i]);
    return 0;
}