#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define SIGMA 26
#define MAXN 20010
int n, tot[MAXN], pos[MAXN], f[MAXN << 1], g[MAXN << 1], ans;
struct state {
    int len, link, son[SIGMA];
    inline state(int Len = 0) {
        len = Len;
        link = 0;
        memset(son, 0, sizeof(son));
    }
    inline state(const state &x) {
        len = x.len;
        link = x.link;
        memcpy(son, x.son, sizeof(son));
    }
} sam[MAXN << 1];
int root = 1, pre = 1, cnt = 1;
inline void insert(int x) {
    register int p, q, s, c;
    sam[p = ++cnt] = state(sam[q = pre].len + 1);
    pre = p;
    for (; q && !sam[q].son[x]; q = sam[q].link) sam[q].son[x] = p;
    if (!q) return void(sam[p].link = root);
    s = sam[q].son[x];
    if (sam[q].len + 1 == sam[s].len) return void(sam[p].link = s);
    sam[c = ++cnt] = state(sam[s]);
    sam[c].len = sam[q].len + 1;
    for (; q && sam[q].son[x] == s; q = sam[q].link) sam[q].son[x] = c;
    sam[s].link = sam[p].link = c;
}
char buf[MAXN];
int main() {
    scanf("%d", &n);
    scanf("%s", buf);
    for (int i = 0; buf[i]; i++) insert(buf[i] - 'a');
    for (int i = 1; i <= cnt; i++) tot[f[i] = sam[i].len]++;
    for (int i = 1; i <= cnt; i++) tot[i] += tot[i - 1];
    for (int i = cnt; i >= 1; i--) pos[tot[sam[i].len]--] = i;
    for (int _ = 2; _ <= n; _++) {
        scanf("%s", buf);
        register int len = 0, now = 1;
        memset(g, 0, sizeof(g));
        for (int j = 0; buf[j]; j++) {
            const int x = buf[j] - 'a';
            while (!sam[now].son[x] && now) now = sam[now].link;
            if (!now)
                len = 0, now = 1;
            else
                len = std::min(len, sam[now].len) + 1, now = sam[now].son[x];
            g[now] = std::max(g[now], len);
        }
        for (int i = cnt; i; i--) g[sam[pos[i]].link] = std::max(g[sam[pos[i]].link], g[pos[i]]);
        for (int i = cnt; i; i--) f[i] = std::min(f[i], g[i]);
    }
    for (int i = 1; i <= cnt; i++) ans = std::max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}
