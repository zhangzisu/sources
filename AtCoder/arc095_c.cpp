#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, m, mat[15];
char ss[15][15];

inline bool g(int x, int y) {
    for (int i = 1; i <= n; i++)
        if (ss[i][x] != ss[mat[i]][y]) return 0;
    return 1;
}

bool used[15];
inline void check() {
    memset(used, 0, sizeof(used));
    used[0] = m & 1;
    for (int i = 1; i <= m; i++) {
        if (used[i]) continue;
        for (int j = i + 1; j <= m; j++) {
            if (g(i, j)) {
                used[i] = used[j] = 1;
                goto succ;
            }
        }
        if (!used[i] && used[0] && g(i, i)) {
            used[i] = 1;
            used[0] = 0;
            goto succ;
        }
        return;
    succ:;
    }
    puts("YES");
    exit(0);
}

void dfs(int x, bool y) {
    if (x > n) return check();
    if (mat[x]) return dfs(x + 1, y);
    if (y) mat[x] = x, dfs(x + 1, 0), mat[x] = 0;
    int z = x;
    while (++z <= n) {
        if (mat[z]) continue;
        mat[z] = x;
        mat[x] = z;
        dfs(x + 1, y);
        mat[z] = 0;
        mat[x] = 0;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%s", ss[i] + 1);
    dfs(1, n & 1);
    puts("NO");
    return 0;
}