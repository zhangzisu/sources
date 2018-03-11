#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
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
int ch[MAXN][2], fuck[MAXN], cnt = 0;
inline void insert(std::string &s, int pos) {
    int p = 1, d;
    for (int i = 0; i < (int)s.length(); i++) {
        if (!ch[p][d = s[i] ^ 'a']) ch[p][d] = ++cnt;
        p = ch[p][d];
    }
    fuck[p] = pos;
}
int first[MAXN], last[MAXN], dfsclk = 0;
inline void dfs(int x) {
    first[x] = last[x] = ++dfsclk;
    if (ch[x][0]) dfs(ch[x][0]), last[x] = std::max(last[x], last[ch[x][0]]);
    if (ch[x][1]) dfs(ch[x][1]), last[x] = std::max(last[x], last[ch[x][1]]);
}
int n, m, q, type[MAXN], val[MAXN], w[MAXN], ans[MAXN];
std::string s;
int main() {
    std::cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> s;
        insert(s, i);
    }
    for (int i = 1; i <= n; i++) std::cin >> type[i];
    for (int i = 1; i <= m; i++) std::cin >> val[i];
    for (int i = 1; i <= n; i++) std::cin >> w[i];
    dfsclk = 0;
    int x, y;
    while (q--) {
        std::cin >> x;
        if (x == 1) {
            std::cin >> s;
            rq++;
            qs++;
            int p = 1;
            for (int i = 0; i < (int)s.length(); i++) p = ch[p][s[i] ^ 'a'];
            if (!p) {
                qs--;
                ans[rq] = 0;
            } else {
                qry[qs] = {first[p], last[p], dfsclk, ans + rq};
            }
        } else {
            std::cin >> x >> y;
            mdf[++ms] = {x, y};
            ++dfsclk;
        }
    }
    std::sort(qry + 1, qry + qs + 1);
    return 0;
}