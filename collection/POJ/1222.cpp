#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int n = 5, m = 6;
int t, a[n][m], g[30][31];
inline int $(int i, int j) { return i * m + j; }
inline void swap(int i, int j) {
    for (int k = 0; k < 31; k++) std::swap(g[i][k], g[j][k]);
}

inline void Gauss() {
    for (int i = 0; i < 30; i++) {
        int max = i;
        for (int j = i + 1; j < 30; j++)
            if (g[j][i] > g[max][i]) max = j;
        swap(i, max);
        if (!g[i][i]) continue;
        for (int j = 0; j < 30; j++) {
            if (j == i || !g[j][i]) continue;
            for (int k = i; k < 31; k++) g[j][k] ^= g[i][k];
        }
    }
}
int main() {
    scanf("%d", &t);
    for (int _ = 1; _ <= t; _++) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) scanf("%d", &a[i][j]);
        memset(g, 0, sizeof(g));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                g[$(i, j)][30] = a[i][j];
                g[$(i, j)][$(i, j)] = 1;
                for (int k = -1; k <= 1; k++) {
                    for (int l = -1; l <= 1; l++) {
                        if (k && l) continue;
                        int I = i + k;
                        int J = j + l;
                        if (I < 0 || I >= n || J < 0 || J >= m) continue;
                        g[$(i, j)][$(I, J)] = 1;
                    }
                }
            }
        }
        Gauss();
        printf("PUZZLE #%d\n", _);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) printf("%d%c", g[$(i, j)][30], " \n"[j == m - 1]);
    }
    return 0;
}