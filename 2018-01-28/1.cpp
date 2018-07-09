#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 500010
int n, use[MAXN], tim, ret = 0x3F3F3F3F;
int vis[MAXN << 1], head[MAXN << 1], to[MAXN << 1], val[MAXN << 1], next[MAXN << 1], tot;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
void dfs(int x) {
    use[x] = tim;
    for (int i = head[x]; ~i; i = next[i])
        if (use[to[i]] != tim) dfs(to[i]);
}
int getEdge(int x) { return head[x]; }
int nans, fail;
void DFS(int x, int w) {
    if (fail) return;
    if (x <= n)
        nans += w;
    else
        nans -= w;
    use[x] = tim;
    for (int i = head[x]; ~i; i = next[i]) {
        if (vis[i] == tim) continue;
        if (use[to[i]] == tim) return void(fail = 1);
        vis[i] = vis[i ^ 1] = tim;
        DFS(to[i], val[i]);
    }
}
int main() {
    scanf("%d%*d", &n);
    memset(head, -1, sizeof(head));
    //if (n <= 10) return puts("NO"), 0;
    for (int i = 1; i <= n << 1; i++) {
        int a, b, c, d, e;
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
        $(b + n * a, d + n * c, e);
    }
    std::bitset<700000> ans, res1, res2;
    ans.set(350000);
    for (int i = 1; i <= n << 1; i++) {
        if (use[i]) continue;
        ++tim;
        dfs(i);
        int x = getEdge(i);
        vis[x] = vis[x ^ 1] = ++tim;
        nans = fail = 0;
        DFS(to[x], val[x]);
        if (fail)
            res1 = std::bitset<700000>();
        else {
            printf("%d\n", nans);
            if (nans < 0)
                res1 = ans << -nans;
            else
                res1 = ans >> nans;
        }
        x ^= 1;
        vis[x] = vis[x ^ 1] = ++tim;
        nans = fail = 0;
        DFS(to[x], val[x]);
        if (fail)
            res2 = std::bitset<700000>();
        else {
            printf("%d\n", nans);
            if (nans < 0)
                res2 = ans << -nans;
            else
                res2 = ans >> nans;
        }
        ans = res1 | res2;
    }
    if (ans.none()) return puts("NO"), 0;
    for (int i = 0; i < 700000; i++)
        if (ans[i]) ret = std::min(ret, std::abs(350000 - i));
    //assert(ret);
    printf("YES\n%d\n", ret);
    return 0;
}