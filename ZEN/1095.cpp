#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 1000010
char buf[MAXN];
int son[MAXN][26], link[MAXN], len[MAXN], size[MAXN], pre = 1, cnt = 1, n;
inline int state() {
    ++cnt;
    memset(son[cnt], 0, sizeof(son[cnt]));
    link[cnt] = 0, len[cnt] = len[pre] + 1;
    return cnt;
}
inline int clone(int x, int _len) {
    ++cnt;
    memcpy(son[cnt], son[x], sizeof(son[cnt]));
    link[cnt] = link[x], len[cnt] = _len;
    return cnt;
}
inline void insert(int x) {
    int p = state(), q = pre;
    size[pre = cnt] = 1;
    for (; q && !son[q][x]; q = link[q]) son[q][x] = p;
    if (!q) return link[p] = 1, void();
    int s = son[q][x];
    if (len[q] + 1 == len[s]) return link[p] = s, void();
    int c = clone(s, len[q] + 1);
    for (; q && son[q][x] == s; q = link[q]) son[q][x] = c;
    link[s] = link[p] = c;
}
long long res = 0;
std::vector<int> V[MAXN];
void dfs(int x) {
    for (auto y : V[x]) {
        dfs(y);
        res += 1LL * len[x] * size[y] * size[x];
        size[x] += size[y];
    }
}
int main() {
    scanf("%s", buf + 1);
    n = strlen(buf + 1);
    for (int i = n; i; i--) insert(buf[i] - 'a');
    for (int i = 2; i <= cnt; i++) V[link[i]].push_back(i);
    dfs(1);
    printf("%lld\n", (1LL * (n - 1) * n * (n + 1) >> 1) - (res << 1));
    return 0;
}