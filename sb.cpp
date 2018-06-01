#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#define INF 0x3F3F3F3F
bool vis[200001];
int dis[200001];
int n, m, s, t, ans = 0;
int tot = -1, to[200001], cap[200001], cost[200001], next[200001], head[200001];
inline void addedge(int x, int y, int z, int zz) {
    to[++tot] = y;
    cap[tot] = z;
    cost[tot] = zz;
    next[tot] = head[x];
    head[x] = tot;
}
std::deque<int> Q;
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
inline int dfs(int x, int flow) {
    vis[x] = 1;
    if (x == t) return flow;
    int ret = 0, tmp;
    vis[x] = 1;
    for (int k = head[x]; ~k; k = next[k])
        if (!vis[to[k]] && cap[k] && dis[x] - cost[k] == dis[to[k]]) {
            a = dfs(to[k], std::min(cap[k], flow - ret));
            if (a) ans += a * cost[k], cap[k] -= a, cap[k ^ 1] += a, ret += a;
            if (ret == flow) break;
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
    memset(next, -1, sizeof next);
    memset(head, -1, sizeof head);
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= m; i++) {
        int x, y, z, zz;
        scanf("%d%d%d%d", &x, &y, &z, &zz);
        addedge(x, y, z, zz);
        addedge(y, x, 0, -zz);
    }
    printf("%d ", cf());
    printf("%d", ans);
    return 0;
}