#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
inline int getInt() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 200010
#define MAXK 41
#define MOD 1000000007

int n, m, k, op, x, y;
int val[MAXK][MAXN];
inline void up(int& x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}

int main() {
    n = getInt();
    m = getInt();
    k = getInt();
    val[0][0] = 1;
    for (register int i = 1; i <= k; i++) {
        val[i][0] = 1;
        for (register int j = 1; j < n; j++)
            val[i][j] = (val[i - 1][j] + val[i][j - 1]) % MOD;
    }

    while (m--) {
        op = getInt();
        x = getInt();
        if (op) {
            printf("%d\n", sum[x]);
        } else {
            y = getInt();
            for (register int i = x; i <= n; i++) up(sum[i], 1LL * y * val[k][i - x] % MOD);
        }
    }
    return 0;
}