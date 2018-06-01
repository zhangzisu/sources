#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#define MAXN 100010
#define MAXM 500010
#define INF 0x3F3F3F3F
int head[MAXN], to[MAXM], cap[MAXM], cost[MAXM], next[MAXM], tot = 0;
inline void $(int u, int v, int w, int c) {
    next[tot] = head[u], to[tot] = v, cap[tot] = w, cost[tot] = c, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, cap[tot] = 0, cost[tot] = -c, head[v] = tot++;
}
int n, m, s, t;
std::deque<int> Q;
int vis[MAXN], dis[MAXN];
inline bool SPFA() {
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x3F, sizeof(dis));
    dis[t] = 0, vis[t] = 1;
    Q.push_back(t);
    while (Q.size()) {
        int x = Q.front();
        Q.pop_front();
        for (int i = head[x]; ~i; i = next[i]) {
            if (cap[i ^ 1] && dis[to[i]] > dis[x] - cost[i]) {
                dis[to[i]] = dis[x] - cost[i];
                if (!vis[to[i]]) {
                    vis[to[i]] = 1;
                    if (Q.size() && dis[to[i]] < dis[Q.front()])
                        Q.push_front(to[i]);
                    else
                        Q.push_back(to[i]);
                }
            }
        }
        vis[x] = 0;
    }
    return dis[s] < INF;
}
int ans;
int dfs(int x, int flow) {
    vis[x] = 1;
    if (x == t) return flow;
    int ret = 0, tmp;
    for (int i = head[x]; ~i; i = next[i]) {
        if (!vis[to[i]] && cap[i] && dis[x] == dis[to[i]] + cost[i]) {
            tmp = dfs(to[i], std::min(flow, cap[i]));
            ans += tmp * cost[i];
            cap[i] -= tmp, cap[i ^ 1] += tmp;
            ret += tmp, flow -= tmp;
            if (!flow) break;
        }
    }
    return ret;
}
inline int cf() {
    int ret = 0;
    while (SPFA()) {
        do {
            memset(vis, 0, sizeof(vis));
            ret += dfs(s, INF);
        } while (vis[t]);
    }
    return ret;
}
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    s = 1, t = n;
    for (int i = 1; i <= m; i++) {
        int u, v, w, c;
        scanf("%d%d%d%d", &u, &v, &w, &c);
        $(u, v, w, c);
    }
    printf("%d ", cf());
    printf("%d\n", ans);
    return 0;
}