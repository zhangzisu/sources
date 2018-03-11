#include <algorithm>
#include <cstdio>
#include <cstring>
#define MOD 1000000007
struct martix {
    int m[2][2];
    inline martix() { memset(m, 0, sizeof(m)); }
    inline friend martix operator*(const martix &a, const martix &b) {
        martix c;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++)
                    (c.m[i][j] += ((long long)a.m[i][k] * b.m[k][j]) % MOD) %=
                        MOD;
        return c;
    }
    inline friend martix operator^(martix a, int p) {
        martix b;
        b.m[0][0] = b.m[1][1] = 1;
        while (p) {
            if (p & 1) b = b * a;
            a = a * a;
            p >>= 1;
        }
        return b;
    }
};
int main() {
    martix f, g;
    f.m[0][0] = f.m[1][0] = 1;
    g.m[0][0] = g.m[1][0] = 1;
    g.m[0][1] = 2;
    g.m[1][1] = 4;
    int x;
    scanf("%d", &x);
    printf("%d\n", ((g ^ (x - 1)) * f).m[1][0]);
    return 0;
}