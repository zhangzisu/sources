#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <stack>

#define MAXN 100010
#define MAXM 200010
int n, m, l, p[MAXN], id[MAXN], len[MAXN];
int head[MAXN], next[MAXM], from[MAXM], to[MAXM], val[MAXM], tot = 1;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, from[tot] = u, val[tot] = w, head[u] = tot++;
}
int dis[MAXN], sid[MAXN], ins[MAXN], inq[MAXN];
std::queue<int> Q;
std::stack<int> S;
struct line {
    int l, e;
    inline friend bool operator<(const line &a, const line &b) {
        return a.l > b.l;
    }
    inline line(int l, int e) : l(l), e(e) {}
};
std::priority_queue<line> T;

inline void spfa(int s, int t, int D) {
    Q.push(s);
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        inq[x] = 0;
        for (int i = head[x]; i; i = next[i]) {
            if (i == D) continue;
            if (id[to[i]] >= id[t]) {
                if (!ins[to[i]])
                    S.push(to[i]), sid[to[i]] = dis[x] + val[i], ins[to[i]] = 1;
                else
                    sid[to[i]] = std::min(sid[to[i]], dis[x] + val[i]);
            } else if (dis[x] + val[i] < dis[to[i]]) {
                dis[to[i]] = dis[x] + val[i];
                if (!inq[to[i]])
                    Q.push(to[i]);
            }
        }
    }
    while (S.size()) T.push(line(sid[S.top()] + len[S.top()], id[S.top()])), ins[S.top()] = 0, S.pop();
}

int main() {
    scanf("%d%d%d", &n, &m, &l);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        $(x, y, z);
    }
    id[1] = 1;
    for (int i = 1; i <= l; i++) {
        scanf("%d", &p[i]);
        id[to[p[i]]] = i + 1;
    }
    for (int i = l; i; i--) len[from[p[i]]] = len[to[p[i]]] + val[p[i]];
    memset(dis, 0x3F, sizeof(dis));
    dis[1] = 0;
    for (int i = 1; i <= l; i++) {
        int u = from[p[i]];
        int v = to[p[i]];
        spfa(u, v, p[i]);
        // puts("DDD #2");
        // for (int i = 1; i <= n; i++) printf("%d ", dis[i]);
        // puts("");
        // puts("DDD #3");
        // for (int i = 1; i <= n; i++) printf("%d ", sid[i]);
        // puts("");
        while (T.size() && T.top().e < id[v])
            T.pop();
        if (T.empty())
            puts("-1");
        else
            printf("%d\n", T.top().l);
        dis[v] = dis[u] + val[p[i]];
    }
    return 0;
}