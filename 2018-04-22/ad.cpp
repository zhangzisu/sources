#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define MAXN 100010
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
namespace ckr {
int max1, max2, vis[MAXN];
inline void query(int x, int d = 0, int fa = 0) {
    d |= vis[x];
    if (d) {
        if (x >= max1)
            max2 = max1, max1 = x;
        else if (x >= max2)
            max2 = x;
    }
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        query(to[i], d, x);
    }
}
inline int main() {
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (u == 1) {
            vis[v] = 1;
        } else {
            max1 = max2 = -1;
            query(v);
            printf("%d\n", max2);
        }
    }
    return 0;
}
}  // namespace ckr
namespace jzm {
std::set<int> g;
inline int main() {
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        g.insert(0);
        g.insert(n + 1);
        if (u == 1) {
            g.insert(v);
        } else {
            int left = *--g.upper_bound(v);
            int right = *g.lower_bound(v);
            if (left == right) {
                printf("%d\n", n - 1);
            } else {
                int len = left + n - right + 1;
                if (len < 2) {
                    puts("-1");
                } else {
                    if (right < n)
                        printf("%d\n", n - 1);
                    else if (right <= n)
                        printf("%d\n", left);
                    else
                        printf("%d\n", left - 1);
                }
            }
        }
    }
    return 0;
}
}  // namespace jzm
std::pair<int, int> q[MAXN];

namespace xjp {
int ans[MAXN], vis[MAXN];
std::set<int> S;
int col[MAXN], id[MAXN], tmp[MAXN], t, cnt = 0, clk = 0;
void dfs(int x, int c) {
    if (vis[x]) return;
    col[++cnt] = c;
    id[cnt] = x;
    vis[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (vis[to[i]]) continue;
        dfs(to[i], c);
    }
}
inline int main(int split) {
    if (n <= 2) return puts("-1"), 0;
    for (int i = 1; i <= split; i++) vis[q[i].second] = 1, ans[q[i].second] = n - 1;
    for (int i = 1; i <= n; i++) S.insert(i);
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            dfs(i, ++clk);
        }
    for (int x = 1; x <= cnt; x++) {
        tmp[++t] = id[x];
        if (col[x] != col[x + 1]) {
            for (int i = 1; i <= t; i++) {
                S.erase(tmp[i]);
            }
            int temp = S.size() < 2u ? -1 : *----S.end();
            for (int i = 1; i <= t; i++) {
                ans[tmp[i]] = temp;
            }
            for (int i = 1; i <= t; i++) {
                S.insert(tmp[i]);
            }
        }
    }
    for (int i = split + 1; i <= m; i++) printf("%d\n", ans[q[i].second]);
    return 0;
}
}  // namespace xjp
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
            ans[q[i].second] = n - 1;
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
    bool flag = 1;
    for (int i = 1, u, v; i < n; i++) {
        $(u = $(), v = $());
        flag &= (u == v + 1) || (v == u + 1);
    }
    return ckr::main();
}