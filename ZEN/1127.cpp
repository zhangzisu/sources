#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 310
int n, m;
char str[MAXN][MAXN];
int bd[MAXN][MAXN];
double Matrix[MAXN][MAXN], _2[MAXN];
inline double kmp(int x, int y) {
    int v = 0;
    for (int i = 0; i < m; i++) {
        while (v && str[x][v + 1] != str[y][i + 1]) v = bd[x][v];
        if (str[x][v + 1] == str[y][i + 1]) v++;
    }
    double ret = 0;
    while (v) ret += _2[m - v], v = bd[x][v];
    return ret;
}
inline void swap(int x, int y) {
    for (int i = 1; i <= n + 1; i++) std::swap(Matrix[x][i], Matrix[y][i]);
}
inline void Gauss() {
    for (int i = 1; i <= n; i++) {
        int max = i;
        for (int j = i + 1; j <= n; j++)
            if (std::abs(Matrix[j][i]) > std::abs(Matrix[max][i])) max = j;
        if (max != i) swap(i, max);
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            double tmp = Matrix[j][i] / Matrix[i][i];
            for (int k = i; k <= n + 1; k++) Matrix[j][k] -= Matrix[i][k] * tmp;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    _2[1] = 0.5;
    for (int i = 2; i <= m; i++) _2[i] = _2[i - 1] * 0.5;

    for (int i = 1; i <= n; i++) {
        scanf("%s", str[i] + 1);
        for (int j = 1; j <= m; j++) {
            int v = bd[i][j];
            while (v && str[i][v + 1] != str[i][j + 1]) v = bd[i][v];
            bd[i][j + 1] = str[i][v + 1] == str[i][j + 1] ? v + 1 : 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            Matrix[i][j] = kmp(i, j);
            Matrix[i][j] += (i == j);
        }
    }
    for (int i = 1; i <= n; i++) Matrix[n + 1][i] = 1, Matrix[i][n + 1] = -1;
    Matrix[n + 1][n + 2] = 1, n++;
    Gauss();
    for (int i = 1; i <= n; i++) Matrix[i][n + 1] /= Matrix[i][i], Matrix[i][i] = 1;
    // puts("PAG!PAG!PAG!");
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n + 1; j++) {
    //         printf("%f ", Matrix[i][j]);
    //     }
    //     puts("");
    // }
    // puts("PAG!PAG!PAG!");
    for (int i = 1; i < n; i++) printf("%.10f\n", Matrix[i][n + 1]);
    return 0;
}