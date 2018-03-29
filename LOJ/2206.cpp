#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 300010
int n, head[MAXN], next[MAXN], to[MAXN], tot;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}

int main() {
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        $(u, v);
    }
    return 0;
}