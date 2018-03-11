#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 50010
int head[MAXN], to[MAXN << 2], val[MAXN << 2], next[MAXN << 2], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
}
int dis[MAXN], inq[MAXN], n;
std::queue<int> Q;
inline void SPFA(int s) {
    memset(dis, 0x80, sizeof(dis));
    Q.push(s);
    inq[s] = 1;
    dis[s] = 0;
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        inq[x] = 0;
        for (int i = head[x]; ~i; i = next[i]) {
            if (dis[to[i]] < dis[x] + val[i]) {
                dis[to[i]] = dis[x] + val[i];
                if (!inq[to[i]]) inq[to[i]] = 1, Q.push(to[i]);
            }
        }
    }
}
int main() {
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    for (int i = 1; i < MAXN; i++) $(i - 1, i, 0);
    for (int i = 1; i < MAXN; i++) $(i, i - 1, -1);
    while (n--) {
        int l, r, c;
        scanf("%d%d%d", &l, &r, &c);
        $(l, r + 1, c);
    }
    SPFA(0);
    printf("%d\n", dis[MAXN - 1]);
    return 0;
}