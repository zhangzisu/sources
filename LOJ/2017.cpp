#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 110

#define MOD 1000000007
struct trie {
    int son[3], fail;
    inline int &operator[](int index) {
        return son[index];
    }
} acm[MAXN];
int cnt;
inline void reset() {
    memset(acm, 0, sizeof(acm));
    cnt = 1;
    for (int i = 0; i < 3; i++) acm[0][i] = 1;
}
inline int insert(int *s, int len) {
    int p = 1;
    for (int i = 1; i <= len; i++) {
        int &nxt = acm[p][s[i]];
        if (!nxt) nxt = ++cnt;
        p = nxt;
    }
    return p;
}
inline void build() {
    std::queue<int> Q;
    acm[1].fail = 0;
    Q.push(1);
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        for (int i = 0; i < 3; i++) {
            int &y = acm[x][i];
            if (y) {
                acm[y].fail = acm[acm[x].fail][i];
                Q.push(y);
            } else {
                y = acm[acm[x].fail][i];
            }
        }
    }
}
inline int getInt() {
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
inline int getAlpha() {
    char ch = getchar();
    while (!isalpha(ch)) ch = getchar();
    return ch == 'W' ? 0 : ch == 'B' ? 1 : 2;
}
int n, m, c, q, s0[MAXN], s1[MAXN], end[2];
int f[101][12][13][4096];
inline void upd(int &x, int y) {
    (x += y) %= MOD;
}
inline void del(int &x, int y) {
    (x -= y) %= MOD;
}

inline void dp() {
    f[0][0][1][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int(*nxt)[4096] = (j == m - 1 ? f[i + 1][0] : f[i][j + 1]);
            for (int k = 1; k <= cnt; k++) {
                for (int l = 0; l < 1 << (m - c + 1); l++) {
                    int real = l << (c - 1), now = f[i][j][k][l];
                    for (int x = 0; x < 3; x++) {
                        int y = acm[k][x];
                        if (((real >> j) & 1) && (y == end[1])) continue;
                        upd(
                            nxt
                                [j == m - 1 ? 1 : y]
                                [((real & ~(1 << j)) | ((y == end[0]) << j)) >> (c - 1)],
                            now);
                    }
                }
            }
        }
    }
}
int main() {
    scanf("%d%d%d%d", &n, &m, &c, &q);
    while (q--) {
        for (int i = 1; i <= c; i++) s0[i] = getAlpha();
        for (int i = 1; i <= c; i++) s1[i] = getAlpha();
        reset();
        memset(f, 0, sizeof(f));
        end[0] = insert(s0, c);
        end[1] = insert(s1, c);
        build();
        dp();
        int ans = 1;
        for (int i = n * m; i >= 1; i--) ans = 1LL * ans * 3 % MOD;
        for (int i = 0; i < (1 << (m - c + 1)); i++) del(ans, f[n][0][1][i]);
        printf("%d\n", (ans + MOD) % MOD);
    }
    return 0;
}