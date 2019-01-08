#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
int n, x1, x2, x3, a[6], b[6], c[6], A, B, C;
int f[2][MAXN][MAXN];
const int w[6] = {100, 50, 20, 10, 5, 1};
inline void up(int &x, const int &y) { x = std::min(x, y); }
int main() {
    scanf("%d%d%d", &x1, &x2, &x3);
    for (int i = 0; i < 6; i++) scanf("%d", &a[i]), A += w[i] * a[i];
    for (int i = 0; i < 6; i++) scanf("%d", &b[i]), B += w[i] * b[i];
    for (int i = 0; i < 6; i++) scanf("%d", &c[i]), C += w[i] * c[i];
    if (A - x1 + x3 < 0 || B - x2 + x1 < 0 || C - x3 + x2 < 0)
        return puts("impossible"), 0;
    n = A + B + C;
    memset(f[1], 0x3F, sizeof(f[0]));
    f[1][A][B] = 0;
    for (register int d = 0; d < 6; d++) {
        int(*F)[MAXN] = f[d & 1], (*G)[MAXN] = f[!(d & 1)];
        memset(F, 0x3F, sizeof(f[0]));
        for (register int x = 0; x <= n; x++)
            for (register int y = 0; y <= n - x; y++) {
                if (G[x][y] == 0x3F3F3F3F) continue;
                int z = n - x - y, &pr = G[x][y];
                for (register int i = 0; i <= a[d]; i++)
                    for (register int j = 0; j <= i; j++)
                        if (x >= w[d] * i)
                            up(F[x - w[d] * i][y + w[d] * j], pr + i);
                        else
                            break;
                for (register int i = 0; i <= b[d]; i++)
                    for (register int j = 0; j <= i; j++)
                        if (y >= w[d] * i)
                            up(F[x + w[d] * j][y - w[d] * i], pr + i);
                        else
                            break;
                for (register int i = 0; i <= c[d]; i++)
                    for (register int j = 0; j <= i; j++)
                        if (z >= w[d] * i)
                            up(F[x + w[d] * j][y + w[d] * (i - j)], pr + i);
                        else
                            break;
                for (register int i = 0; i <= a[d]; i++)
                    for (register int j = 0; j <= b[d]; j++)
                        if (x >= w[d] * i && y >= w[d] * j)
                            up(F[x - w[d] * i][y - w[d] * i], pr + i + j);
                        else
                            break;
                for (register int i = 0; i <= a[d]; i++)
                    for (register int j = 0; j <= c[d]; j++)
                        if (x >= w[d] * i && z >= w[d] * j)
                            up(F[x - w[d] * i][y + w[d] * (i + j)], pr + i + j);
                        else
                            break;
                for (register int i = 0; i <= b[d]; i++)
                    for (register int j = 0; j <= c[d]; j++)
                        if (y >= w[d] * i && z >= w[d] * j)
                            up(F[x + w[d] * (i + j)][y - w[d] * i], pr + i + j);
                        else
                            break;
            }
    }
    if (f[1][A - x1 + x3][B - x2 + x1] != 0x3F3F3F3F)
        printf("%d\n", f[1][A - x1 + x3][B - x2 + x1]);
    else
        puts("impossible");
    return 0;
}