#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, k, sa[MAXN], rank[MAXN], h[MAXN], height[MAXN], tmp[MAXN];
char buf[MAXN];
inline int cmp(int x, int y) {
    if (rank[x] != rank[y]) {
        return rank[x] < rank[y];
    } else {
        int rx = x + k <= n ? rank[x + k] : -1;
        int ry = y + k <= n ? rank[y + k] : -1;
        return rx < ry;
    }
}
inline void build_sa() {
    for (int i = 1; i <= n; i++) sa[i] = i, rank[i] = buf[i] - 'a' + 1;
    k = 0;
    std::sort(sa + 1, sa + n + 1, cmp);
    for (k = 1; k <= n; k <<= 1) {
        std::sort(sa + 1, sa + n + 1, cmp);
        tmp[sa[1]] = 1;
        for (int i = 2; i <= n; i++) tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        for (int i = 1; i <= n; i++) rank[i] = tmp[i];
    }
    for (int i = 1; i <= n; i++) rank[sa[i]] = i;
    for (int i = 1, j, k = 0; i <= n; h[rank[i++]] = k)
        for (k ? k-- : 0, j = sa[rank[i] - 1]; buf[i + k] == buf[j + k]; k++)
            ;
    for (int i = 1; i <= n; i++) height[i] = h[sa[i]];
}
int main() {
    scanf("%s", buf + 1);
    n = strlen(buf + 1);
    build_sa();
    for (int i = 1; i <= n; i++) printf("%d ", sa[i]);
    puts("");
    for (int i = 2; i <= n; i++) printf("%d ", h[i]);
    puts("");
    return 0;
}