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
#define MAXN 2010
#define MAXM 100010
typedef long long lnt;
const lnt INF = 0x3F3F3F3F3F3F3F3F;
struct hydra {
    lnt d[9][9];
    inline hydra() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                d[i][j] = i == j ? 0 : INF;
            }
        }
    }
    inline hydra friend operator+(hydra a, hydra b) {
        hydra ret;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                for (int k = 0; k < 9; k++) {
                    ret.d[i][j] = std::min(ret.d[i][j], a.d[i][k] + b.d[k][j]);
                }
            }
        }
        return ret;
    }
} val[MAXN << 2];
int head[MAXN], u[MAXM], v[MAXM], w[MAXM], next[MAXM], tot = 0;
inline void $(int p, int U, int V, int W) {
    next[tot] = head[p], u[tot] = U, v[tot] = V, w[tot] = W, head[p] = tot++;
}
lnt tmp[9][9];
void build(int n, int l, int r) {
    if (l == r) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                tmp[i][j] = i == j ? 0 : INF;
            }
        }
        for (int i = head[l]; ~i; i = next[i]) {
            tmp[u[i]][v[i]] = std::min(tmp[u[i]][v[i]], (lnt)w[i]);
        }
        for (int k = 0; k < 9; k++) {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    tmp[i][j] = std::min(tmp[i][j], tmp[i][k] + tmp[k][j]);
                }
            }
        }
        memcpy(val[n].d, tmp, sizeof(tmp));
        return;
    }
    int mid = (l + r) >> 1;
    build(n << 1, l, mid);
    build(n << 1 | 1, mid + 1, r);
    val[n] = val[n << 1] + val[n << 1 | 1];
}
hydra query(int n, int l, int r, int L, int R) {
    if (l == L && r == R) return val[n];
    int mid = (l + r) >> 1;
    if (R <= mid) return query(n << 1, l, mid, L, R);
    if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R);
    return query(n << 1, l, mid, L, mid) + query(n << 1 | 1, mid + 1, r, mid + 1, R);
}
const int n = 2000;
std::pair<int, int> qry[MAXM];
int main() {
    freopen("tesseract.in", "r", stdin);
    freopen("tesseract.out", "w", stdout);

    memset(head, -1, sizeof(head));
    for (int m = $(), p = $(), u, v, w; m; m--) {
        p = $(), u = $(), v = $(), w = $();
        $(p, u, v, w);
    }
    build(1, 1, n);
    for (int q = $(), s, t, k; q; q--) {
        s = $(), t = $(), k = $();
        for (int i = 1; i <= k; i++) qry[i].first = $(), qry[i].second = $();
        std::sort(qry + 1, qry + k + 1);
        hydra all;
        for (int i = 1; i <= k; i++) {
            all = all + query(1, 1, n, qry[i].first, qry[i].second);
        }
        printf("%lld\n", all.d[s][t] == INF ? -1 : all.d[s][t]);
    }
    return 0;
}