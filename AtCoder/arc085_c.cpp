#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 110
#define MAXM 110110
int head[MAXN], to[MAXM], cap[MAXM], next[MAXM], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, cap[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, cap[tot] = 0, head[v] = tot++;
}
int level[MAXN];
inline void Dinic();
int main() {
    //
    return 0;
}