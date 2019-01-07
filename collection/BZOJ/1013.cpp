#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 110
#define EPS 1e-6
int n;
double tmp[MAXN], Matrix[MAXN][MAXN];
inline void swap(int i, int j) {
    for (int k = 1; k <= n + 1; k++) std::swap(Matrix[i][k], Matrix[j][k]);
}
inline void Gauss() {
    for (int i = 1; i <= n; i++) {
        int max = i;
        for (int j = i + 1; j <= n; j++)
            if (fabs(Matrix[j][i]) > fabs(Matrix[max][i])) max = j;
        if (max != i) swap(i, max);
        if (fabs(Matrix[i][i]) <= EPS) continue;
        for (int j = 1; j <= n; j++) {
            if (j == i) continue;
            double t = Matrix[j][i] / Matrix[i][i];
            for (int k = i; k <= n + 1; k++) Matrix[j][k] -= Matrix[i][k] * t;
        }
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lf", &tmp[i]);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            double t;
            scanf("%lf", &t);
            Matrix[i][j] = 2 * (t - tmp[j]);
            Matrix[i][n + 1] += t * t - tmp[j] * tmp[j];
        }
    }
    Gauss();
    for (int i = 1; i <= n; i++) printf("%.3lf%c", Matrix[i][n + 1] / Matrix[i][i], " \n"[i == n]);
    return 0;
}