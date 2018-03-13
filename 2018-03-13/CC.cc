#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
#define MOD 1000000007
long long d[MAXN][MAXN];
int t, n, p, ans;
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &p);
        d[0][0] = 1; ans = 1;
        for (int i = 1; i <= n; i++) {
            d[i][0] = 1;
            for (int j = 1; j <= n; j++) {
                d[i][j] = (d[i - 1][j] + d[i - 1][j - 1] * i) % p;
                if(i == n)ans += d[i][j] != 0;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}