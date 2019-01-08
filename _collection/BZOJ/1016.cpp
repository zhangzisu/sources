#include <algorithm>
#include <cctype>
#include <cstdio>
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#include <cstdlib>
#include <cstring>
#define MAXM 1010
#define MOD 31011
int n = $(), m = $(), p[MAXM], P[MAXM], S[MAXM], c[MAXM], tot, cnt, ans,
    res = 1;
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
struct _edge {
    int u, v, w, ww;
    inline friend bool operator<(const _edge &a, const _edge &b) {
        return a.w < b.w;
    }
} e[MAXM], s[MAXM];
int main() {
    for (int i = 1; i <= m; i++)
        e[i].u = $(), e[i].v = $(), e[i].w = e[i].ww = $();
    for (int i = 1; i <= n; i++) p[i] = i;
    std::sort(e + 1, e + m + 1);
    for (int i = 1, x = 0; i <= m; i++) {
        if (i == 1 || e[i].ww != e[i - 1].ww) x++;
        e[i].w = x;
    }
    for (int i = 1; i <= m; i++) {
        int U = find(e[i].u), V = find(e[i].v);
        if (U == V) continue;
        p[U] = V;
        c[e[i].w]++;
        cnt++;
    }
    if (cnt != n - 1) return puts("0"), 0;
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 1; i <= m; i++) {
        s[tot++] = e[i];
        if (e[i].w != e[i + 1].w) {
            memcpy(P, p, sizeof(P));
            ans = 0;
            for (int d = 0; d < (1 << tot); d++) {
                if (__builtin_popcount(d) == c[e[i].w]) {
                    memcpy(p, P, sizeof(p));
                    for (int j = 0; j < tot; j++)
                        if ((d >> j) & 1) {
                            int U = find(s[j].u), V = find(s[j].v);
                            if (U == V) goto fail;
                            p[U] = V;
                        }
                    if (!ans++) memcpy(S, p, sizeof(S));
                }
            fail:;
            }
            memcpy(p, S, sizeof(p));
            res = (res * ans) % MOD;
            tot = 0;
        }
    }
    printf("%d\n", res);
    return 0;
}