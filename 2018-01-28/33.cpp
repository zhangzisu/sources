#include <bits/stdc++.h>
#define ll long long
#define mod 998244353
#define N 2009
#define ad(x, y) (x = (x + (y)) % mod)
using namespace std;

int n, m, a[N][N], dp[2][N][3][2][2][2], p[N][3];
char s[N];
int read() {
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}
void work(int p, int i) {
    int j, k, x, y, z;
    for (j = 1; j <= n; j++)
        for (k = 0; k < 3; k++)
            for (x = 0; x < 2; x++)
                for (y = 0; y < 2; y++)
                    ad(dp[p][j][k][1][x][y], dp[p][j][k][0][x][y]);
    for (j = 1; j <= n; j++)
        if (s[j] == 'r')
            for (k = 0; k < 3; k++)
                for (x = 0; x < 2; x++)
                    for (y = 0; y < 2; y++)
                        ad(dp[p][j][k][x][1][y], dp[p][j][k][x][0][y]);
    for (j = 1; j <= n; j++)
        if (s[j] == 'b')
            for (k = 0; k < 3; k++)
                for (x = 0; x < 2; x++)
                    for (y = 0; y < 2; y++)
                        ad(dp[p][j][k][x][y][1], dp[p][j][k][x][y][0]);
    for (j = 1; j <= n; j++)
        for (k = 0; k < 3; k++)
            for (x = 0; x < 2; x++)
                for (y = 0; y < 2; y++)
                    for (z = 0; z < 2; z++) {
                        dp[p][j][k][x][y][z] = (ll)dp[p][j][k][x][y][z] * a[i][j] % mod;
                    }
}
int main() {
    //	string ch="17";
    //freopen(("B"+ch+".in").data(),"r",stdin);
    //	freopen(("B"+ch+".out").data(),"w",stdout);
    n = read();
    m = read();
    scanf("%s", s + 1);
    cerr << "ok" << endl;
    int i, j, k, l, x, y, u, v;
    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++) a[i][j] = read();
    cerr << "ok" << endl;
    for (i = 1; i <= n; i++) {
        p[i][0] = (i == 1 ? n : i - 1);
        p[i][1] = i;
        p[i][2] = i % n + 1;
    }
    for (i = 1; i <= n; i++)
        for (j = 0; j < 3; j++)
            for (k = 0; k <= (s[i] == 'r'); k++)
                for (l = 0; l <= (s[i] == 'b'); l++) {
                    ad(dp[0][p[i][j]][j][0][k][l], a[1][i]);
                }
    work(0, 2);
    int last, now = 0;
    for (i = 3; i <= m; i++) {
        last = now;
        now ^= 1;
        memset(dp[now], 0, sizeof(dp[now]));
        for (j = 1; j <= n; j++)
            for (k = 0; k < 3; k++)
                for (l = 0; l < 3; l++)
                    for (x = (k != l); x < 2; x++) {
                        y = (k == l ? x : 0);
                        for (u = 0; u < 2; u++)
                            for (v = 0; v < 2; v++) {
                                ad(dp[now][p[j][l]][l][y][u][v], dp[last][j][k][x][u][v]);
                                printf("f[%d][%d][%d][%d][%d][%d]=%d\n", now, p[j][l], l, y, u, v, dp[now][p[j][l]][l][y][u][v]);
                                printf("\tfrom f[%d][%d][%d][%d][%d][%d]\n", last, j, k, x, u, v);
                            }
                    }
        work(now, i);
    }
    int ans = 0;
    for (i = 1; i <= n; i++)
        for (j = 0; j < 3; j++)
            for (x = 0; x < 2; x++)
                for (y = 0; y < 2; y++)
                    ad(ans, dp[now][i][j][1][x][y]);
    printf("%d\n", ans);
    return 0;
}