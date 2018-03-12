#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#define MAXN 10
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

int cnt = 1, pre = 1;
inline void insert(int x) {
    int p, q, s, c;
    sam[p = ++cnt] = state(sam[q = pre].len + 1, 1);
    pre = p;
    for (; q && !sam[q][x]; q = sam[q].link) sam[q][x] = p;
    if (!q) return void(sam[p].link = 1);
    s = sam[q][x];
    if (sam[q].len + 1 == sam[s].len) return void(sam[p].link = s);
    sam[c = ++cnt] = state(sam[s], sam[q].len + 1);
    for (; q && sam[q][x] == s; q = sam[q].link) sam[q][x] = c;
    sam[s].link = sam[p].link = c;
}

int n, m, q, k;
char buf[MAXN];
int l[MAXN], r[MAXN];
int L, R, len[MAXN], pos[MAXN];
int fa[MAXN][18];

inline void prepare() {
    for (int i = 1; i <= cnt; i++) fa[i][0] = sam[i].link;
    for (int d = 1; d < 18; d++)
        for (int i = 1; i <= cnt; i++) fa[i][d] = fa[fa[i][d - 1]][d - 1];
}

inline void init(char* buf) {
    for (int i = 0, p = 1, l = 0; buf[i]; i++) {
        for (; p && !sam[p][buf[i] - 'a']; p = sam[p][buf[i] - 'a']) l = sam[p].size;
        if (p) {
            ++l;
            p = sam[p][buf[i] - 'a'];
        } else {
            p = 1;
        }
        len[i + 1] = l;
        pos[i + 1] = p;
    }
}

inline int Query(int p, int l) {
    for (int d = 17; ~d; d--)
        if (sam[fa[p][d]].len >= l) p = fa[p][d];
    return sam[p].size;
}

int main() {
    scanf("%d%d%d%d", &n, &m, &q, &k);
    scanf("%s", buf);
    for (int i = 0; buf[i]; i++) insert(buf[i] - 'a');
    for (int i = 1; i <= cnt; i++) printf("LINK[%d]=%d\n", i, sam[i].link);
    for(int i=1;i<=cnt;i++){
        for(int j=0;j<26;j++){
            if(sam[i][j])printf("SON[%d][%c]=%d\n",i,(char)j+'a',sam[i][j]);
        }
    }

    for (int i = cnt; i; i--) sam[sam[i].link].size += sam[i].size;
    puts("DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD");
    for(int i = 1;i <= cnt;i++)printf("NODE[%d] : {len = %d, size = %d}\n", i, sam[i].len, sam[i].size);
    puts("DONEDONEDONEDONEDONEDONEDONEDONE");
    sam[1].size = 0;
    for (int i = 1; i <= m; i++) scanf("%d%d", &l[i], &r[i]),l[i]++,r[i]++;
    while (q--) {
        scanf("%s%d%d", buf, &L, &R);
        init(buf);
        long long ans = 0;
        for (int i = L; i <= R; i++) {
            if (len[r[i]] >= r[i] - l[i] + 1) {
                ans += Query(pos[r[i]], r[i] - l[i] + 1);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}