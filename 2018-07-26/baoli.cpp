#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 310
#define MAXM 40
#define MOD 1000000007

int n, m, k, len[MAXM], val[MAXN];
char buf[MAXM][MAXN];
inline void up(int& x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int f[MAXN][MAXN];
struct trie {
    int son[2], danger, fail;
    inline int& operator[](int index) {
        return son[index];
    }
} acm[2][MAXN];
int cnt[2];
inline void insert(int id, int pos) {
    int p = cnt[id];
    for (int i = 1; i <= len[pos]; i++) {
        int& next = acm[id][p][buf[pos][i] ^ 48];
        if (!next) next = ++cnt[id];
        p = next;
    }
    acm[id][p].danger = 1;
}
std::queue<int> Q;
inline void build(int id) {
    acm[id][1].fail = 0;
    acm[id][0].son[0] = acm[id][0].son[1] = 1;
    while (Q.size()) {
        int x = Q.front();
        for (int i = 0; i < 2; i++) {
            int& y = acm[id][x][i];
            if (y) {
                acm[id][y].fail = acm[id][acm[id][x].fail][i];
                acm[id][y].danger |= acm[id][x].danger;
                Q.push(y);
            } else {
                y = acm[id][acm[id][x].fail][i];
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", buf[i] + 1);
        len[i] = strlen(buf[i] + 1);
        if (len[i] > n) {
            i--;
            n--;
            continue;
        }
        k = std::max(k, len[i]);
    }
    cnt[0] = cnt[1] = 1;
    int len = std::min((n + 1) / 2, k);
    for (int i = 0; i < (1 << len); i++) {
        for (int i = 0; i < len; i++)
    }
    return 0;
}