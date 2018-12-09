#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 110
#define MOD 998244353
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int n, m, k, a[MAXN][MAXN];
inline void fail() {
    for (int i = 0; i <= k; i++) printf("0 ");
    puts("");
    exit(0);
}
namespace GCC {
int map[MAXN][MAXN], ans[MAXN];
void dfs(int x, int y, int cur) {
    if (x > n + 1 || y > m + 1) return void(ans[cur]++);
    int start = a[x][y] > 0 ? a[x][y] : std::max(map[x - 1][y], map[x][y - 1]);
    int end = a[x][y] > 0 ? a[x][y] : std::min(map[x - 1][y] + 2, map[x][y - 1] + 2);
    for (int c = start; c <= end; c++) {
        map[x][y] = c;
        if (x > 0 && (c < map[x - 1][y] || c > map[x - 1][y] + 2 || (c == map[x - 1][y] && (c & map[x - 1][y] & 1)))) continue;
        if (y > 0 && (c < map[x][y - 1] || c > map[x][y - 1] + 2 || (c == map[x][y - 1] && (c & map[x][y - 1] & 1)))) continue;
        if (x > 0 && y > 0 && map[x - 1][y - 1] + 4 == c && (~c & ~map[x - 1][y - 1] & 1)) continue;
        y <= m ? dfs(x, y + 1, cur + (a[x][y] == -1 && (c & 1))) : dfs(x + 1, 0, cur + (a[x][y] == -1 && (c & 1)));
    }
}
int main() {
    dfs(0, 0, 0);
    for (int i = 0; i <= k; i++) printf("%d%c", ans[i], " \n"[i == k]);
    return 0;
}
}  // namespace GCC
namespace CGC {
int delta[19683], bin[20], tmp[20], pre[20], f[20][19683];
inline int get(int val, int pos) {
    return val / bin[pos - 1] % 3;
}
inline int main() {
    bin[0] = 1;
    for (int i = 1; i <= m; i++) bin[i] = bin[i - 1] * 3;
    for (int i = 0; i < bin[m]; i++) {
        for (int j = 1; j <= m; j++) {
            delta[i] += get(i, j);
        }
    }
    for (int j = 0; j < bin[m]; j++) {
        if (a[1][0] + delta[j] > a[1][m + 1] || a[1][0] + delta[j] < a[1][m + 1] - 2) continue;
        tmp[0] = a[1][0];
        for (int k = 1; k <= m; k++) tmp[k] = tmp[k - 1] + get(j, k);
        tmp[m + 1] = a[1][m + 1];
        for (int k = 1; k <= m + 1; k++) {
            if (tmp[k] - a[0][k] < 0 || tmp[k] - a[0][k] > 2) goto fail;
            if (tmp[k] == a[0][k] && (a[0][k] & tmp[k] & 1)) goto fail;
        }
        for (int k = 1; k <= m + 1; k++) {
            if (tmp[k - 1] == tmp[k] && (tmp[k - 1] & tmp[k] & 1)) goto fail;
            if (tmp[k] == a[0][k - 1] + 4 && (~tmp[k] & ~a[0][k - 1] & 1)) goto fail;
        }
        up(f[1][j], 1);
    fail:;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < bin[m]; j++) {
            if (!f[i - 1][j]) continue;
            pre[0] = a[i - 1][0];
            for (int k = 1; k <= m; k++) pre[k] = pre[k - 1] + get(j, k);
            pre[m + 1] = a[i - 1][m + 1];
            if (pre[m] + 4 == a[i][m + 1] && (~pre[m] & ~a[i][m + 1] & 1)) continue;
            for (int k = 0; k < bin[m]; k++) {
                if (a[i][0] + delta[k] > a[i][m + 1] || a[i][0] + delta[k] < a[i][m + 1] - 2) continue;
                tmp[0] = a[i][0];
                for (int l = 1; l <= m; l++) tmp[l] = tmp[l - 1] + get(k, l);
                for (int l = 1; l <= m + 1; l++) {
                    if (tmp[l] - pre[l] < 0 || tmp[l] - pre[l] > 2) goto Fail;
                    if (tmp[l] == pre[l] && (pre[l] & tmp[l] & 1)) goto Fail;
                }
                for (int l = 1; l <= m + 1; l++) {
                    if (tmp[l - 1] == tmp[l] && (tmp[l - 1] & tmp[l] & 1)) goto Fail;
                    if (tmp[l] == pre[l - 1] + 4 && (~tmp[l] & ~pre[l - 1] & 1)) goto Fail;
                }
                up(f[i][k], f[i - 1][j]);
            Fail:;
            }
        }
    }
    int ret = 0;
    for (int i = 0; i < bin[m]; i++) {
        if (!f[n][i]) continue;
        pre[0] = a[n][0];
        for (int j = 1; j <= m; j++) pre[j] = pre[j - 1] + get(i, j);
        pre[m + 1] = a[n][m + 1];
        for (int j = 1; j <= m + 1; j++) {
            if (a[n + 1][j] - pre[j] < 0 || a[n + 1][j] - pre[j] > 2) goto FAil;
            if (a[n + 1][j] == pre[j] && (pre[j] & a[n + 1][j] & 1)) goto FAil;
        }
        for (int j = 1; j <= m + 1; j++) {
            if (a[n + 1][j - 1] == a[n + 1][j] && (a[n + 1][j - 1] & a[n + 1][j] & 1)) goto FAil;
            if (a[n + 1][j] == pre[j - 1] + 4 && (~a[n + 1][j] & ~pre[j - 1] & 1)) goto FAil;
        }
        up(ret, f[n][i]);
    FAil:;
    }
    printf("%d\n", ret);
    return 0;
}
}  // namespace CGC

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            scanf("%d", &a[i][j]);
            k += a[i][j] == -1;
        }
    }
    for (int i = 1; i <= m + 1; i++) {
        if (a[0][i] < a[0][i - 1] || a[0][i] - a[0][i - 1] > 2) fail();
        if (a[n + 1][i] < a[n + 1][i - 1] || a[n + 1][i] - a[n + 1][i - 1] > 2) fail();
        if (a[0][i] == a[0][i - 1] && (a[0][i] & a[0][i - 1] & 1)) fail();
        if (a[n + 1][i] == a[n + 1][i - 1] && (a[n + 1][i] & a[n + 1][i - 1] & 1)) fail();
    }
    for (int i = 1; i <= n + 1; i++) {
        if (a[i][0] < a[i - 1][0] || a[i][0] - a[i - 1][0] > 2) fail();
        if (a[i][m + 1] < a[i - 1][m + 1] || a[i][m + 1] - a[i - 1][m + 1] > 2) fail();
        if (a[i][0] == a[i - 1][0] && (a[i][0] & a[i - 1][0] & 1)) fail();
        if (a[i][m + 1] == a[i - 1][m + 1] && (a[i][m + 1] & a[i - 1][m + 1] & 1)) fail();
    }
    if (a[0][m] + 4 == a[1][m + 1] && (~a[0][m] & ~a[1][m + 1] & 1)) fail();
    if (a[n][0] + 4 == a[n + 1][1] && (~a[n][0] & ~a[n + 1][1] & 1)) fail();
    if (n <= 9 && m <= 9 && !k) return CGC::main();
    return GCC::main();
}