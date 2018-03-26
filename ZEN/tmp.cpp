#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
using namespace std;

const int N = 303;
typedef long double DB;
const DB eps = 1E-10;

int n, m, fail[N][N];
DB A[N][N], B[N], mi[N];
char s[N][N];

inline void Swap(int x, int y) {
    for (int i = x; i <= n; i++) swap(A[x][i], A[y][i]);
    swap(B[x], B[y]);
}

inline DB Check(int x, int y) {
    DB ret = 0;
    int tot = 0;
    for (int i = 1; i <= m; i++) {
        while (tot && s[x][tot + 1] != s[y][i]) tot = fail[x][tot];
        if (s[x][tot + 1] == s[y][i]) ++tot;
    }
    while (tot) ret += mi[m - tot], tot = fail[x][tot];
    return ret;
}

inline void Gauss(int k) {
    int pos = k;
    DB Max = A[k][k], tmp;
    for (int i = k + 1; i <= n; i++)
        if (fabs(A[i][k]) > Max) Max = fabs(A[i][k]), pos = i;
    if (pos > k) Swap(k, pos);
    tmp = A[k][k];
    for (int i = k; i <= n; i++) A[k][i] /= tmp;
    B[k] /= tmp;
    if (k == n) return;
    for (int i = k + 1; i <= n; i++) {
        if (fabs(A[i][k]) <= eps) continue;
        tmp = A[i][k];
        B[i] -= B[k] * tmp;
        for (int j = k; j <= n; j++)
            A[i][j] -= A[k][j] * tmp;
    }
    Gauss(k + 1);
    for (int i = k + 1; i <= n; i++) B[k] -= B[i] * A[k][i];
}

int main() {
    cin >> n >> m;
    mi[1] = 0.5;
    for (int i = 2; i <= m; i++) mi[i] = mi[i - 1] / 2.00;
    for (int i = 1; i <= n; i++) {
        scanf("%s", s[i] + 1);
        for (int j = 1; j < m; j++) {
            int v = fail[i][j];
            while (v && s[i][v + 1] != s[i][j + 1]) v = fail[i][v];
            fail[i][j + 1] = s[i][v + 1] == s[i][j + 1] ? v + 1 : 0;
        }
    }

    // for(int i = 1;i <= n;i++){
    //     for(int j = 1;j <= m;j++){
    //         printf("%3d", fail[i][j]);
    //     }
    //     puts("");
    // }

    // puts("");

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         printf("%f ", (double)Check(i, j));
    //     }
    //     puts("");
    // }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            A[i][j] = Check(i, j) + (i == j ? 1.00 : 0.00);
    for (int i = 1; i <= n; i++) A[n + 1][i] = 1, A[i][n + 1] = -1;
    B[++n] = 1;
    Gauss(1);
    puts("DDD!DDD!DDD!");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            printf("%.12lf ", (double)(A[i][j]));
        printf("%.12lf\n", (double)(B[i]));
    }
    puts("DDD!DDD!DDD!");
    for (int i = 1; i < n; i++) printf("%.10lf\n", (double)(B[i]));
    return 0;
}