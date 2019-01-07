#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 100010
#define MAXK 200
int n, k, f[MAXK][MAXN], Q[MAXN], H, T;
std::vector<int> pi;
int main() {
    scanf("%d%d", &n, &k);
    memset(f[0], 0x3F, sizeof(f[0]));
    f[0][0] = 0;
    for (int i = 1; i <= k; i++) {
        int l, r, len;
        scanf("%d%d", &l, &r);
        len = r - l;
        memcpy(f[i], f[i - 1], sizeof(f[i]));
        H = 0;
        T = -1;
        for (int j = 0; j <= r; j++) {
            if (j <= n) {
                while (H <= T && f[i - 1][j] < f[i - 1][Q[T]]) T--;
                Q[++T] = j;
            }
            while (H <= T && Q[H] < j - len) H++;
            if (H <= T) f[i][j] = std::min(f[i][j], f[i - 1][Q[H]] + 2);
        }
        H = 0;
        T = -1;
        for (int j = r; ~j; j--) {
            if (r - j <= n) {
                while (H <= T && f[i - 1][r - j] < f[i - 1][Q[T]]) T--;
                Q[++T] = r - j;
            }
            while (H <= T && Q[H] < r - j - len) H++;
            if (H <= T) f[i][j] = std::min(f[i][j], f[i - 1][Q[H]] + 1);
        }
    }
    if (f[k][n] == 0x3F3F3F3F)
        puts("Hungry");
    else
        printf("Full\n%d\n", f[k][n]);
    return 0;
}