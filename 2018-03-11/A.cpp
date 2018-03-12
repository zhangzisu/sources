#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000000
int k, n;
int vis[MAXN], val[MAXN], ver[MAXN], fa[MAXN], ans[100];
inline void BFS(int n) {
    register int H, T;
    H = T = 0;
    memset(vis, 0, sizeof(vis));
    vis[val[0] = 1] = 1, ver[0] = 1, fa[0] = -1;
    while (H <= T) {
        int top = H;
        H++;
        if (!val[top]) {
            H = top;
            T = 0;
            while (~H) {
                ans[++T] = ver[H];
                H = fa[H];
            }
            while (T) putchar(ans[T--] ^ 48);
            putchar(0xA);
            return;
        }
        if (!vis[val[top] * 10 % n]) {
            ++T;
            vis[val[T] = val[top] * 10 % n] = 1;
            ver[T] = 0;
            fa[T] = top;
        }
        if (!vis[(val[top] * 10 + 1) % n]) {
            ++T;
            vis[val[T] = (val[top] * 10 + 1) % n] = 1;
            ver[T] = 1;
            fa[T] = top;
        }
        if (T >= MAXN) break;
    }
    puts("BRAK");
    return;
}
int main() {
    scanf("%d%*d", &k);
    while (k--) {
        scanf("%d", &n);
        if (n == 1)
            puts("1");
        else
            BFS(n);
    }
    return 0;
}