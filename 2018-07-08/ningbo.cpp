#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int n, m, p, f[12];
inline void up(int& x, int y) {
    if ((x += y) >= p) x -= p;
}

struct Matrix {
    int **val, size;
    inline Matrix(int s = 0) {
        size = s;
        val = (int**)calloc(size, sizeof(int*));
        for (int i = 0; i < size; i++) val[i] = (int*)calloc(size, sizeof(int));
    }
    inline Matrix(const Matrix& arg) {
        size = arg.size;
        val = (int**)calloc(size, sizeof(int*));
        for (int i = 0; i < size; i++) val[i] = (int*)calloc(size, sizeof(int));
        for (int i = 0; i < size; i++) memcpy(val[i], arg.val[i], sizeof(int) * size);
    }
    inline int* operator[](int index) {
        return val[index];
    }
    inline void print() {
        puts(">>> Matrix");
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) printf("%10d", val[i][j]);
            puts("");
        }
    }
    inline friend Matrix operator*(Matrix a, Matrix b) {
        Matrix c(a.size);
        for (int i = 0; i < a.size; i++)
            for (int j = 0; j < a.size; j++)
                for (int k = 0; k < a.size; k++)
                    c[i][j] = (1LL * a[i][k] * b[k][j] % p + c[i][j]) % p;
        return c;
    }
    inline void operator=(Matrix arg) {
        size = arg.size;
        val = (int**)calloc(size, sizeof(int*));
        for (int i = 0; i < size; i++) val[i] = (int*)calloc(size, sizeof(int));
        for (int i = 0; i < size; i++) memcpy(val[i], arg.val[i], sizeof(int) * size);
    }
} trans[1010], all, init;

int main() {
    scanf("%d%d%d", &n, &m, &p);
    // if (n < p) {
    //     f[1] = 1;
    //     for (register int i = 1; i < n; i++) {
    //         for (register int j = m; j >= 1; j--) {
    //             if (!f[j]) continue;
    //             up(f[j + 1], 1LL * f[j] * (i + 1 - 2 * j) % p);
    //             f[j] = 2LL * f[j] * j % p;
    //         }
    //     }
    //     printf("%d\n", f[m]);
    //     return 0;
    // }
    init = Matrix(m);
    init[0][0] = 1;
    for (int i = 1; i <= p; i++) {
        trans[i] = Matrix(m);
        for (int j = 1; j <= m; j++) {
            trans[i][j - 1][j - 1] = 2 * j % p;
            if (j < m) trans[i][j - 1][j] = (i + 1 - 2 * j) % p;
        }
    }
    all = trans[1];
    for (int i = 2; i <= p; i++) all = all * trans[i];
    int count = (n - 1) / p;
    int rest = (n - 1) % p;
    for (; count; count >>= 1) {
        if (count & 1) init = init * all;
        all = all * all;
    }
    for (int i = 1; i <= rest; i++) init = init * trans[i];
    printf("%d\n", init[0][m - 1]);
    return 0;
}