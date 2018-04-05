#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int n, x, v[MAXN], size[MAXN], f[MAXN][MAXN];
void dp(int x, int fa) {
    size[x] = 1;
    f[x][0] = ::x - v[x];
    static int tmp[MAXN];
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        dp(to[i], x);
        memset(tmp, -0x3F, sizeof(tmp));
        for (int j = 0; j <= size[x]; j++) {
            for (int k = 0; k <= size[to[i]]; k++) {
                tmp[j + k + 1] = std::max(tmp[j + k + 1], f[x][j] + f[to[i]][k]);
                if (f[to[i]][k] >= 0) tmp[j + k] = std::max(tmp[j + k], f[x][j]);
            }
        }
        size[x] += size[to[i]];
        memcpy(f[x], tmp, sizeof(tmp));
    }
}
int main() {
    memset(head, -1, sizeof(head));
    memset(f, -0x3F, sizeof(f));
    scanf("%d%d", &n, &x);
    for (int i = 1; i <= n; i++) scanf("%d", &v[i]);
    for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
    dp(1, 0);
    for (int i = 1; i < n; i++)
        if (f[1][i] >= 0) return printf("%d\n", i), 0;
    return puts("-1"), 0;
}