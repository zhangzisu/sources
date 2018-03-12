#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

// using namespace std;
#define BLOCK 512
#define MAXN 200000
#define ll long long
#define c(x, y) t[x].c[y]
#define maxlen(x) t[x].maxlen
#define link(x) t[x].link
#define mx(x) t[x].mx
#define fa(i, j) fa[j][i]

struct Node {
    int c[26], maxlen, link;
    ll mx;
} t[MAXN + 5];
char s[MAXN + 5];
int book[MAXN + 5], o[MAXN + 5], L[MAXN + 5], R[MAXN + 5], last, tot, n, m, q, k;
#define New(p, v) (++tot, maxlen(tot) = p ? maxlen(p) + 1 : 0, mx(tot) = v, tot)
inline void Append(int x) {
    int p = last, np = last = New(p, 1), q, nq;
    for (; p && !c(p, x); c(p, x) = np, p = link(p))
        ;
    if (!p)
        link(np) = 1;
    else if (maxlen(q = c(p, x)) == maxlen(p) + 1)
        link(np) = q;
    else {
        for (nq = New(p, 0), memcpy(t[nq].c, t[q].c, 104); p && c(p, x) == q; c(p, x) = nq, p = link(p))
            ;
        link(nq) = link(q), link(q) = link(np) = nq;
    }
}

int LOG[MAXN + 5], fa(MAXN + 5, 20), end[MAXN + 5], len[MAXN + 5];
ll Ans;
inline ll FindL(int p, int l) {
    for (int j = LOG[maxlen(p)]; ~j; maxlen(fa(p, j)) >= l ? p = fa(p, j) : 0, j--)
        ;
    return mx(p);
}
void Run(int p = 1) {
    for (int i = 1, l = 0; i <= k; p = p ? ++l, c(p, s[i] - 'a') : 1, len[i] = l, end[i] = p, i++)
        for (; p && !c(p, s[i] - 'a'); p = link(p), l = maxlen(p))
            ;
}

int main() {
    scanf("%d%d%d%d", &n, &m, &q, &k), tot = 0, last = New(0, 0);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; Append(s[i] - 'a'), i++)
        ;
    for (int i = tot; i; mx(link(i)) += mx(i), i--)
        ;
    mx(1) = 0;
    for (int i = 1; i <= m; scanf("%d%d", &L[i], &R[i]), L[i]++, R[i]++, i++)
        ;
    for (int i = 2; i <= n; LOG[i] = -~LOG[i >> 1], i++)
        ;
    for (int i = 1; i <= tot; fa(i, 0) = link(i), i++)
        ;
    for (int j = 1, i; j <= LOG[n]; j++)
        for (i = 1; i <= tot; fa(i, j) = fa(fa(i, j - 1), j - 1), i++)
            ;
    for (int i = 1, l, r; i <= q; printf("%lld\n", Ans), i++)
        for (scanf("%s", s + 1), Run(), Ans = 0, scanf("%d%d", &l, &r), l++, r++; l <= r; len[R[l]] >= R[l] - L[l] + 1 ? Ans += FindL(end[R[l]], R[l] - L[l] + 1) : 0, l++)
            ;
    return 0;
}