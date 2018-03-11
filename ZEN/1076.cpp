#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
const int INFL = 0x3F3F3F3F;
const int INF = 3000000;
#define MAXN 610
#define MAXM 800010
int n, p[MAXN];
int head[MAXN], to[MAXM], next[MAXM], tot = 0;
long long cap[MAXM], ans;
inline void $(int u, int v, long long w) {
    next[tot] = head[u], to[tot] = v, cap[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, cap[tot] = 0, head[v] = tot++;
    // printf("%d --%lld--> %d\n", u, w, v);
}

std::queue<int> Q;
int level[MAXN];
int BFS(int s, int t) {
    memset(level, 0, sizeof(level));
    level[s] = 1;
    Q.push(s);
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
    return level[t];
}

long long DFS(int s, int t, long long flow) {
    if (s == t || !flow) return flow;
    long long ret = 0, tmp;
    for (int i = head[s]; ~i; i = next[i]) {
        if (level[to[i]] != level[s] + 1) continue;
        if (cap[i] && (tmp = DFS(to[i], t, std::min(flow, cap[i])))) {
            ret += tmp, flow -= tmp, cap[i] -= tmp, cap[i ^ 1] += tmp;
            if (!tmp) break;
        }
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    memset(head, -1, sizeof(head));

    int s = n * 2 + 1, t = s + 1;
    for (int i = 1, x, y; i <= n; i++) {
        scanf("%d", &x);
        $(i + n, t, INF);
        while (x--) scanf("%d", &y), $(i, y + n, INFL);
    }

    for (int i = 1, p; i <= n; i++) {
        scanf("%d", &p);
        ans += INF - p;
        $(s, i, INF - p);
    }

    // printf("D:%lld\n", ans);
    while(BFS(s, t)){
        long long tmp = DFS(s, t, INFL);
        // printf("D:%lld\n", tmp);
        ans -= tmp;
    }
    printf("%lld\n", -ans);
    return 0;
}