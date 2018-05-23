#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2000010
#define MAXT 8000010
int L[MAXT], R[MAXT], cnt = 0;
void insert(int &rt, int l, int r, int p) {
    if (!rt) rt = cnt++;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (p <= mid) return insert(L[rt], l, mid, p);
    return insert(R[rt], mid + 1, r, p);
}
int merge(int x, int y) {
    if (!x || !y) return x | y;
    int z = cnt++;
    L[z] = merge(L[x], L[y]);
    R[z] = merge(R[x], R[y]);
    return z;
}
int query(int n, int l, int r, int _l, int _r) {
    if (!n) return 0;
    if (l == _l && r == _r) return 1;
    int mid = (l + r) >> 1;
    if (_r <= mid) return query(L[n], l, mid, _l, _r);
    if (_l > mid) return query(R[n], mid + 1, r, _l, _r);
    return query(L[n], l, mid, _l, mid) | query(R[n], mid + 1, r, mid + 1, _r);
}
struct state {
    int son[26], len, link, id;
    inline state() {
        memset(son, 0, sizeof(son));
        len = link = 0;
    }
    inline state(state &x) {
        memcpy(son, x.son, sizeof(son));
        len = x.len, link = x.link, id = x.id;
    }
    inline int &operator[](int x) { return son[x]; }
} sam[MAXN];
int tot = 0, last = 0;
inline void extend(int x, int c) {
    int p, q, np, nq;
    p = last;
    last = np = ++tot;
    sam[np].len = sam[p].len + 1;
    sam[np].id = x;
    for (; p && !sam[p][c]; p = sam[p].link) sam[p][c] = np;
    if (!p) return sam[np].link = 1, void();
    q = sam[p][c];
    if (sam[q].len == sam[p].len + 1) return sam[np].link = q, void();
    sam[nq = ++tot] = state(sam[q]);
    sam[nq].len = sam[p].len + 1;
    sam[np].id = x;
    for (; p && sam[p][c] == q; p = sam[p].link) sam[p][c] = nq;
    sam[np].link = sam[q].link = nq;
}
int n, ans, f[MAXN], b[MAXN], c[MAXN], rt[MAXN], pos[MAXN];
void build() {
    for (int i = 1; i <= tot; i++) b[sam[i].len]++;
    for (int i = 1; i <= tot; i++) b[i] += b[i - 1];
    for (int i = tot; i >= 1; i--) c[b[sam[i].len]--] = i;
    for (int i = tot; i >= 2; i--) {
        int x = c[i];
        insert(rt[x], 1, n, sam[x].id);
        rt[sam[x].link] = merge(rt[sam[x].link], rt[x]);
    }
}
char buf[MAXN];
int main() {
    scanf("%d%s", &n, buf + 1);
    last = tot = 1;
    for (int i = 1; i <= n; i++) extend(i, buf[i] - 'a');
    build();
    ans = 1;
    for (int i = 2; i <= tot; i++) {
        int x = c[i];
        if (sam[x].link == 1) {
            f[x] = 1;
            pos[x] = x;
            continue;
        }
        if (query(
                rt[pos[sam[x].link]],
                1,
                n,
                sam[x].id - sam[x].len + sam[pos[sam[x].link]].len,
                sam[x].id - 1))
            f[x] = f[sam[x].link] + 1, pos[x] = x;
        else
            f[x] = f[sam[x].link], pos[x] = pos[sam[x].link];
        ans = std::max(ans, f[x]);
    }
    printf("%d\n", ans);
    return 0;
}
