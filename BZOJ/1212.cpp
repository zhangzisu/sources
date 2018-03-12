#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 500
int n, m, k, son[MAXN][26], word[MAXN], f[4096000], cnt, ans, t;
inline void insert(char *s) {
    register int p = 0;
    for (int i = 0; s[i]; i++) {
        const int x = s[i] - 'a';
        if (!son[p][x]) son[p][x] = ++cnt;
        p = son[p][x];
    }
    word[p] = 1;
}
char buf[4096000];
inline void fill(int x) {
    register int p = son[0][buf[x] - 'a'];
    for (; p && x <= k; p = son[p][buf[++x] - 'a'])
        if (word[p]) f[x] = 1;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", buf);
        insert(buf);
    }
    while (m--) {
        scanf("%s", buf + 1);
        k = strlen(buf + 1);
        memset(f, 0, sizeof(f));
        f[0] = 1;
        t = 0;
        for (int i = 0; i <= k; i++) {
            if (t > 10) break;
            if (!f[i]) {
                t++;
                continue;
            }
            ans = i;
            t = 0;
            fill(i + 1);
        }
        printf("%d\n", ans);
    }
    return 0;
}