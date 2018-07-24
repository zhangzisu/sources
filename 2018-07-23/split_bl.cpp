#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int k, n, m, t, a[50], stk[2][50], ok;
void dfs(int deep, int x, int y) {
    if (deep > n) ok = 1;
    if (ok) return;
    if ((x < m) && ((y <= x) || (a[deep] == stk[1][x + 1]))) {
        stk[0][x + 1] = a[deep];
        dfs(deep + 1, x + 1, y);
    }
    if ((y < m) && ((x <= y) || (a[deep] == stk[0][y + 1]))) {
        stk[1][y + 1] = a[deep];
        dfs(deep + 1, x, y + 1);
    }
}

int main() {
    for (scanf("%d", &t); t; t--) {
        ok = 0;
        scanf("%d", &n);
        m = n >> 1;
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        dfs(1, 0, 0);
        if (ok)
            printf("Frederica Bernkastel\n");
        else
            printf("Furude Rika\n");
    }
    return 0;
}
