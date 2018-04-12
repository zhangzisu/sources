#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int MAXN = 110;
const double EPS = 1e-7;
double R[MAXN][MAXN], M[MAXN][MAXN];
int n, m;
inline void swap(int i, int j) {
    for (int k = 1; k <= n + 1; k++) std::swap(M[i][k], M[j][k]);
}
inline void Gauss() {
    for (int i = 1; i <= n; i++) {
        int max = i;
        for (int j = i + 1; j <= n; j++)
            if (fabs(M[j][i]) > fabs(M[max][i])) max = j;
        if (i != max) swap(max, i);
        if (fabs(M[i][i]) < EPS) continue;
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            double tmp = M[j][i] / M[i][i];
            for (int k = 1; k <= n + 1; k++) M[j][k] -= M[i][k] * tmp;
        }
    }
}
int main() {
    while (~scanf("%d%d", &n, &m)) {
        memset(R, 0, sizeof(R));
        memset(M, 0, sizeof(M));
        for (int i = 1; i <= m; i++) {
            int x, y;
            double r;
            scanf("%d%d%lf", &x, &y, &r);
            R[x][y] += 1. / r;
            R[y][x] += 1. / r;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j) continue;
                M[i][j] = -R[i][j];
                M[i][i] += R[i][j];
            }
        }
        M[1][n + 1] = 1;
        M[n][n + 1] = -1;
        M[n][n] += 1;
        Gauss();
        printf("%.2f\n", M[1][n + 1] / M[1][1]);
    }
    return 0;
}