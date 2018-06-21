#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 1000010
typedef long long lnt;

struct state {
    int son[26], len, link;
    inline int& operator[](int index) { return son[index]; }
} sam[MAXN];
int cnt = 1, last = 1, pos[MAXN];
inline void extend(int c) {
    int p = last, q, np = ++cnt, nq;
    last = np;
    sam[np].len = sam[p].len + 1;
    for (; p && !sam[p][c]; p = sam[p].link) sam[p][c] = np;
    if (!p) return sam[np].link = 1, void();
    q = sam[p][c];
    if (sam[q].len == sam[p].len + 1) return sam[np].link = q, void();
    sam[nq = ++cnt] = state(sam[q]);
    sam[nq].len = sam[p].len + 1;
    for (; p && sam[p][c] == q; p = sam[p].link) sam[p][c] = nq;
    sam[np].link = sam[q].link = nq;
}
std::vector<int> next[MAXN];
int n, m, t, q[3000010], fa[MAXN][20], deep[MAXN], dfn[MAXN], dfsclk;
void dfs(int x) {
    dfn[x] = ++dfsclk;
    for (int i = 1; i < 20; i++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for (std::vector<int>::iterator _y = next[x].begin(); _y != next[x].end(); _y++) {
        int y = *_y;
        fa[y][0] = x, deep[y] = deep[x] + 1, dfs(y);
    }
}
char buf[MAXN];
int stk[MAXN], top;
inline int lca(int x, int y) {
    if (deep[x] < deep[y]) std::swap(x, y);
    int delta = deep[x] - deep[y];
    for (int i = 19; ~i; i--)
        if ((delta >> i) & 1) x = fa[x][i];
    for (int i = 19; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return x == y ? x : fa[x][0];
}
std::vector<int> nxt[MAXN];
lnt f[MAXN], size[MAXN];
void dp(int x) {
    for (std::vector<int>::iterator _y = nxt[x].begin(); _y != nxt[x].end(); _y++) {
        int y = *_y;
        dp(y);
        f[x] += size[x] * size[y];
        size[x] += size[y];
    }
}
inline int cmp(int a, int b) { return dfn[a] < dfn[b]; }
int main() {
    scanf("%d%d%s", &n, &m, buf + 1);
    std::reverse(buf + 1, buf + n + 1);
    for (int i = 1; i <= n; i++) extend(buf[i] - 'a'), pos[i] = last;
    std::reverse(pos + 1, pos + n + 1);
    for (int i = 2; i <= cnt; i++) next[sam[i].link].push_back(i);
    dfs(1);
    deep[0] = -1;
    while (m--) {
        scanf("%d", &t);
        for (int i = 1; i <= t; i++) scanf("%d", &q[i]), q[i] = pos[q[i]];
        std::sort(q + 1, q + t + 1, cmp);
        t = std::unique(q + 1, q + t + 1) - q - 1;
        int tt = t;
        stk[top = 1] = 0;

        for (int i = 1; i <= t; i++) {
            int x = q[i], lca = ::lca(stk[top], x);
            if (lca == stk[top]) {
                stk[++top] = x;
            } else {
                while (top >= 2 && deep[stk[top - 1]] >= deep[lca]) {
                    nxt[stk[top - 1]].push_back(stk[top]);
                    top--;
                }
                if (lca != stk[top]) {
                    nxt[lca].push_back(stk[top]);
                    stk[top] = lca;
                    q[++tt] = lca;
                }
                stk[++top] = x;
            }
        }
        while (top >= 2) nxt[stk[top - 1]].push_back(stk[top]), top--;
        for (int i = 1; i <= tt; i++) {
            size[q[i]] = i <= t;
            f[q[i]] = 0;
        }
        dp(0);
        lnt ans = 0;
        for (int i = 1; i <= tt; i++) {
            ans += f[q[i]] * sam[q[i]].len;
            nxt[q[i]].clear();
        }
        nxt[0].clear();
        printf("%lld\n", ans);
    }
    return 0;
}