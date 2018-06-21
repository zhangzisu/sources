#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
int a[4], b[4], rank[4], buf[100][100];
int head[5000], next[100000], to[100000], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
inline int get(int x, int y) { return (x - 1) * 50 + y; }
std::queue<int> Q;
int vis[5000], inq[5000], col[5000];
void bfs() {
    Q.push(1);
    inq[1] = 1;
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        int d[4];
        memset(d, 0, sizeof(d));
        for (int i = head[x]; ~i; i = next[i])
            if (vis[to[i]]) d[col[to[i]]] = 1;
        std::sort(rank, rank + 4, [](int x, int y) { return a[x] < a[y]; });
        if (!a[rank[3]]) {
            for (int i = 3; ~i; i--) {
                if (!d[rank[i]]) {
                    vis[x] = 1;
                    a[col[x] = rank[i]]--;
                    goto ok;
                }
            }
        }
        vis[x] = 1;
        col[x] = rank[0];
    ok:;
        for (int i = head[x]; ~i; i = next[i]) {
            if (!vis[to[i]] && !inq[to[i]]) {
                inq[to[i]] = 1;
                Q.push(to[i]);
            }
        }
    }
}
int main() {
    scanf("%d%d%d%d", &a[0], &a[1], &a[2], &a[3]);
    memset(head, -1, sizeof(head));
    rank[0] = 0, rank[1] = 1, rank[2] = 2, rank[3] = 3;
    for (int i = 1; i < 50; i++) {
        for (int j = 1; j <= 50; j++) {
            $(get(i, j), get(i + 1, j));
        }
    }
    for (int i = 1; i <= 50; i++) {
        for (int j = 1; j < 50; j++) {
            $(get(i, j), get(i, j + 1));
        }
    }
    bfs();
    for (int i = 1; i <= 50; i++) {
        for (int j = 1; j <= 50; j++) {
            putchar('A' + col[get(i, j)]);
        }
        putchar(10);
    }
    return 0;
}