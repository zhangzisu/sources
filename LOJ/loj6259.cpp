#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
inline char a() {
    register char ch = gc();
    while (!isalpha(ch) && ch ^ '.') ch = gc();
    return ch;
}
#define MAXN 310
#define MOD 1000000007
const int d[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
int _ = $(), n, m, t;
int anc[MAXN][MAXN], vis[MAXN][MAXN], val[MAXN][MAXN], x[MAXN], y[MAXN], timer;
int DFS(int x, int y) {
    if (vis[x][y] == timer) return -1;
    if (~anc[x][y]) return anc[x][y];
    if (!x || !y || x > n || y > m) return anc[x][y] = 0;
    vis[x][y] = timer;
    return anc[x][y] = DFS(x + d[val[x][y]][0], y + d[val[x][y]][1]);
}
int MAP[256];
long long A[MAXN][MAXN];
inline long long fpow(long long x, int p) {
    register long long ret = 1;
    while (p) {
        if (p & 1) (ret *= x) %= MOD;
        (x *= x) %= MOD;
        p >>= 1;
    }
    return ret;
}
inline long long MTT() {
    long long ret = 1, inv, tmp;
    for (int i = 1; i <= t; i++)
        for (int j = 1; j <= t; j++)
            if (A[i][j] < 0) A[i][j] += MOD;
    for (int i = 1; i <= t; i++) {
        int p = i;
        while (p <= t && !A[p][i]) p++;
        if (p > t) return 0;
        if (p != i) {
            for (int j = i; j <= t; j++) std::swap(A[i][j], A[p][j]);
            ret = p - ret;
        }
        (ret *= A[i][i]) %= MOD;
        inv = fpow(A[i][i], MOD - 2);
        for (p = i + 1; p <= t; p++) {
            if (!A[p][i]) continue;
            tmp = A[p][i] * inv % MOD;
            for (int j = i; j <= t; j++)
                (A[p][j] += MOD - A[i][j] * tmp % MOD) %= MOD;
        }
    }
    return ret;
}
int main() {
    MAP['L'] = 0;
    MAP['R'] = 1;
    MAP['U'] = 2;
    MAP['D'] = 3;
    MAP['.'] = -1;
    while (_--) {
        memset(anc, -1, sizeof(anc));
        memset(vis, 0, sizeof(vis));
        memset(val, 0, sizeof(val));
        n = $(), m = $();
        t = timer = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if ((val[i][j] = MAP[(int)a()]) == -1) {
                    anc[i][j] = ++t;
                    x[t] = i;
                    y[t] = j;
                }
            }
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (!vis[i][j] && ~val[i][j]) {
                    ++timer;
                    if (!~DFS(i, j)) goto fail;
                }
        memset(A, 0, sizeof(A));
        for (int i = 1; i <= t; i++) {
            for (int k = 0; k < 4; k++) {
                int next = anc[x[i] + d[k][0]][y[i] + d[k][1]];
                if (i != next) A[i][i]++, A[i][next]--;
            }
        }
        printf("%lld\n", MTT());
        continue;
    fail:
        puts("0");
    }
}