#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 200010
#define MAXK 41
#define MOD 1000000007
#define MAXM 1000010
int n, m, k;
int val[MAXK][MAXN];
int sum[MAXM], cnt = 0;
const int N = sqrt(MAXN) + 1;
struct oper {
    int type, x, y, ans, id;
} d[MAXN];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    val[0][0] = 1;
    for (int i = 1; i <= k; i++) {
        val[i][0] = 1;
        for (int j = 1; j < n; j++)
            val[i][j] = (val[i - 1][j] + val[i][j - 1]) % MOD;
    }

    for (int i = 1; i <= m; i += d[i].type || scanf("%d", &d[i].y))
        scanf("%d%d", &d[i].type, &d[i].x), d[i].id = i;

    
    return 0;
}