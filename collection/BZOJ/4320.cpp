#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 19260
#define MAXM 19260
#define INF 0x3F3F3F3F
int head[MAXN], to[MAXM << 1], val[MAXM << 1], cap[MAXM << 1], next[MAXM << 1], tot = 0;
inline void $(int u, int v, int w, int c) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, cap[tot] = c, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = -w, cap[tot] = 0, head[v] = tot++;
}
int dis[MAXN], pre[MAXN], Q[MAXN], inq[MAXN], H, T, x;
int n, k, dat[MAXN << 1], l[MAXN], r[MAXN], N;
inline int fm(int x) { return x >= MAXN ? 0 : x; }
inline int spfa(int s, int t) {
    memset(dis, 0x80, sizeof(dis));
    memset(pre, -1, sizeof(pre));
    inq[s] = 1;
    dis[Q[H = T = 0] = s] = 0;
    while (H != fm(T + 1)) {
        inq[x = Q[H]] = 0;
        H = fm(H + 1);
        for (int i = head[x]; ~i; i = next[i]) {
            if (!cap[i]) continue;
            if (dis[x] + val[i] > dis[to[i]]) {
                dis[to[i]] = dis[x] + val[i];
                pre[to[i]] = i;
                if (!inq[to[i]]) {
                    inq[Q[T = fm(T + 1)] = to[i]] = 1;
                }
            }
        }
    }
    return ~pre[t];
}
inline int mcmf(int s, int t) {
    int ret = 0;
    while (spfa(s, t)) {
        int low = INF, now;
        for (now = t; ~pre[now]; now = to[pre[now] ^ 1]) low = std::min(low, cap[pre[now]]);
        ret += low * dis[t];
        for (now = t; ~pre[now]; now = to[pre[now] ^ 1]) cap[pre[now]] -= low, cap[pre[now] ^ 1] += low;
    }
    return ret;
}
int main() {
    scanf("%d%d", &n, &k);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &l[i], &r[i]);
        if (l[i] > r[i]) std::swap(l[i], r[i]);
        dat[++N] = l[i];
        dat[++N] = r[i];
    }
    std::sort(dat + 1, dat + N + 1);
    N = std::unique(dat + 1, dat + N + 1) - dat - 1;
    T = N + 1;
    $(0, 1, 0, k);
    $(N, T, 0, INF);
    for (int i = 1; i <= n; i++) {
        int x = std::lower_bound(dat + 1, dat + N + 1, l[i]) - dat;
        int y = std::lower_bound(dat + 1, dat + N + 1, r[i]) - dat;
        $(x, y, r[i] - l[i], 1);
    }
    for (int i = 1; i < N; i++) $(i, i + 1, 0, INF);
    printf("%d\n", mcmf(0, T));
    return 0;
}