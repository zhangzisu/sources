#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, m, c, s, t, dis[MAXN];
int u[MAXN], v[MAXN], w[MAXN];
int main() {
    scanf("%d%d%d", &n, &m, &c);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &u[i], &v[i], &w[i]);
    }
    scanf("%d%d", &s, &t);
    for (int i = 1; i <= n; i++) dis[i] = (s ^ i) * c;
    for (int _ = 1; _ <= m; _++)
        for (int i = 1; i <= m; i++) {
            dis[v[i]] = std::min(dis[v[i]], dis[u[i]] + w[i]);
            for (int j = 1; j <= n; j++) dis[j] = std::min(dis[j], dis[v[i]] + (v[i] ^ j) * c);
        }
    printf("%d\n", dis[t]);
    return 0;
}