#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 3010
int data[MAXN][MAXN], tmp[MAXN], n, m;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int main() {
    scanf("%d%d", &n, &m);
    memset(data[0], 0, sizeof(data[0]));
    for (int i = 1; i <= n; i++) {
        memcpy(data[i], data[i - 1], sizeof(data[i]));
        int x;
        scanf("%d", &x);
        data[i][x]++;
    }
    while (m--) {
        int l, r, k, ans = 0;
        scanf("%d%d%d", &l, &r, &k);
        for (int i = 1; i <= n; i++) tmp[i] = data[r][i] - data[l - 1][i];
        for (int i = 1; i <= n; i++)
            if (tmp[i] && gcd(tmp[i], k) == 1) ans++;
        printf("%d\n", ans);
    }
    return 0;
}