#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <queue>
const int MAXV = 400010;
const int MAXE = 4000010;
int n, m, r, b, cx, cy, s, t, ss, tt, flag, x[MAXV], y[MAXV], d[MAXV], lmt[MAXV], p[MAXV];
std::map<int, int> _x, _y;
const int INF = (~0u) >> 1;
int head[MAXV], cur[MAXV], to[MAXE], next[MAXE], cap[MAXE], in[MAXV], out[MAXV], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, cap[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, cap[tot] = 0, head[v] = tot++;
}
inline void $(int u, int v, int l, int r) {
    $(u, v, r - l);
    out[u] += l, in[v] += l;
}
std::queue<int> Q;
int level[MAXV];
inline bool BFS() {
    memset(level, 0, sizeof(level));
    memcpy(cur, head, sizeof(head));
    Q.push(ss);
    level[ss] = 1;
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        for (int i = head[x]; ~i; i = next[i]) {
            if (cap[i] && !level[to[i]]) {
                level[to[i]] = level[x] + 1;
                Q.push(to[i]);
            }
        }
    }
    return level[tt];
}
int DFS(int x, int flow) {
    if (x == tt || !flow) return flow;
    int tmp, ret = 0;
    for (int &i = cur[x]; ~i; i = next[i]) {
        if (level[x] + 1 == level[to[i]] && cap[i]) {
            tmp = DFS(to[i], std::min(flow, cap[i]));
            flow -= tmp, ret += tmp, cap[i] -= tmp, cap[i ^ 1] += tmp;
            if (!flow) return ret;
        }
    }
    return ret;
}
inline int Dinic() {
    int ret = 0;
    while (BFS()) ret += DFS(ss, INF);
    return ret;
}
int main() {
    scanf("%d%d%d%d", &n, &m, &r, &b);
    if (r < b) std::swap(r, b), flag = 1;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &x[i], &y[i]);
        _x[x[i]] = 1;
        _y[y[i]] = 1;
    }
    for (auto &t : _x) t.second = ++cx;
    for (auto &t : _y) t.second = ++cy;

    memset(head, -1, sizeof(head));
    s = cx + cy + 1;
    t = cx + cy + 2;
    ss = cx + cy + 3;
    tt = cx + cy + 4;

    for (int i = 1; i <= n; i++) {
        x[i] = _x[x[i]], y[i] = _y[y[i]] + cx;
        d[x[i]]++, d[y[i]]++;
        $(x[i], y[i], 0, 1);
        p[i] = tot - 2;
    }

    for (int i = 1; i <= cx + cy; i++) lmt[i] = d[i];
    for (int i = 1; i <= m; i++) {
        int t, l, d;
        scanf("%d%d%d", &t, &l, &d);
        if (t == 1) {
            if (!_x.count(l)) continue;
            l = _x[l];
            lmt[l] = std::min(lmt[l], d);
        } else {
            if (!_y.count(l)) continue;
            l = _y[l] + cx;
            lmt[l] = std::min(lmt[l], d);
        }
    }

    for (int i = 1; i <= cx; i++) {
        int l = ceil(1. * (d[i] - lmt[i]) / 2);
        int r = floor(1. * (d[i] + lmt[i]) / 2);
        if (l > r) {
            printf("-1\n");
            return 0;
        }
        $(s, i, l, r);
    }
    for (int i = cx + 1; i <= cx + cy; i++) {
        int l = ceil(1. * (d[i] - lmt[i]) / 2);
        int r = floor(1. * (d[i] + lmt[i]) / 2);
        if (l > r) {
            printf("-1\n");
            return 0;
        }
        $(i, t, l, r);
    }

    for (int i = 1; i <= t; i++) {
        if (in[i]) $(ss, i, in[i]);
        if (out[i]) $(i, tt, out[i]);
    }

    Dinic();
    $(t, s, INF);
    Dinic();
    for (int i = head[ss]; ~i; i = next[i])
        if (cap[i]) return puts("-1"), 0;
    int cr = cap[tot - 1];
    printf("%lld\n", 1LL * cr * r + 1LL * (n - cr) * b);
    for (int i = 1; i <= n; i++) {
        if (!cap[p[i]]) {
            putchar(flag ? 'b' : 'r');
        } else {
            putchar(flag ? 'r' : 'b');
        }
    }
    return 0;
}