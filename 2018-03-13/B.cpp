#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2000010
int son[MAXN][26], max[MAXN], cnt = 1;
inline void insert(char *s) {
    for (int p = 1; *s; s++, max[p]++) {
        if (!son[p][*s - 'a']) son[p][*s - 'a'] = ++cnt;
        p = son[p][*s - 'a'];
    }
}
int pa[MAXN], fa[MAXN][20], deep[MAXN];
long long pos[MAXN], last[MAXN];
void dfs(int x) {
    pos[x] = last[x] = last[fa[x][0]] + deep[x] * max[x];
    for (int i = 0; i < 26; i++) {
        if (!son[x][i]) continue;
        pa[son[x][i]] = i;
        fa[son[x][i]][0] = x;
        deep[son[x][i]] = deep[x] + 1;
        dfs(son[x][i]);
        last[x] = std::max(last[x], last[son[x][i]]);
    }
}

std::pair<int, int> val[MAXN];

int n, q, p, m, g, k;
char buf[200010];
int main() {
    scanf("%s", buf);
    n = strlen(buf);
    for (int i = 0; i < n; i++) insert(buf + i);
    dfs(1);
    for(int d = 1;d < 20;d++){
        for(int i = 1;i <= cnt;i++){
            fa[i][d] = fa[fa[i][d - 1]][d - 1];
        }
    }
    for (int i = 1; i <= cnt; i++) val[i] = {pos[i], i};
    std::sort(val + 1, val + cnt + 1);
    // print(1);
    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &p, &m);
        k = 1LL * p * g % m + 1;
        int res = std::lower_bound(val + 1, val + cnt + 1, std::make_pair(k, 0))->second;
        int delta = pos[res] - k;
        int top = deep[res];
        delta %= top;
        for(int i = 0;i < 20;i++)if((delta >> i) & 1)res = fa[res][i];
        printf("%c\n", 'a' + pa[res]);
        g += pa[res] + 'a';
    }
}