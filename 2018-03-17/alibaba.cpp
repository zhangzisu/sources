#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int f0, f1, f2, a1, a2, a3, p;
struct Matrix {
    int d[3][3];
    inline Matrix() {
        memset(d, 0, sizeof(d));
    }
    inline friend Matrix operator*(const Matrix &a, const Matrix &b) {
        Matrix ret;
        for (int k = 0; k < 3; k++)
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    (ret.d[i][j] += 1LL * a.d[i][k] * b.d[k][j] % p) %= p;
        return ret;
    }
};
char buf[102400];
int n[102400], N;

int main() {
#ifndef DEBUG
    freopen("alibaba.in", "r", stdin);
    freopen("alibaba.out", "w", stdout);
#endif
    scanf("%d%d%d%d%d%d%d", &f0, &f1, &f2, &a1, &a2, &a3, &p);
    scanf("%s", buf + 1);
    N = strlen(buf + 1);
    if (N == 1 && ((buf[1] ^ 48) < 3)) {
        switch (buf[1] ^ 48) {
            case 0:
                printf("%d\n", f0);
                break;
            case 1:
                printf("%d\n", f1);
                break;
            case 2:
                printf("%d\n", f2);
                break;
        }
        return 0;
    }
    for (int i = 1; i <= N; i++) n[i] = buf[N - i + 1] ^ 48;
    n[1] -= 2;
    for (int i = 2; i <= N; i++) {
        if (n[i - 1] < 0) n[i]--, n[i - 1] += 10;
        if (i == N && !n[i]) N--;
    }
    Matrix a, b, c;
    a.d[0][0] = a1;
    a.d[0][1] = a2;
    a.d[0][2] = a3;
    a.d[1][0] = 1;
    a.d[1][1] = 0;
    a.d[1][2] = 0;
    a.d[2][0] = 0;
    a.d[2][1] = 1;
    a.d[2][2] = 0;

    b.d[0][0] = f2;
    b.d[0][1] = 0;
    b.d[0][2] = 0;
    b.d[1][0] = f1;
    b.d[1][1] = 0;
    b.d[1][2] = 0;
    b.d[2][0] = f0;
    b.d[2][1] = 0;
    b.d[2][2] = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= n[i]; j++) b = a * b;
		c = a;
        for (int j = 1; j <= 9; j++) a = c * a;
    }

    printf("%d\n", b.d[0][0]);
#ifndef DEBUG
    fclose(stdin);
    fclose(stdout);
#endif
}
