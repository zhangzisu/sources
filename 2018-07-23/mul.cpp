#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int MOD;
struct Matrix {
    int degree, data[31][31];
    inline Matrix(int degree = 0) : degree(degree) {
        memset(data, 0, sizeof(data));
    }
    inline int* operator[](int index) {
        return data[index];
    }
    inline void print() {
        printf("> Matrix %dx%d\n", degree, degree);
        for (int i = 0; i < degree; i++) {
            for (int j = 0; j < degree; j++) printf("%4d", data[i][j]);
            puts("");
        }
    }
    inline void operator=(Matrix other) {
        degree = other.degree;
        memcpy(data, other.data, sizeof(data));
    }
} tr[26];
inline void up(int& x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline Matrix mul(Matrix a, Matrix b) {
    assert(a.degree == b.degree);
    const int d = a.degree;
    Matrix c(d);
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            for (int k = 0; k < d; k++) {
                up(c[i][j], 1LL * a[i][k] * b[k][j] % MOD);
            }
        }
    }
    return c;
}
int n;
int main() {
    scanf("%d %d\n", &n, &MOD);
    Matrix a(n), b(n), c(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) scanf("%d", &a[i][j]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) scanf("%d", &b[i][j]);
    c = mul(a, b);
    c.print();
    return 0;
}