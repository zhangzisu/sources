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
#define c(x, y) sam[x][y]
#define maxlen(x) sam[x].len
#define link(x) sam[x].link
#define mx(x) sam[x].size
#define rint int

struct state {
    int len, link, size, son[26];
    inline state(int len = 0, int size = 0) {
        this->len = len;
        this->link = 0;
        this->size = size;
        memset(son, 0, sizeof(son));
    }
    inline state(const state& x, int len = 0, int size = 0) {
        this->len = len;
        this->link = x.link;
        this->size = size;
        memcpy(son, x.son, sizeof(son));
    }
    inline int& operator[](int index) { return son[index]; }
} sam[MAXN << 2];

int n, m, q, k, L[MAXN], R[MAXN];

int cnt = 1, pre = 1;
inline void insert(int x) {
    int p, q, s, c;
    sam[p = ++cnt] = state(sam[q = pre].len + 1, 1);
    pre = p;
    for (; q && !sam[q][x]; q = sam[q].link) sam[q][x] = p;
    if (!q) return void(sam[p].link = 1);
    s = sam[q][x];
    if (sam[q].len + 1 == sam[s].len) return void(sam[p].link = s);
    // puts("C");
    sam[c = ++cnt] = state(sam[s], sam[q].len + 1);
    for (; q && sam[q][x] == s; q = sam[q].link) sam[q][x] = c;
    sam[s].link = sam[p].link = c;
}

int LOG[MAXN + 5], fa[MAXN + 5][20], end[MAXN + 5], len[MAXN + 5];
ll Ans;
char s[MAXN];
inline int Query(int p, int l) {
    for (int d = 17; ~d; d--)
        if (sam[fa[p][d]].len >= l) p = fa[p][d];
    return sam[p].size;
}

void Run(rint p = 1) {
    for (rint i = 1, l = 0; i <= k; p = p ? ++l, c(p, s[i] - 'a') : 1, len[i] = l, end[i] = p, i++)
        for (; p && !c(p, s[i] - 'a'); p = link(p), l = maxlen(p))
            ;
}
void Calc() {
    for (rint i = 1; i <= cnt; i++) fa[i][0] = link(i);
    for (rint j = 1, i; j <= 17; j++)
        for (i = 1; i <= cnt; i++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
    for (rint i = 1, l, r; i <= q; printf("%lld\n", Ans), i++) {
        scanf("%s", s + 1);
        Run();
        Ans = 0;
        scanf("%d%d", &l, &r), l++, r++;
        for (; l <= r; l++) {
            if (len[R[l]] >= R[l] - L[l] + 1) Ans += Query(end[R[l]], R[l] - L[l] + 1);
        }
    }
}

int o[MAXN];

int main() {
    scanf("%d%d%d%d", &n, &m, &q, &k);
    scanf("%s", s + 1);
    for (rint i = 1; i <= n; i++) insert(s[i] - 'a');
    for (rint i = 1; i <= cnt; i++) o[i]=i;
    for (rint i = cnt; i; i--) o[book[maxlen(i)]--] = i;
    for (rint i = cnt; i; i--) mx(link(o[i])) += mx(o[i]);
    mx(1) = 0;
    for (rint i = 1; i <= m; i++) scanf("%d%d", &L[i], &R[i]), L[i]++, R[i]++;
    Calc();
    return 0;
}