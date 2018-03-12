#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
struct state {
    int son[26], len, link;
    inline state() {
        memset(son, 0, sizeof(son));
        len = link = 0;
    }
    inline int& operator[](int x) {
        return son[x];
    }
} sam[MAXN << 2];
int cnt = 1, last = 1;
inline void insert(int x) {
    int p;
    if (p = sam[last][x]) {
        if (sam[p].len == sam[last].len + 1) {
            last = p;
        } else {
            int c = ++cnt;
            sam[c].len = sam[last].len + 1;
            sam[c].link = sam[p].link;
            sam[p].link = c;
            memcpy(sam[c].son, sam[p].son, sizeof(int) * 26);
            for (int q = last; q && sam[q][x] == p; q = sam[q].link) sam[q][c] = c;
            last = c;
        }
    } else {
        int q = last;
        p = last = ++cnt;
        sam[p].len = sam[q].len + 1;
        for (; q && !sam[q][x]; q = sam[q].link) sam[q][c] = p;
        if (!q) {
            sam[p].link = 1;
        } else {
            int s = sam[q][x];
            if (sam[s].len == sam[q].len + 1) {
                sam[p].link = q;
            } else {
                int c = ++cnt;
                sam[c].len = sam[q].len + 1;
                sam[c].link = sam[s].link;
                memcpy(sam[c].son, sam[s].son, sizeof(int) * 26);
                for (; q && sam[q][x] == s; q = sam[q].link) sam[q][x] = c;
                sam[s].link = sam[p].link = c;
            }
        }
    }
}
int n, m, q, k;
char buf[MAXN];
int main() {
    scanf("%d%d%d%d", &n, &m, &q, &k);
    scanf("%s", buf);
    for (int i = 0; buf[i]; i++) insert(buf[i] - 'a');
    return 0;
}