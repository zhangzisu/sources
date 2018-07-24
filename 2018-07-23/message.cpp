#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int MOD;
struct Matrix {
    int degree, data[32][32];
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
} tr[32];
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
int n, k, len[32], zero[32];
char buf[32][200];
inline void build_trans(int level) {
    Matrix& val = tr[level];
    val = Matrix(n + 2);
    for (int i = 0; i < val.degree; i++) val[i][i] = 1;
    // val.print();
    for (int i = 4; i <= len[level]; i++) {
        if (isalpha(buf[level][i])) {
            int trans_id = buf[level][i] - 'A';
            up(zero[level], zero[trans_id]);
            val = mul(val, tr[trans_id]);
        } else {
            int number = buf[level][i] - '0';
            Matrix trans(n + 2);
            trans[n][n] = trans[n + 1][n + 1] = 1;
            trans[0][n] = 1;
            for (int i = 0; i < n; i++) {
                int next = (i * 10 + number) % n;
                up(trans[i][next], 1);
            }
            if (number) {
                up(trans[n + 1][number % n], 1);
            } else {
                up(zero[level], 1);
            }
            // printf("TRANS:\n");
            // trans.print();
            val = mul(val, trans);
        }
        // val.print();
    }
}
int main() {
#ifndef DEBUG
    freopen("message.in", "r", stdin);
    freopen("message.out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &MOD, &k);
    for (int i = 0; i < k; i++) {
        scanf("%s", buf[i] + 1);
        len[i] = strlen(buf[i] + 1);
    }
    for (int i = k - 1; ~i; i--) build_trans(i);
    Matrix init(n + 2);
    init[0][n + 1] = 1;
    Matrix ans = mul(init, tr[0]);
    int ret = zero[0];
    up(ret, ans[0][n]);
    up(ret, ans[0][0]);
    printf("%d\n", ret);
    return 0;
}