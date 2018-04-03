#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#define MAXN 110
#define INF 0x3F3F3F3F
int head[MAXN], to[MAXN << 1], pa[MAXN << 1], val[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, pa[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, pa[tot] = w, head[v] = tot++;
}
int vis[MAXN], size[MAXN], f[MAXN], fa[MAXN], deep[MAXN], dis[MAXN];
int Process(int x, int fa, int n) {
    size[x] = 1;
    int ret = 0, tmp, i;
    for (i = head[x]; ~i; i = next[i])
        if (to[i] != fa && !vis[to[i]]) {
            tmp = Process(to[i], x, n);
            size[x] += size[to[i]];
            f[x] = std::max(f[x], size[to[i]]);
            if (f[tmp] < f[ret]) ret = tmp;
        }
    return (f[x] = std::max(f[x], n - size[x])) < f[ret] ? x : ret;
}
std::deque<int> Q, P;
inline void Initialization() { Q.clear(), P.clear(); }
int n, m, l, r, x, y, dat[MAXN], now[MAXN];
bool bfs(int rt) {
    Initialization();
    Q.push_back(rt);
    deep[rt] = 1;
    int boom = MAXN - 1;
    while (Q.size()) {
        int x = Q.front();
        Q.pop_front();
        if (deep[x] > r) break;
        if (deep[x] <= l)
            while (boom >= l - deep[x]) {
                while (P.size() && dis[P.back()] <= dis[now[boom]]) P.pop_back();
                P.push_back(now[boom--]);
            }
        while (P.size() && dis[P.front()] > r - deep[x]) P.pop_front();
        if (P.size() && dis[P.front()] + dis[x] >= 0) {
            ::x = x;
            ::y = P.front();
            return 1;
        }
        for (int i = head[x]; ~i; i = next[i]) {
            if (vis[to[i]] || to[i] == fa[x]) continue;
            fa[to[i]] = x;
            deep[to[i]] = deep[x] + 1;
            dis[to[i]] = dis[x] + val[i];
            Q.push_back(to[i]);
        }
    }
    while (Q.size()) {
        int x = Q.front();
        Q.pop_front();
        if (dis[x] > dis[now[deep[x]]]) now[deep[x]] = x;
        for (int i = head[x]; ~i; i = next[i]) {
            if (vis[to[i]] || to[i] == fa[x]) continue;
            Q.push_back(to[i]);
        }
    }
    return 0;
}
void clear(int rt) {
    Initialization();
    Q.push_back(rt);
    while (Q.size()) {
        int x = Q.front();
        Q.pop_front();
        now[deep[x]] = 0;
        for (int i = head[x]; ~i; i = next[i]) {
            if (vis[to[i]] || to[i] == fa[x]) continue;
            fa[to[i]] = x;
            Q.push_back(to[i]);
        }
    }
}
bool Solve(int x, int n) {
    vis[x] = 1;
    Process(x, 0, n);
    bool flag = 0;
    dis[now[0] = x] = 0;
    for (int i = head[x]; ~i; i = next[i])
        if (!vis[to[i]] && (dis[to[i]] = val[i], flag |= bfs(to[i]))) break;
    for (int i = head[x]; ~i; i = next[i])
        if (!vis[to[i]]) clear(to[i]);
    now[0] = 0;
    if (flag) return 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (!vis[to[i]]) {
            if (Solve(Process(to[i], x, size[to[i]]), size[to[i]])) return 1;
        }
    }
    return 0;
}
inline bool check(int mid) {
    for (int i = 0; i < tot; i++) val[i] = pa[i] >= mid ? 1 : -1;
    memset(vis, 0, sizeof(vis));
    return Solve(Process(1, 0, n), n);
}
int main() {
    freopen("in.txt", "r", stdin);
    memset(head, -1, sizeof(head)), f[0] = INF, dis[0] = -INF;
    scanf("%d%d%d", &n, &l, &r);
    for (int i = 1, u, v, w; i < n; i++) scanf("%d%d%d", &u, &v, &w), $(u, v, w), dat[++m] = w;
    dat[++m] = 0;
    std::sort(dat + 1, dat + m + 1);
    m = std::unique(dat + 1, dat + m + 1) - dat - 1;
    register int l = 1, r = m, mid;
    int ansX = -1, ansY = -1;
    while (l <= r) {
        memset(now, 0, sizeof(now));
        memset(dis, 0, sizeof(dis));
        dis[0] = -INF;
        mid = (l + r) >> 1;
        if (check(dat[mid]))
            ansX = x, ansY = y, l = mid + 1;
        else
            r = mid - 1;
    }
    printf("%d %d\n", ansX, ansY);
    return 0;
}