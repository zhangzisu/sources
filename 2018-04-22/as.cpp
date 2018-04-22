#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define MAXN 20
const int INF = (~0U) >> 1;
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
int n = $(), m = $();
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
std::pair<int, int> q[MAXN];
namespace cgc {
struct answer {
    int m0, m1;
    inline answer(int m0 = -1, int m1 = -1) : m0(m0), m1(m1){}
    inline void up(int x) {
        if (x >= m0)
            m1 = m0, m0 = x;
        else if (x >= m1)
            m1 = x;
    }
    inline void up(answer b) {
        up(b.m0);
        up(b.m1);
    }
} ans[MAXN];
int vis[MAXN], col[MAXN], clk;
std::set<int> S;
int tmp[MAXN], cnt = 0;
void dfs(int x, int c, int fa) {
    if (vis[x]) return;
    if (col[x] != c) return;
    tmp[++cnt] = x;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        dfs(to[i], c, x);
    }
}
inline int main() {
    if (n <= 2) return puts("-1"), 0;
    for (int i = 1; i <= m; i++) {
        if (q[i].first == 1) {
            if(vis[q[i].second])continue;
            cnt = 0;
            dfs(q[i].second, col[q[i].second], 0);
            S.clear();
            for (int j = 1; j <= cnt; j++) S.insert(tmp[j]);
            ans[q[i].second] = {n - 1, n - 1};
            vis[q[i].second] = 1;
            for (int j = head[q[i].second]; ~j; j = next[j]) {
                if (vis[to[j]]) continue;
                cnt = 0;
                dfs(to[j], col[to[j]], q[i].second);
                for (int k = 1; k <= cnt; k++) S.erase(tmp[k]);
                answer temp;
                auto x = S.end();
                if (S.size() == 1)
                    temp.m0 = *--x;
                else
                    temp.m0 = *--x, temp.m1 = *--x;
                ++clk;
                for (int k = 1; k <= cnt; k++) {
                    ans[tmp[k]].up(temp);
                    S.insert(tmp[k]);
                    col[tmp[k]] = clk;
                }
            }
        } else {
            printf("%d\n", ans[q[i].second].m1);
        }
    }
    return 0;
}
}  // namespace cgc
int main() {
    memset(head, -1, sizeof(head));
    for (int i = 1, u, v; i < n; i++) {
        $(u = $(), v = $());
    }
    for (int i = 1; i <= m; i++) q[i].first = $(), q[i].second = $();
    return cgc::main();
}